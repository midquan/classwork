/* 
 * This file is derived from source code for the Pintos
 * instructional operating system which is itself derived
 * from the Nachos instructional operating system. The 
 * Nachos copyright notice is reproduced in full below. 
 *
 * Copyright (C) 1992-1996 The Regents of the University of California.
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for any purpose, without fee, and
 * without written agreement is hereby granted, provided that the
 * above copyright notice and the following two paragraphs appear
 * in all copies of this software.
 *
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE
 * AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF CALIFORNIA
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
 * BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
 * MODIFICATIONS.
 *
 * Modifications Copyright (C) 2017 David C. Harrison. All rights reserved.
 */

#include <stdio.h>
#include <syscall-nr.h>
#include <list.h>

#include "devices/shutdown.h"
#include "devices/input.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "filesys/inode.h"
#include "filesys/directory.h"
#include "threads/palloc.h"
#include "threads/malloc.h"
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "threads/lock.h"
#include "userprog/syscall.h"
#include "userprog/process.h"
#include "userprog/umem.h"


struct lock filelock;

static void syscall_handler(struct intr_frame *);

static void write_handler(struct intr_frame *);
static void exit_handler(struct intr_frame *);
static void create_handler(struct intr_frame *);
static void open_handler(struct intr_frame *);
static void read_handler(struct intr_frame *);
static void filesize_handler(struct intr_frame *);
static void close_handler(struct intr_frame *);
static void exec_handler(struct intr_frame *);
static void wait_handler(struct intr_frame *);

/*File tracker stores file descriptor
 *Keeps pointer of an open file, the file descriptor int,
 * and the list_elem that will be stored inside of a thread's 
 * list of file descriptors
 */
struct file_tracker {
    struct file *file;
    struct list_elem fileelement;
    int fileid;
};

void
syscall_init (void)
{
  lock_init(&filelock);
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler(struct intr_frame *f)
{
  int syscall;
  ASSERT( sizeof(syscall) == 4 ); // assuming x86

  // The system call number is in the 32-bit word at the caller's stack pointer.
  umem_read(f->esp, &syscall, sizeof(syscall));

  // Store the stack pointer esp, which is needed in the page fault handler.
  // Do NOT remove this line
  thread_current()->current_esp = f->esp;

  switch (syscall) {
  case SYS_HALT: 
    shutdown_power_off();
    break;

  case SYS_EXIT: 
    exit_handler(f);
    break;
      
  case SYS_WRITE: 
    write_handler(f);
    break;

  // create system call
  case SYS_CREATE:
    create_handler(f);
    break;
    
  // open system call
  case SYS_OPEN:
    open_handler(f);
    break; 
    
  // read system call
  case SYS_READ:
    read_handler(f);
    break;
    
  // filesize system call, needed for read  
  case SYS_FILESIZE:
    filesize_handler(f);
    break;
    
  // close system call
  case SYS_CLOSE:
    close_handler(f);
    break;
    /*
  case SYS_EXEC:
    exec_handler(f);
    break;
    
  case SYS_WAIT:
    wait_handler(f);
    break; */
    
  default:
    printf("[ERROR] system call %d is unimplemented!\n", syscall);
    thread_exit();
    break;
  }
}

/****************** System Call Implementations ********************/

// *****************************************************************
// CMPS111 Lab 3 : Put your new system call implementatons in your 
// own source file. Define them in your header file and include 
// that .h in this .c file.
// *****************************************************************

void sys_exit(int status) 
{
  printf("%s: exit(%d)\n", thread_current()->name, status);
  thread_exit();
}

static void exit_handler(struct intr_frame *f) 
{
  int exitcode;
  umem_read(f->esp + 4, &exitcode, sizeof(exitcode));

  sys_exit(exitcode);
}

/*
 * BUFFER+0 and BUFFER+size should be valid user adresses
 */
static uint32_t sys_write(int fd, const void *buffer, unsigned size)
{
  umem_check((const uint8_t*) buffer);
  umem_check((const uint8_t*) buffer + size - 1);

  int ret = -1;
  lock_acquire(&filelock);
  if (fd == 1) { // write to stdout
    putbuf(buffer, size);
    ret = size;
  } else { //My code for when writing into file
      struct file_tracker *file_track = NULL;
      struct list *filelist = &(thread_current()->file_track_list);
      for (struct list_elem *e = list_begin(filelist); 
          e != list_end(filelist); e = list_next(e)) {
          file_track = list_entry(e, struct file_tracker, fileelement);
          if (file_track->fileid == fd) {
              break;
           }
      }
      ret = file_write(file_track->file, buffer, size);
  }
  lock_release(&filelock);
  return (uint32_t) ret;
}

static void write_handler(struct intr_frame *f)
{
    int fd;
    const void *buffer;
    unsigned size;

    umem_read(f->esp + 4, &fd, sizeof(fd));
    umem_read(f->esp + 8, &buffer, sizeof(buffer));
    umem_read(f->esp + 12, &size, sizeof(size));

    f->eax = sys_write(fd, buffer, size);
}

/* Create Handler
 * Reads in the filename and size of the file to be created. 
 * Locks filelock during filesys_create
 */
static void create_handler(struct intr_frame *f) {
    const char *filename;
    int size;
    umem_read(f->esp + 4, &filename, sizeof(filename));
    umem_read(f->esp + 8, &size, sizeof(size));
    lock_acquire(&filelock);
    f->eax = filesys_create(filename, size, false);
    lock_release(&filelock);
}

/* Open Handler
 * 
 */
static void open_handler(struct intr_frame *f) {
    const char *filename;
    umem_read(f->esp + 4, &filename, sizeof(filename));
    struct file *openfile;
    struct file_tracker *file_track = palloc_get_page(0);
    
    lock_acquire(&filelock);
    openfile = filesys_open(filename);
    
    //if statement required to pass test open-missing
    if (!openfile) {
        lock_release(&filelock); 
        f->eax = -1;
        return;
    }
    
    file_track->file = openfile;
    struct list *filelist = &(thread_current()->file_track_list);
    if (list_empty(filelist)) {
        file_track->fileid = 2; 
    } else {
        file_track->fileid = (list_entry(list_back(filelist), 
            struct file_tracker, fileelement)->fileid) + 1;
    }
    list_push_back(filelist, &(file_track->fileelement));
    lock_release(&filelock);
    
    f->eax = file_track->fileid;
}

/* Read Handler
 * Starting variables, reads, and checks same as given write handler
 * buffer not const, and file_track initialized as null to avoid a compiler warning
 */
static void read_handler(struct intr_frame *f) {
    int fd;
    void *buffer;
    unsigned size;
    umem_read(f->esp + 4, &fd, sizeof(fd));
    umem_read(f->esp + 8, &buffer, sizeof(buffer));
    umem_read(f->esp + 12, &size, sizeof(size));
    umem_check((const uint8_t*) buffer);
    umem_check((const uint8_t*) buffer + size - 1);
    
    lock_acquire(&filelock);
    if (fd == 0) {
        for (unsigned i = 0; i < size; i++) {
            buffer = buffer + i;
            *(char *) buffer = input_getc();
        }
        f->eax = size;
    } else {
        struct file_tracker *file_track = NULL;
        struct list *filelist = &(thread_current()->file_track_list);
        for (struct list_elem *e = list_begin(filelist); 
            e != list_end(filelist); e = list_next(e)) {
           file_track = list_entry(e, struct file_tracker, fileelement);
            if (file_track->fileid == fd) {
                break;
            }
        }
        f->eax = file_read(file_track->file, buffer, size);
        
    }
    lock_release(&filelock);
}

/* Filesize Handler
 * Got an error for read-normal test saying that system call 7 is 
 * unimplemented. According to a canvas post, this system call 7 
 * is SYS_FILESIZE and is required for the SYS_READ call.
 */
static void filesize_handler(struct intr_frame *f){ 
    int fileid;
    umem_read(f->esp + 4, &fileid, sizeof(fileid));
    lock_acquire(&filelock);
    struct file_tracker *file_track = NULL;
    struct list *filelist = &(thread_current()->file_track_list);
    for (struct list_elem *e = list_begin(filelist); 
        e != list_end(filelist); e = list_next(e)) {
        file_track = list_entry(e, struct file_tracker, fileelement);
            if (file_track->fileid == fileid) {
                break;
            }
    }
    f->eax = file_length(file_track->file);
    lock_release(&filelock);
}

static void close_handler(struct intr_frame *f) {
    int fileid;
    umem_read(f->esp + 4, &fileid, sizeof(fileid));
    lock_acquire(&filelock);
    struct file_tracker *file_track = NULL;
    struct list *filelist = &(thread_current()->file_track_list);
    for (struct list_elem *e = list_begin(filelist); 
        e != list_end(filelist); e = list_next(e)) {
        file_track = list_entry(e, struct file_tracker, fileelement);
            if (file_track->fileid == fileid) {
                break;
            }
    }
    list_remove(&(file_track->fileelement));
    file_close(file_track->file);
    lock_release(&filelock);
}
/*
static void exec_handler(struct intr_frame *f) {
    
}
static void wait_handler(struct intr_frame *f) {
    
}
 */
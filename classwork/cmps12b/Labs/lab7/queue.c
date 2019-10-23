// $Id: queue.c,v 1.7 2016-02-26 01:07:22-08 - - $
//Michael Quan midquan

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf (stderr, __VA_ARGS__);

typedef struct queue_node queue_node;
struct queue_node {
   queue_item_t item;
   queue_node *link;
};

struct queue {
   queue_node *front;
   queue_node *rear;
};

queue *new_queue (void) {
   queue *this = malloc (sizeof (struct queue));
   assert(this != NULL);
   this->front = NULL;
   this->rear = NULL;
   return this;
}

void free_queue (queue *this) {
   assert (isempty_queue (this));
   free (this);
}

void insert_queue (queue *this, queue_item_t item) {
   queue_node *insert = malloc(sizeof (queue_node));
   assert(insert != NULL);
   insert->item = item;
   insert->link = NULL;
   if (this->front == NULL) this->front = insert;
      else this->rear->link = insert;
   this->rear = insert; 
}

queue_item_t remove_queue (queue *this) {
   queue_node *remove = NULL;
   remove = this->front;
   this->front = this->front->link;
   queue_item_t remove_item = remove->item;
   free(remove);
   return remove_item; 
}

bool isempty_queue (queue *this) {
   return this->front == NULL;
}


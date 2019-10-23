// $Id: queue.h,v 1.1 2016-02-26 00:58:47-08 - - $
// Michael Quan midquan

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>

typedef struct queue queue;
typedef char *queue_item_t;

queue *new_queue (void);

void free_queue (queue*);

void insert_queue (queue*, queue_item_t);

queue_item_t remove_queue (queue*);

bool isempty_queue (queue*);

#endif


#ifndef CONDVAR_H
#define CONDVAR_H

#include "threads/semaphore.h"
#include "threads/lock.h"

/* Condition variable */
struct condvar {
    struct list waiters; /* List of semaphore_elems */
};

bool comp_sema(const struct list_elem *x, const struct list_elem *y);
void condvar_init(struct condvar *);
void condvar_wait(struct condvar *, struct lock *);
void condvar_signal(struct condvar *, struct lock *);
void condvar_broadcast(struct condvar *, struct lock *);

#endif /* UCSC CMPS111 */

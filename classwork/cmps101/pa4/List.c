// List.c
// Michael Quan
// midquan
// Programing Assignment 4
// Linked-list constructor and functions

#include<stdio.h>
#include<stdlib.h>

#include "List.h"

typedef struct NodeObj{
   int data;
	struct NodeObj* prev;
   struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private QueueObj type
typedef struct ListObj{
   Node front;
   Node back;
	Node cursor;
	int numData;
   int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

Node newNode(int data, Node prev, Node next){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = next;
	N->prev = prev;
   return(N);
}

List newList(void){
	List L; 
	L = malloc(sizeof (ListObj));
	L->front = L->back = NULL;
	L->numData = 0;
	L->index = -1;
	return (L);
}

void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

void freeList(List* pL){
	if(pL!=NULL && *pL!=NULL) { 
      Node temp = (*pL)->front; 
      while(temp != NULL) {
         Node cur = temp;
         temp = temp->next;
         free(cur);
      }
		free(*pL);
		*pL = NULL;
   }
}
// Access functions -----------------------------------------------------------

// Returns the number of elements in this List.
int length(List L){
	if(L == NULL){
      fprintf(stderr, "Cannot call length() from NULL list reference. \n");
      exit(1);
   }
	return L->numData; 
}

// If cursor is defined, returns the index of the cursor element, otherwise returns -1.
int index(List L){
	if(L == NULL){
      fprintf(stderr, "Cannot call index() from NULL list reference. \n");
      exit(1);
   }
	if (L->cursor == NULL) return -1;
	return L->index;
}

// Returns front element. Pre: length()>0	
int front(List L){
	if(L == NULL){
      fprintf(stderr, "Cannot call front() from NULL list reference. \n");
      exit(1);
   }
	if(L->numData < 1){
		fprintf(stderr, "Cannot call front() from an empty list \n");
      exit(1);
	}
	return L->front->data;
}

// Returns back element. Pre: length()>0
int back(List L){
	if(L == NULL){
      fprintf(stderr, "Cannot call back() from NULL list reference. \n");
      exit(1);
   }
	if(L->numData < 1){
		fprintf(stderr, "Cannot call back() from an empty list \n");
      exit(1);
	}
	return L->back->data;
}

// Returns cursor element. Pre: length()>0, index()>=0
int get(List L){
	if(L->numData < 1 || L->index == -1){
		fprintf(stderr, "Cannot call get() from an empty list \n");
      exit(1);
	}
	return L->cursor->data;
	
}

// Returns true if this List and L are the same integer
// sequence. The cursor is ignored in both lists.
int equals(List A, List B){
	if( A==NULL || B==NULL ){
      fprintf(stderr, "Cannot call equals() from NULL list references. \n");
      exit(1);
   }
	if(A->numData != B->numData) return 0;
	Node test1 = A->front;
	Node test2 = B->front;
	while(test1->next != NULL && test2->next != NULL){
      if(test1->data != test2->data) return 0;
      test1 = test1->next;
      test2 = test2->next;
   }
	return 1;
}

// Manipulation procedures ----------------------------------------------------

// Resets this List to its original empty state.
void clear(List L){
	if(L == NULL){
      fprintf(stderr, "Cannot call clear() from NULL list reference. \n");
      exit(1);
   }
	Node temp = L->front;
	while (temp != NULL){
		Node clr = temp; 
		temp = temp->next;
		free(clr);
	} 
	
	L->front = L->back = L->cursor = NULL;
	L->numData = 0;
	L->index = -1;
}

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
	if(L == NULL){
      fprintf(stderr, "Cannot call moveFront() from NULL list reference. \n");
      exit(1);
   }
	if (L->numData > 0){
		L->cursor = L->front;
		L->index = 0;
	}
}

// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
	if(L == NULL){
      fprintf(stderr, "Cannot call moveBack() from NULL list reference. \n");
      exit(1);
   }
	if (L->numData > 0){
		L->cursor = L->back;
		L->index = L->numData - 1;
	}
}

// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L){
	if(L == NULL){
      fprintf(stderr, "Cannot call movePrev() from NULL list reference. \n");
      exit(1);
   }
	if(L->cursor != NULL ){
			if(L->index == 0){
				L->cursor = NULL; 
				L->index = -1;
			}
			if(L->index > 0){
				L-> cursor = L->cursor->prev;
				L->index--;
			}
	}
}

// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L){
	if(L == NULL){
		fprintf(stderr, "Cannot call moveNext() from NULL list reference. \n");
		exit(1);
   }
	if(L->cursor != NULL ){
			if(L->index == 0){
				L->cursor = NULL; 
				L->index = -1;
			}
			if(L->index < L->numData-1 && L->index >= 0){
				L-> cursor = L->cursor->next;
				L->index++;
			}
	}
}

// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
	if(L == NULL){
      fprintf(stderr, "Cannot call prepend() from NULL list reference. \n");
      exit(1);
   }
	Node temp = newNode(data,NULL,L->front);
	if(L->numData < 1) L->front = L->back = temp;

	if(L->front == NULL) L->back = temp;
   else L->front->prev = temp;
	
	L->front = temp;
	L->numData++;
}

// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data){
	if(L == NULL){
		fprintf(stderr, "Cannot call append() from NULL list reference. \n");
		exit(1);
   }
	Node temp = newNode(data,L->back,NULL);
	if(L->numData < 1) L->front = L->back = temp;
	
   if(L->front == NULL) L->front = temp;
   else L->back->next = temp;
	L->numData++;
	L->back = temp;
}
	
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
	if(L == NULL){
		fprintf(stderr, "Cannot call insertBefore() from NULL list reference. \n");
		exit(1);
   }
	if (L->numData < 1 || L->index <= -1){
		fprintf(stderr, "Cannot call insertBefore() from an empty list \n");
		exit(1);
	}
	Node temp = newNode(data, L->cursor->prev, L->cursor);
	if(L->cursor->next != NULL) L->cursor->prev->next = temp;
	else L->front = temp;
	
	L->cursor->prev = temp;
	L->numData++;
}

// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
	if(L == NULL){
		fprintf(stderr, "Cannot call insertAfter() from NULL list reference. \n");
		exit(1);
   }
	if (L->numData < 1 || L->index <= -1){
		fprintf(stderr, "Cannot call insertAfter() from an empty list \n");
		exit(1);
	}
	Node temp = newNode(data, L->cursor, L->cursor->next);
	if(L->cursor->next != NULL) L->cursor->next->prev = temp;
	else L->back = temp;
	
	L->cursor->next = temp;
	L->numData++;	
}

// Deletes the front element. Pre: length()>0
void deleteFront(List L){
	if(L == NULL){
		fprintf(stderr, "Cannot call deleteFront() from NULL list reference. \n");
		exit(1);
   }	
	if (L->numData < 1){
		fprintf(stderr, "Cannot call deleteFront() from an empty list \n");
		exit(1);
	}
	if (L->cursor == L->front){
		L->cursor = NULL;
		L->index = -1;
	}
	Node temp = L->front;
	L->front = L->front->next;
	L->front->prev = NULL;
	L->numData--;
	freeNode(&temp);
}

// Deletes the back element. Pre: length()>0
void deleteBack(List L){
	if(L == NULL){
		fprintf(stderr, "Cannot call deleteBack() from NULL list reference. \n");
		exit(1);
   }	
	if (L->numData < 1){
		fprintf(stderr, "Cannot call deleteBack() from an empty list \n");
		exit(1);
	}
	if (L->cursor == L->back){
		L->cursor = NULL;
		L->index = -1;
	}
	Node temp = L->back;
	L->back = L->back->prev;
	L->back->next = NULL;
	L->numData--;	
	freeNode(&temp);
}

// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
	if(L == NULL){
		fprintf(stderr, "Cannot call deleteBack() from NULL list reference. \n");
		exit(1);
   }	
	if (L->numData < 1 || L->index <= -1){
		fprintf(stderr, "Cannot call deleteBack() from an empty list \n");
		exit(1);
	}	
	if(L->cursor == L->back) deleteBack(L);
	else if(L->cursor == L->front) deleteFront(L);
	
	else{
		Node temp = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		freeNode(&temp);
		L->cursor = NULL;
		L->index = -1;
		L->numData--;
	}
	
	
}


// Other operations -----------------------------------------------------------

// Prints out a string representation of the list. Prints a
// representation of this List consisting of a space
// separated sequence of integers, with front on left.
void printList(FILE* out, List L){
	Node temp = L->front;
	while(temp != NULL) {
      printf("%d ", temp->data);
      temp = temp->next;
   }
}

// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L){
	List cop = newList();
	for(Node fir = L->front; fir != NULL; fir = fir->next){
		append(cop, fir->data);
	}
	return cop;
	
}
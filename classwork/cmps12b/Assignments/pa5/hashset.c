// $Id: hashset.c,v 1.13 2016-03-12 05:38:01-08 - - $
// Michael Quan midquan

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15

typedef struct hashnode hashnode;
struct hashnode {
   char *word;
   hashnode *link;
};

struct hashset {
   size_t size;
   size_t load;
   hashnode **chains;
};

hashset *new_hashset (void) {
   hashset *this = malloc (sizeof (struct hashset));
   assert (this != NULL);
   this->size = HASH_NEW_SIZE;
   this->load = 0;
   size_t sizeof_chains = this->size * sizeof (hashnode *);
   this->chains = malloc (sizeof_chains);
   assert (this->chains != NULL);
   memset (this->chains, 0, sizeof_chains);
   DEBUGF ('h', "%p -> struct hashset {size = %zd, chains=%p}\n",
                this, this->size, this->chains);
   return this;
}

void double_hashset (hashset *this){
   size_t old = this->size;
   this->size = (2 * old) + 1;
   this->load = 0;
   size_t chain_size = this->size * sizeof (hashnode *);
   hashnode **chains = malloc(chain_size);
   assert(chains != NULL);
   memset(chains, 0, chain_size);
   for(size_t index = 0; index < old; index++){
      hashnode *node = this->chains[index];
      while(node != NULL){
         int hash_index = strhash(node->word) % this->size;
         hashnode *temp = malloc(sizeof(struct hashnode));
         assert(temp != NULL);
         temp->word = strdup(node->word);
         temp->link = (chains[hash_index] == NULL ? NULL :
            chains[hash_index]);
         chains[hash_index] = temp;
         free(node->word);
         hashnode *oldnode = node;
         node = node->link;
         free(oldnode); 
      }
   }
   free(this->chains);
   this->chains = chains;
}

void free_hashset (hashset *this) {
   //DEBUGF ('h', "free (%p)\n", this);
   for(size_t index = 0; index < this->size; index++) {
      hashnode *head = NULL;
      head = this->chains[index];
      while(head != NULL){
         hashnode *temp = NULL;
         temp = head;
         head = head->link;
         free(temp->word);
         free(temp);
      }
   }
   free(this->chains);
   free(this);
}

void put_hashset (hashset *this, const char *item) {
   //STUBPRINTF ("hashset=%p, item=%s\n", this, item);
   if(this->load * 2 > this->size) double_hashset(this);
   int hash_index = strhash (item) % this->size;
   hashnode *head = this->chains[hash_index];

   if(has_hashset(this,item)) return;
   hashnode *temp = malloc(sizeof(struct hashnode));\
   assert(temp != NULL);
   temp->word = strdup(item);
   assert(temp->word != NULL);
   temp->link = (head == NULL ? NULL : this->chains[hash_index]);
   this->chains[hash_index] = temp;
   this->load++;
}

bool has_hashset (hashset *this, const char *item) {
   //STUBPRINTF ("hashset=%p, item=%s\n", this, item);
   int hash_index = strhash (item) % this->size;
   hashnode *node = NULL;
   for(node = this->chains[hash_index]; node != NULL;
         node = node->link) {
      if(strcmp(node->word, item) == 0) return true;
   }
   return false;
}

void print_hash(hashset *this) {
   size_t array[this->size];
   memset(array, 0, this->size * sizeof(size_t));
   printf("%5zd words in the hash set\n", this->load);
   printf("%5zd size of the hash array\n", this->size);
   for(size_t index = 0; index < this->size; index++) {
      hashnode *node = this->chains[index];
      size_t length = 0;
      while(node != NULL){
         length++;
         node = node->link;
      }
      if(length > 0) array[length]++;
   }
   for(size_t index = 0; index < this->size; index++){
      if(array[index] != 0)
         printf("%5zd chains of size %5zd\n", array[index], index);
   }
}

bool overload_hashset(hashset *this) {
   return this->load * 2 > this->size;
}

void dump_hash(hashset *this){
   for(size_t index = 0; index < this->size;index++){
      hashnode *node = this->chains[index];
      int count = 0;
      while(node != NULL) {
         if(count == 0){
            printf("array[%10zd] = %20lu \"%s\"\n",
               index, strhash(node->word), node->word);
         }else{
            printf("                  = %20lu \"%s\"\n",
               strhash(node->word), node->word);
            node = node->link;
            count++;
         }
      }
   }
}

// $Id: bigint.c,v 1.11 2016-03-01 03:55:59-08 - - $
// Michael Quan midquan

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigint.h"
#include "debug.h"

#define MIN_CAPACITY 16

struct bigint {
   size_t capacity;
   size_t size;
   bool negative;
   char *digits;
};

void trim_zeros (bigint *this) {
   while (this->size > 0) {
      size_t digitpos = this->size - 1;
      if (this->digits[digitpos] != 0) break;
      --this->size;
   }
}

bigint *new_bigint (size_t capacity) {
   bigint *this = malloc (sizeof (bigint));
   assert (this != NULL);
   this->capacity = capacity;
   this->size = 0;
   this->negative = false;
   this->digits = calloc (this->capacity, sizeof (char));
   assert (this->digits != NULL);
   DEBUGS ('b', show_bigint (this));
   return this;
}


bigint *new_string_bigint (const char *string) {
   assert (string != NULL);
   size_t length = strlen (string);
   bigint *this = new_bigint (length > MIN_CAPACITY
                            ? length : MIN_CAPACITY);
   const char *strdigit = &string[length - 1];
   if (*string == '_') {
      this->negative = true;
      ++string;
   }
   char *thisdigit = this->digits;
   while (strdigit >= string) {
      assert (isdigit (*strdigit));
      *thisdigit++ = *strdigit-- - '0';
   }
   this->size = thisdigit - this->digits;
   trim_zeros (this);
   DEBUGS ('b', show_bigint (this));
   return this;
}

bigint *do_add (bigint *this, bigint *that) {
   bigint *result = new_bigint((this->size > that-> size ?
      this->capacity : that->capacity) + 1 );
   result->size = result->capacity;

   int carry = 0;
   int digit = 0;
   for(size_t index = 0; index < result->capacity; ++index){
      digit = carry;
      if(index < this->capacity) digit += this->digits[index];
      if(index < that->capacity) digit += that->digits[index];
      result->digits[index] = digit % 10;
      carry = digit / 10;
   }
   trim_zeros(result);
   DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   return result;
}

bigint *do_sub (bigint *this, bigint *that) {
   bigint *result = new_bigint(this->capacity);
   
   int borrow = 0;
   int digit = 0;
   for(size_t index = 0; index < result->capacity; ++index){
      digit = this->digits[index] - borrow + 10;
      if(index < that->capacity) digit = digit - that->digits[index];
      result->digits[index] = digit % 10;
      borrow = 1 - digit / 10;
   }
   trim_zeros(result);
   result->size = this->size;
   DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   return result;
}

void free_bigint (bigint *this) {
   free (this->digits);
   free (this);
}

static bool do_compare(bigint *this, bigint *that){
   if(this->size > that->size) return true;
   else if(that->size > this->size) return false;
   else if(this->size == that->size){
      for(int i = this->size; i >= 0; i++){
         if(this->digits[i] > that->digits[i]) return true;
         if(this->digits[i] < that->digits[i]) return false;
      }
   }
   return true;
}

void print_bigint (bigint *this) {
   if(this->negative) printf("-");
   for(char *byte = &this->digits[this->size -1];
      byte >= this->digits; --byte){
      printf("%d", *byte);
   }
   printf("\n");
   DEBUGS ('b', show_bigint (this));
}

bigint *add_bigint (bigint *this, bigint *that) {
   DEBUGS('b', show_bigint(this));
   DEBUGS('b', show_bigint(that));
   bigint *result = NULL;

   if(this->negative == that->negative){
      result = do_add(this,that);
      result->negative = this->negative;   
   }else {
      bool comp = do_compare(this,that);
      if(comp == true) {
         result = do_sub(this, that);
         result->negative = this->negative;
      }else {
         result = do_sub(that,this);
         result->negative = that->negative;
      }
   } 
   
   return result;
}

bigint *sub_bigint (bigint *this, bigint *that) {
   DEBUGS('b', show_bigint(this));
   DEBUGS('b', show_bigint(that));

   bigint *result = NULL;

   if(this->negative != that->negative){
      result = do_add(this,that);
      result->negative = this->negative;
   }else {
      bool comp = do_compare(this,that);
      if(comp == true) {
         result = do_sub(this,that);
         result->negative = this->negative;
      }else{
         result = do_sub(that,this);
         result->negative = !that->negative;
      }
   }
   return result;
}


bigint *mul_bigint (bigint *this, bigint *that) {
   //DEBUGS ('b', show_bigint (this));
   //DEBUGS ('b', show_bigint (that));
   bigint *result = new_bigint(this->capacity + that->capacity);

   result->size = result->capacity;
   result->negative = (this->negative != that->negative ? true : false);
   for(size_t index = 0; index < this->capacity; ++index){
      int carry = 0;
      for(size_t jdex = 0; jdex < that->capacity; ++jdex){
         int digit = result->digits[index + jdex] + this->digits[index]
            * that->digits[jdex] + carry;
         result->digits[index + jdex] = digit % 10;
         carry = digit / 10;         
      }
      result->digits[index + that->size] = carry;
   }
   trim_zeros(result);
   return result;
   //STUB (return NULL);
   //return NULL;
}

void show_bigint (bigint *this) {
   fprintf (stderr, "bigint@%p->{%lu,%lu,%c,%p->", this,
            this->capacity, this->size, this->negative ? '-' : '+',
            this->digits);
   for (char *byte = &this->digits[this->size - 1];
        byte >= this->digits; --byte) {
      fprintf (stderr, "%d", *byte);
   }
   fprintf (stderr, "}\n");
}

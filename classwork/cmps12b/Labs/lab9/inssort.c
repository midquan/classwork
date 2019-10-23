// $Id: inssort.c,v 1.2 2016-03-10 05:28:59-08 - - $
// Michael Quan midquan

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "inssort.h"

void inssort(void *base, size_t nelem, size_t size,
            int (compar) (const void*, const void*)) {
   for(size_t sorted = 1; sorted < nelem; ++sorted){
      size_t slot = sorted;
      void *element = malloc(size);
      assert(element != NULL);
      memcpy(element, base + sorted * size, size);
      for(; slot > 0; slot--){
         void* piece = (char*)base + (slot - 1) * size;
         void* item = (char*)base + slot * size;
         int cmp = compar(element, piece);
         if (cmp > 0) break;
         memcpy(item, piece, size);
      }
      void* item = (char*)base + slot * size;
      memcpy(item, element, size);
      free(element);
   }
}

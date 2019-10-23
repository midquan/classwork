// $Id: inssort.h,v 1.2 2016-03-10 04:05:03-08 - - $
// Michael Quan midquan

#ifndef _INSSORT_H_
#define _INSSORT_H_

#include <stdlib.h>
#include <stdio.h>

void inssort (void* base, size_t nelem, size_t size,
         int(*compar) (const void*, const void*));

#endif

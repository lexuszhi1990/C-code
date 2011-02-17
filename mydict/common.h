#ifndef COMMON_H_
#define COMMON_H_

#include "dict_item.h"
#include "dict.h"
#include "err.h"

#define TRUE 1
#define FALSE 0

#define BUF_SIZE 4096 
#define WLEN 1024

#ifdef DEBUG
#define DEBUG_PRINT0(arg0) printf(arg0)
#else
#define DEBUG_PRINT0(arg0)
#endif

#endif

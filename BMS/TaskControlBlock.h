#ifndef _TASKCONTROLBLOCK_H
#define _TASKCONTROLBLOCK_H

#include <stdlib.h>

/* This struct represents a task control block (TCB)  
 *TCB encapsulates task function and data
 *This piece of code was provided in Lab 02.*/
typedef struct taskControlBlock {
    void (*task)(void*);
    void* taskDataPtr;
    struct taskControlBlock* next;
    struct taskControlBlock* prev;
} TCB;

#endif    // _TASKCONTROLBLOCK_H

//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef FREE_H
#define FREE_H

#include "Type.h"

class Used;

class Free
{
public:
    // ---------------------------------------------------------
    // Do not reorder, change or add data fields
    //     --> any changes to the data... 0 given to the assignment
    // You can add methods if you wish
    // ---------------------------------------------------------

    uint16_t   mAllocSize;    // size (16 bit)
    Type       mType;         // Type type 
    bool       bAboveFree;    // Type above is free (T/F)
    Free       *pNext;        // next free Type
    Free       *pPrev;        // prev free Type                              
               
    Free() = default;
    Free(const Free&) = delete;
    Free& operator = (const Free&) = delete;
    ~Free() = default;

    Free(uint32_t blockSize);
};

#endif 

// --- End of File ---

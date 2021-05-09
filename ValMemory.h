#pragma once
// ValMemory.h 
/*
proposed solution to New'd variables getting destroyed when the thread they were created in closes.
in this header, we create a tripple linkedlist struct with void* handle and short(or BYTE) type
include a number of defines or globals for type for each recycled type.
have a start/end pool for each nessesary type ->freshqueue
have a len var for each pool
constructor creates and 0's a number of each type and fills each pool
a start/end pool for recycled variables ->recycqueue
 -funciton to reset some recycled vars and append the recycled to end of the appropriate freshqueue by type

globalscope resetter functions, fill an array of function pointers for these for each type.


**/
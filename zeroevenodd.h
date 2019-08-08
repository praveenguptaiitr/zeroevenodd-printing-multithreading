#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "zeroevenodddef.h"

typedef struct {
    int n;
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n);
void zeroEvenOddFree(ZeroEvenOdd* obj);
void zero(ZeroEvenOdd* obj);
void even(ZeroEvenOdd* obj);
void odd(ZeroEvenOdd* obj);

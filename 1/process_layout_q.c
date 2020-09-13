#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];            /* 1. Uninitialized data segment(BSS)  */
int primes[] = { 2, 3, 5, 7 };  /* 2. Initialized data segment */

static int
square(int x)                   /* 3. text segment */
{
    int result;                 /* 4. stack  */

    result = x * x;
    return result;              /* 5. by register eax */
}

static void
doCalc(int val)                 /* 6. text segment */
{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000) {
        int t;                  /* 7. stack  */

        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int main(int argc, char* argv[])    /* 8  text segment */
{
    static int key = 9973;      /*9  Initialized data segment */
    static char mbuf[10240000]; /*10 Uninitialized data segment(BSS)  */
    char* p;                    /*11 No space allocation */
    doCalc(key);
    exit(EXIT_SUCCESS);
}
#include <stdio.h>
#include <string.h>
/*
Each new term in the Fibonacci sequence is generated by adding the previous two 
terms. By starting with 1 and 2, the first 10 terms will be:

1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

Find the sum of all the even-valued terms in the sequence which do not exceed 
four million.
*/

//#define MAX_VAL 90
#define MAX_VAL 4000000

int main(int argc, char **argv)
{
    unsigned int total = 2;
    unsigned int prev1 = 1, prev2 = 2;
    unsigned int next;
    
    printf("2 ");
    while (1)
    {
        next = prev1 + prev2;
        if (next > MAX_VAL)
            break;
        if ((next & 0x01) == 0)
        {
            printf("%d ", next);
            total += next;
        }
        prev1 = prev2;
        prev2 = next;
    }
    printf("\n%d\n", total);
    
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * A permutation is an ordered arrangement of objects. For example, 3124 is
 * one possible permutation of the digits 1, 2, 3 and 4. If all of the
 * permutations are listed numerically or alphabetically, we call it
 * lexicographic order. The lexicographic permutations of 0, 1 and 2 are:
 *
 * 012   021   102   120   201   210
 *
 * What is the millionth lexicographic permutation of the digits 0, 1, 2, 3,
 * 4, 5, 6, 7, 8 and 9?
 *
 */

void recursivePermutation(int *counter, char *numberPool, char *result)
{
    int len = strlen(result);
    if (len == 10)
    {
        *counter = *counter - 1;
        if (*counter <= 0)
            printf("%s : %d\n", result, *counter);
    }
    if (*counter == 0) // short-circuit out
        return;
    for (int i = 0; i< 10; i++)
        if (*(numberPool + i) == 1)
        {
            result[len] = i + '0';
            result[len + 1] = '\0';
            *(numberPool + i) = 0;
            recursivePermutation(counter, numberPool, result);
            *(numberPool + i) = 1;
            result[len] = '\0';
            if (*counter == 0) // short-circuit out
                return;
        }
}

int main(int argc, char **argv)
{
    int counter;
    char numberPool[10];
    char result [11];
    printf("Calculating permutation 1\n");
    memset(numberPool, 1, sizeof(numberPool));
    memset(result, 0, sizeof(result));
    counter = 1;
    recursivePermutation(&counter, numberPool, result);
    printf("Calculating permutation 2\n");
    memset(numberPool, 1, sizeof(numberPool));
    memset(result, 0, sizeof(result));
    counter = 2;
    recursivePermutation(&counter, numberPool, result);
    printf("Calculating permutation 1000000\n");
    memset(numberPool, 1, sizeof(numberPool));
    memset(result, 0, sizeof(result));
    counter = 1000000;
    recursivePermutation(&counter, numberPool, result);
}

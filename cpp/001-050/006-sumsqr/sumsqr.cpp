#include <stdio.h>
#include <string.h>

/*
The sum of the squares of the first ten natural numbers is,
1^2 + 2^2 + ... + 10^2 = 385

The square of the sum of the first ten natural numbers is,
(1 + 2 + ... + 10)^2 = 55^2 = 3025

Hence the difference between the sum of the squares of the first ten natural 
numbers and the square of the sum is 3025 - 385 = 2640.

Find the difference between the sum of the squares of the first one hundred 
natural numbers and the square of the sum.
*/

//#define MAX_VAL 10
#define MAX_VAL 100

unsigned int sumOfSquares(unsigned int number)
{
    unsigned int result = 0;
    for (int i = 1; i <= number; i++)
        result += i * i;
    return result;
}

unsigned int squareOfSums(unsigned int number)
{
    unsigned int result = 0;
    for (int i = 1; i <= number; i++)
        result += i;
    result = result * result;
    return result;
}

int main(int argc, char **argv)
{
    unsigned int v1, v2, result;
    v1 = sumOfSquares(MAX_VAL);
    v2 = squareOfSums(MAX_VAL);
    result = v2 - v1;
    printf("sumOfSquares(%d) == %d\n", MAX_VAL, v1);
    printf("squareOfSums(%d) == %d\n", MAX_VAL, v2);
    printf("result == %d\n", result);
    return 0;
}

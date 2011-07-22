#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
/*
Let d(n) be defined as the sum of proper divisors of n (numbers less than n 
which divide evenly into n).
If d(a) = b and d(b) = a, where a b, then a and b are an amicable pair and 
each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 
55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 
71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
*/

unsigned int sumOfDivisors(unsigned int number)
{
    unsigned int result = 0;
    unsigned int max = number / 2;
    for (int i = 1; i<= max; i++)
        if ((number % i) == 0)
            result += i;
    return result;
}

int main(int argc, char **argv)
{
    unsigned int result = 0;
    printf("220 -> %d\n", sumOfDivisors(220));
    printf("284 -> %d\n", sumOfDivisors(284));
    for (int i = 0; i < 10000; i++)
    {
        unsigned int rv = sumOfDivisors(i);
        if (sumOfDivisors(rv) == i)
        {
            if (i < rv)
                result += i + rv;
        }
    }
    printf("%d\n", result);
    return 0;
}

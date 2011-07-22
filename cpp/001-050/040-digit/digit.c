#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
//#include <gmp.h>
/*
 * An irrational decimal fraction is created by concatenating the positive
 * integers:
 *
 * 0.123456789101112131415161718192021...
 *
 * It can be seen that the 12^(th) digit of the fractional part is 1.
 *
 * If d_(n) represents the n^(th) digit of the fractional part, find the value
 * of the following expression.
 *
 * d_(1) x d_(10) x d_(100) x d_(1000) x d_(10000) x d_(100000) x d_(1000000)
 */

static inline int numberLength(unsigned int n)
{
    if (n <= 9)                 return 1;
    else if (n <= 99)           return 2;
    else if (n <= 999)          return 3;
    else if (n <= 9999)         return 4;
    else if (n <= 99999)        return 5;
    else if (n <= 999999)       return 6;
    else if (n <= 9999999)      return 7;
    else return -1000; //  this should get someone's attention
}

// Note for future enhancement: This could be more efficient if it saved its
// spot and resumed if you gave it progressively larger position arguments.
char getDigit(unsigned int position)
{
    unsigned int currentPosition = 0;
    unsigned int value = 0;
    int length;
    char buffer[10];
    while (1)
    {
        length = numberLength(value);
        if (length <= 0)
            return -1;
        if ((position >= currentPosition) && (position < currentPosition + length))
            break;
        value++;
        currentPosition += length;
    }
    sprintf(buffer, "%d", value);
    return buffer[position - currentPosition] - '0';
}

void test()
{
    for (unsigned int i = 1; i <= 18; i++)
        printf("%s%d", i > 1 ? "," : "", getDigit(i));
    printf("\n");
}

int main(int argc, char **argv)
{
    unsigned int sum = 1;
    test();
    for (unsigned int d = 1; d <= 1000000; d *= 10)
        sum *= getDigit(d);
    printf("%d\n", sum);
    return 0;
}

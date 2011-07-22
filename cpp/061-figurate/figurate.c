#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Triangle, square, pentagonal, hexagonal, heptagonal, and octagonal numbers
 * are all figurate (polygonal) numbers and are generated by the following
 * formulae:
 * Triangle        P_(3,n)=n(n+1)/2        1, 3, 6, 10, 15, ...
 * Square      P_(4,n)=n^(2)       1, 4, 9, 16, 25, ...
 * Pentagonal      P_(5,n)=n(3n-1)/2       1, 5, 12, 22, 35, ...
 * Hexagonal       P_(6,n)=n(2n-1)         1, 6, 15, 28, 45, ...
 * Heptagonal      P_(7,n)=n(5n-3)/2       1, 7, 18, 34, 55, ...
 * Octagonal       P_(8,n)=n(3n-2)         1, 8, 21, 40, 65, ...
 *
 * The ordered set of three 4-digit numbers: 8128, 2882, 8281, has three
 * interesting properties.
 *
 * 1. The set is cyclic, in that the last two digits of each number is the
 * first two digits of the next number (including the last number with the
 * first).
 * 2. Each polygonal type: triangle (P_(3,127)=8128), square (P_(4,91)=8281),
 * and pentagonal (P_(5,44)=2882), is represented by a different number in the
 * set.
 * 3. This is the only set of 4-digit numbers with this property.
 *
 * Find the sum of the only ordered set of six cyclic 4-digit numbers for which
 * each polygonal type: triangle, square, pentagonal, hexagonal, heptagonal,
 * and octagonal, is represented by a different number in the set.
 */
#define ARRAY_SIZE 142 // just enough size so we can get all 4-digit numbers of each type
unsigned int poly[9][ARRAY_SIZE];

unsigned int triangle(unsigned int n) {return (n * (n + 1)) / 2;}
unsigned int square(unsigned int n) {return n * n;}
unsigned int pentagonal(unsigned int n) {return (n * ((3 * n) - 1)) / 2;}
unsigned int hexagonal(unsigned int n) {return n * ((2 * n) - 1);}
unsigned int heptagonal(unsigned int n) {return (n * ((5 * n) - 3)) / 2;}
unsigned int octagonal(unsigned int n) {return n * ((3 * n) - 2);}

void fillArrays()
{
    memset(poly, 0, sizeof(poly));
    for (unsigned int i = 1; i < ARRAY_SIZE; i++)
    {
        poly[3][i] = triangle(i);
        poly[4][i] = square(i);
        poly[5][i] = pentagonal(i);
        poly[6][i] = hexagonal(i);
        poly[7][i] = heptagonal(i);
        poly[8][i] = octagonal(i);
    }
#if 0
    for (int i = 1; i < 6; i++)
        printf("%5d %5d %5d %5d %5d %5d\n", poly[3][i], poly[4][i], poly[5][i], poly[6][i], poly[7][i], poly[8][i]);
    printf("High numbers are %d %d %d %d %d %d\n",
            poly[3][ARRAY_SIZE - 1], poly[4][ARRAY_SIZE - 1], poly[5][ARRAY_SIZE - 1],
            poly[6][ARRAY_SIZE - 1], poly[7][ARRAY_SIZE - 1], poly[8][ARRAY_SIZE - 1]);
#endif
    // trim out non-4-digit numbers
    for (int i = 0; i < ARRAY_SIZE; i++)
        for (int j = 3; j <= 8; j++)
            if ((poly[j][i] < 1000) || (poly[j][i] > 9999))
                poly[j][i] = 0;
}

unsigned int isReallyCyclic(unsigned int *set, unsigned int length)
{
    if ((*set / 100) == *(set + length) % 100)
        return 1;
    return 0;
}

void findCycle(unsigned int *set, unsigned int currentLength, unsigned int maxLength, unsigned char *listsUsed)
{
    int firstDigits = -1;
    if (currentLength >= maxLength)
    {
        unsigned int sum = 0;
        if (!isReallyCyclic(set, currentLength - 1))
            return;
        printf("Possible Match: ");
        for (int i = 0; i < maxLength; i++)
        {
            printf("%d ", *(set + i));
            sum += *(set + i);
        }
        printf("= %d\n", sum);
        return;
    }
    if (currentLength > 0)
    {
        firstDigits = *(set + currentLength - 1) % 100;
        if (firstDigits == 0)
            return;
    }
    for (int list = 3; list < 3 + maxLength; list++)
    {
        // Already pulled a number from this list
        if (*(listsUsed + list) != 0)
            continue;
#if 0
        printf("At depth %d, list %d, lists ", currentLength, list);
        for (int i = 3; i <= 8; i++)
            printf("%c", *(listsUsed + i) ? '1' : '0');
        printf("\n");
#endif
        *(listsUsed + list) = 1;
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            unsigned char possibleMatch = 0;
            if ((firstDigits == -1) && (poly[list][i] != 0))
                possibleMatch = 1;
            if ((firstDigits != -1) && ((poly[list][i] / 100) == firstDigits))
                possibleMatch = 1;
            if (possibleMatch)
            {
                *(set + currentLength) = poly[list][i];
#if 0
                printf("Recursing at length %d list %d, lists ", currentLength, list);
                for (int i = 3; i <= 8; i++)
                    printf("%c", *(listsUsed + i) ? '1' : '0');
                printf(": ");
                for (int i = 0; i < currentLength; i++)
                    printf("%d ", *(set + i));
                printf("\n");
#endif
                findCycle(set, currentLength + 1, maxLength, listsUsed);
                *(set + currentLength) = 0;
            }
        }
        *(listsUsed + list) = 0;
    }
#if 0
    printf("Fell out of loop at length %d, lists ", currentLength, 3, 3 + maxLength);
    for (int i = 3; i <= 8; i++)
        printf("%c", *(listsUsed + i) ? '1' : '0');
    printf("\n");
#endif
}

int main(int argc, char **argv)
{
    unsigned int set[6];
    unsigned char listsUsed[9];
    fillArrays();
    memset(listsUsed, 0, sizeof(listsUsed));
    //findCycle(set, 0, 3, listsUsed);
    findCycle(set, 0, 6, listsUsed);
    return 0;
}

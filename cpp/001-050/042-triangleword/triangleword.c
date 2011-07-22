#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
#include <ctype.h>
//#include <gmp.h>
/*
 * The n^(th) term of the sequence of triangle numbers is given by,
 * t_(n) =  1/2 n(n+1); so the first ten triangle numbers are:
 *
 * 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
 *
 * By converting each letter in a word to a number corresponding to its
 * alphabetical position and adding these values we form a word value. For
 * example, the word value for SKY is 19 + 11 + 25 = 55 = t_(10). If the word
 * value is a triangle number then we shall call the word a triangle word.
 *
 * Using words.txt (right click and 'Save Link/Target As...'), a 16K text file
 * containing nearly two-thousand common English words, how many are triangle
 * words?
 *
 */

#define TABLE_SIZE 256
unsigned int triangleNumberTable[TABLE_SIZE];
unsigned int biggestTriangleNumber;

unsigned int triangleNumber(int i)
{
    return (i * (i + 1)) / 2;
}

void buildTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        triangleNumberTable[i] = triangleNumber(i + 1);
        printf("%d ", triangleNumberTable[i]);
    }
    printf("\n");
    biggestTriangleNumber = triangleNumberTable[TABLE_SIZE - 1];
}

int isTriangleWord(const char *s)
{
    const char *originalWord = s;
    unsigned int sum = 0;
    while (*s)
    {
        if (!isalpha(*s))
        {
            printf("Bad character: %c\n", *s);
            return -1;
        }
        sum += toupper(*s) - 'A' + 1;
        s++;
    }
    printf("Sum for %s is %d\n", originalWord, sum);
    for (int i = 0; (i < TABLE_SIZE) && (sum >= triangleNumberTable[i]); i++)
        if (sum == triangleNumberTable[i])
            return 1;
    if (sum > biggestTriangleNumber)
    {
        printf("Triangle number too big: %s has value of %d, bigger than biggest table entry of %d\n", originalWord, sum, biggestTriangleNumber);
        return -1;
    }
    return 0;
}

void test()
{
    printf("SKY:%d\n", isTriangleWord("SKY"));
}

void processFile()
{
    char buffer[256] = "";
    char *s = &buffer[0];
    unsigned int hitCount = 0;
    FILE *f = fopen("words.txt", "r");
    while (!feof(f))
    {
        int c = fgetc(f);
        if (!isalpha(c))
        {
            *s++ = '\0';
            if (buffer[0])
                if (isTriangleWord(buffer))
                {
                    printf("%s\n", buffer);
                    hitCount++;
                }
            buffer[0] = 0;
            s = &buffer[0];
        } else {
            *s++ = c;
            //printf("(%s)\n", buffer);
        }
    }
    fclose(f);
    printf("%d\n", hitCount);
}

int main(int argc, char **argv)
{
    buildTable();
    test();
    processFile();
    return 0;
}

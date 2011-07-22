#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//#include <ctype.h>
//#include <gmp.h>
/*
 *
 */

int isPrime_ui(unsigned int value)
{
    unsigned int max;
    // Fail by definition (prime has to be > 1)
    if (value <= 1)
        return 0;
    if (value == 2)
        return 1;
    // Check if prime
    max = sqrt(value) + 1;
    for (unsigned int i = 2; i <= max; i++)
        if ((value % i) ==  0)
            return 0;
    return 1;
}

int matchCount;
unsigned int matches[10];
void resetCheckPrimeCallback()
{
    matchCount = 0;
}

void checkPrimeCallback(char *s)
{
    unsigned int i = atoi(s);
    if (matchCount >= 10)
        return;
    if ((i >= 1000) && isPrime_ui(i))
    {
        for (int j = 0; j < matchCount; j++)
            if (matches[j] == i)
                return;
        matches[matchCount++] = i;
    }
}

int inList(unsigned int num) {
    for (int i = 0; i < matchCount; i++)
        if (matches[i] == num)
            return 1;
    return 0;
}

int checkIncreasing() {
    // Yeay, bubble sort!  Fortunately this only gets called if there's a pretty close match.  This is the last check.
    for (int i = 0; i < matchCount; i++)
        for (int j = 0; j < matchCount; j++)
            if (matches[j] > matches[i])
            {
                unsigned int temp = matches[j];
                matches[j] = matches[i];
                matches[i] = temp;
            }
    // TODO: check for increasing terms
    // TODO: if match, migrate them to matches[0]..matches[2]
    for (int first = 1; first < matchCount; first++)
    {
        for (int second = first + 1; second < matchCount; second++)
        {
            unsigned int distance = matches[second] - matches[first];
            //printf("Distance is %d\n", distance);
            for (int j = 0; j < matchCount; j++)
                if (inList(matches[j] + distance) && inList(matches[j] + 2 * distance))
                {
                    printf("FOUND!\n");
                    matches[0] = matches[j];
                    matches[1] = matches[0] + distance;
                    matches[2] = matches[0] + 2 * distance;
                    return 1;
                }
        }
    }
    return 0;
}

void printCallback(char *s)
{
    printf("%s\n", s);
}

int doPermutations(char *charset, int charsetLength, char depth, char *buffer, void (*callback)(char *))
{
    char *bufferEnd = buffer + strlen(buffer);
    if (depth == 0)
    {
        callback(buffer);
    }
    for (int i = 0; i < charsetLength; i++)
    {
        if (*(charset + i) != 0)
        {
            char c = *(charset + i);
            *(charset + i) = 0;
            *bufferEnd = c;
            *(bufferEnd + 1) = '\0';
            doPermutations(charset, charsetLength, depth - 1, buffer, callback);
            *bufferEnd = '\0';
            *(charset + i) = c;
        }
    }
    return 0;
}

void test()
{
    char charset[3] = {'A','B','C'};
    char buffer[10];
    buffer[0] = 0;
    doPermutations(charset, 3, 2, buffer, printCallback);
    buffer[0] = 0;
    doPermutations(charset, 3, 3, buffer, printCallback);
}

void test2()
{
    matches[0] = 1487;
    matches[1] = 1847;
    matches[2] = 4817;
    matches[3] = 4871;
    matches[4] = 8147;
    matches[5] = 8741;
    matches[6] = 7481;
    matches[7] = 7841;
    matchCount = 8;
    checkIncreasing();
    exit(0);
}

int main(int argc, char **argv)
{
    char charset[10];
    char buffer[10];
    //test();
    //test2();
    for (unsigned int i = 1000; i <= 9999; i++)
        if (isPrime_ui(i))
        {
            if (i == 1487)
                printf("XXX ");
            sprintf(charset, "%d", i);
            buffer[0] = 0;
            resetCheckPrimeCallback();
            matches[matchCount++] = i;
            doPermutations(charset, 4, 4, buffer, checkPrimeCallback);
            if (i == 1487)
            {
                printf("XXX %d\n", matchCount);
                for (int i = 0; i < matchCount; i++)
                    printf("%d ", matches[i]);
                printf("\n");
            }
            //if (matchCount == 3)
                if (checkIncreasing())
                    printf("%d %d %d\n", matches[0], matches[1], matches[2]);
        }
    return 0;
}

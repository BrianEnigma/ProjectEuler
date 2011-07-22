#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>

/* The cube, 41063625 (345^(3)), can be permuted to produce two other cubes:
 * 56623104 (384^(3)) and 66430125 (405^(3)). In fact, 41063625 is the smallest
 * cube which has exactly three permutations of its digits which are also cube.
 *
 * Find the smallest cube for which exactly five permutations of its digits
 * are cube.
 */

int matchCounter;
mpz_t matchList[10];
int matchListLength;
unsigned char initialized = 0;

#define CUBE_LIST_LENGTH 10000
mpz_t cubeList[CUBE_LIST_LENGTH];

void fillCubeList()
{
    for (int i = 0; i < CUBE_LIST_LENGTH; i++)
    {
        mpz_init(cubeList[i]);
        mpz_ui_pow_ui(cubeList[i], i, 3);
    }
}

unsigned char isCube(mpz_t value)
{
    int bottom = 1;
    int top = CUBE_LIST_LENGTH - 1;
    if (mpz_cmp(value, cubeList[top]) > 0)
    {
        printf("ERROR: Past end of list of cubes!\n");
        mpz_out_str(stdout, 10, value); printf("\n");
        mpz_out_str(stdout, 10, cubeList[top]); printf("\n");
        exit(1);
    }
    while (bottom <= top)
    {
        int middle = (top - bottom) / 2 + bottom;
        int diff = mpz_cmp(cubeList[middle], value);
        if (diff == 0)
            return 1;
        else if (diff < 0)
            bottom = middle + 1;
        else
            top = middle - 1;
    }
    return 0;
}

void resetMatchList()
{
    matchCounter = matchListLength = 0;
    for (int i = 0; i < 10; i++)
    {
        if (!initialized)
            mpz_init(matchList[i]);
        mpz_set_ui(matchList[i], 0);
    }
    initialized = 1;
}

void checkCallback(char *s)
{
    mpz_t value;
    mpz_t theRoot;
    // Number with leading zeros fails
    if (*s == '0')
        return;
    mpz_init(value);
    mpz_init(theRoot);
    mpz_set_str(value, s, 10);
    //if (mpz_root(theRoot, value, 3) != 0)
    if (isCube(value))
    {
        for (int i = 0; i < matchListLength; i++)
            if (mpz_cmp(matchList[i], value) == 0)
            {
                mpz_clear(value);
                mpz_clear(theRoot);
                return;
            }
        //printf("Match: %s\n", s);
        matchCounter++;
        mpz_set(matchList[matchListLength], value);
        matchListLength++;
    }
    mpz_clear(value);
    mpz_clear(theRoot);
}

static int doPermutations(char *charset, int charsetLength, char depth, char *buffer, void (*callback)(char *))
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

int test()
{
    char buffer[80] = "";
    char *s;
    mpz_t value;
    mpz_init(value);
    mpz_ui_pow_ui(value, 345, 3);
    s = mpz_get_str(NULL, 10, value);
    resetMatchList();
    doPermutations(s, strlen(s), strlen(s), buffer, checkCallback);
    printf("Number %d has cube %s and %d matching permutation(s)\n", 345, s, matchCounter);
    free(s);
}

int main(int argc, char **argv)
{
    char *s;
    char buffer[80] = "";
    mpz_t value;
    mpz_init(value);
    fillCubeList();
    //return test();
    //for (int i = 2694; i < 3000; i++)
    for (int i = 4; i < 5000; i++)
    {
        mpz_ui_pow_ui(value, i, 3);
        s = mpz_get_str(NULL, 10, value);
        resetMatchList();
        memset(buffer, 0, sizeof(buffer));
        doPermutations(s, strlen(s), strlen(s), buffer, checkCallback);
        if (matchCounter > 1)
            printf("Number %d has cube %s and %d matching permutation(s)\n", i, s, matchCounter);
        free(s);
        if (matchCounter >= 4)
            break;
    }
    return 0;
}

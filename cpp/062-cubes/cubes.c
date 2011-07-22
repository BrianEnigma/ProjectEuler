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

#define CUBE_LIST_LENGTH 20000
char *cubeList[CUBE_LIST_LENGTH];
mpz_t lastCube;

void sortDigits(char *s)
{
    for (char *i = s; *i; i++)
        for (char *j = i; *j; j++)
            if (*i < *j)
            {
                char temp = *i;
                *i = *j;
                *j = temp;
            }
}

void fillCubeList()
{
    mpz_t number;
    mpz_init(number);
    for (int i = 0; i < CUBE_LIST_LENGTH; i++)
    {
        mpz_ui_pow_ui(number, i, 3);
        cubeList[i] = mpz_get_str(NULL, 10, number);
        sortDigits(cubeList[i]);
    }
    mpz_clear(number);
    mpz_init(lastCube);
    mpz_ui_pow_ui(lastCube, CUBE_LIST_LENGTH - 1, 3);
}

unsigned int cubeMatches(unsigned int baseValue, mpz_t value, unsigned int *sum)
{
    unsigned int result = 0;
    char *s = mpz_get_str(NULL, 10, value);
    int len = strlen(s);
    *sum = 0;
    if (mpz_cmp(value, lastCube) > 0)
    {
        printf("ERROR: Past end of list of cubes!\n");
        exit(1);
    }
    sortDigits(s);
    for (int position = 0; position < CUBE_LIST_LENGTH; position++)
    {
        int comp = strcmp(s, cubeList[position]);
        if (position == baseValue)
            continue;
        //printf("%3d : %d : %s : %s\n", comp, position, s, cubeList[position]);
        if (comp == 0) // perfect match
        {
            result++;
            *sum += position;
        }
        // Too far in list
        if (strlen(cubeList[position]) > len)
            break;
    }
    free(s);
    return result;
}

int test()
{
    unsigned int matches, sum;
    mpz_t value;
    mpz_init(value);
    mpz_ui_pow_ui(value, 345, 3);
    matches = cubeMatches(345, value, &sum);
    printf("Number %d has %d matching permutation(s), summing %d\n", 345, matches, sum);
    return 0;
}

int main(int argc, char **argv)
{
    unsigned int matches, sum;
    mpz_t value;
    mpz_init(value);
    fillCubeList();
    test();
    //return test();
    for (int i = 4; i < 20000; i++)
    {
        mpz_ui_pow_ui(value, i, 3);
        matches = cubeMatches(i, value, &sum);
        if (matches > 1)
            printf("Number %d has %d matching permutation(s), summing %d\n", i, matches, sum);
        if (matches >= 5) {
            mpz_out_str(stdout, 10, value);
            printf("\n");
            break;
        }
    }
    return 0;
}

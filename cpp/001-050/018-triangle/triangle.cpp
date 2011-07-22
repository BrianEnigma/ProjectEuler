#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/*
By starting at the top of the triangle below and moving to adjacent numbers 
on the row below, the maximum total from top to bottom is 23.

   3
  7 5
 2 4 6
8 5 9 3

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom of the triangle below:

                            75
                          95 64
                        17 47 82
                      18 35 87 10
                    20 04 82 47 65
                  19 01 23 75 03 34
                88 02 77 73 07 63 67
              99 65 04 28 06 16 70 92
            41 41 26 56 83 40 80 70 33
          41 48 72 33 47 32 37 16 94 29
        53 71 44 65 25 43 91 52 97 51 14
      70 11 33 28 77 73 17 78 39 68 17 57
    91 71 52 38 17 14 91 43 58 50 27 29 48
  63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23

NOTE: As there are only 16384 routes, it is possible to solve this problem by 
trying every route. However, Problem 67, is the same challenge with a triangle 
containing one-hundred rows; it cannot be solved by brute force, and requires 
a clever method! ;o)
*/

//#define TRIANGLE_MAX_WIDTH  15
//#define TRIANGLE_MAX_HEIGHT 15
#define TRIANGLE_MAX_WIDTH  100
#define TRIANGLE_MAX_HEIGHT 100
unsigned int triangle[TRIANGLE_MAX_HEIGHT][TRIANGLE_MAX_WIDTH];

void loadFile(const char *filename)
{
    int row = 0, column = 0, value = 0;
    char line[1024];
    FILE *f = fopen(filename, "r");
    while (fgets(line, sizeof(line), f) != NULL)
    {
        printf("%s\n", line);
        value = 0;
        if (!isdigit(line[0]))
            return;
        for (char *c = line; *c; c++)
        {
            if (isdigit(*c))
            {
                value = value * 10 + *c - '0';
            } else {
                printf("%d,%d -> %d\n", row, column, value);
                triangle[row][column++] = value;
                value = 0;
                if (*c < ' ') {
                    printf("newline\n");
                    row++;
                    column = 0;
                    *c = 0;
                }
            }
        }
    }
    triangle[row][column++] = value;
}

void debugPrintArray()
{
    for (int row = 0; row < TRIANGLE_MAX_HEIGHT; row++)
    {
        for (int column = 0; column < TRIANGLE_MAX_WIDTH; column++)
            printf("%3d", triangle[row][column]);
        printf("\n");
    }
    printf("\n");
}

void bestSum(unsigned int row)
{
    for (int column = 0; column < TRIANGLE_MAX_WIDTH; column++)
    {
        if (triangle[row + 1][column] + triangle[row][column] > triangle[row + 1][column + 1] + triangle[row][column])
            triangle[row][column] += triangle[row + 1][column];
        else
            triangle[row][column] += triangle[row + 1][column + 1];
    }
}

int main(int argc, char **argv)
{
    memset(triangle, 0, sizeof(triangle));
    //loadFile("small.txt");
    //loadFile("large.txt");
    loadFile("huge.txt");
    debugPrintArray();
    for (int row = TRIANGLE_MAX_HEIGHT - 1; row >= 0; row--)
        bestSum(row);
    debugPrintArray();
    printf("%d\n", triangle[0][0]);
    return 0;
}

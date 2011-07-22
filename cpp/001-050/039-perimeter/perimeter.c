#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
//#include <gmp.h>
/*
 * If p is the perimeter of a right angle triangle with integral length
 * sides, {a,b,c}, there are exactly three solutions for p = 120.
 *
 * {20,48,52}, {24,45,51}, {30,40,50}
 *
 * For which value of p <= 1000, is the number of solutions maximised?
 */

int solutionCount(int perimeter)
{
    int result = 0;
    int lastSide;
    for (int a = 1; a < perimeter; a++)
        for (int b = 1; b < a; b++)
        {
            lastSide = a * a + b * b;
            if (((perimeter - a - b) * (perimeter - a - b)) == lastSide)
            {
                //printf(" {%d,%d,%d}", a, b, perimeter - a - b);
                result++;
            }
        }
    if (result)
        printf("%3d results for %d\n", result, perimeter);
    return result;
}

void test()
{
    solutionCount(120);
}

int main(int argc, char **argv)
{
    int maxValue = 0, maxValueCount = 0, thisValueCount = 0;
    test();
    for (int i = 3; i <= 1000; i++)
    {
        thisValueCount = solutionCount(i);
        if (thisValueCount > maxValueCount)
        {
            maxValueCount = thisValueCount;
            maxValue = i;
        }
    }
    printf("Max was %d at %d\n", maxValueCount, maxValue);
    return 0;
}

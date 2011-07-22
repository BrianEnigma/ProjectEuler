#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * Starting with the number 1 and moving to the right in a clockwise direction
 * a 5 by 5 spiral is formed as follows:
 *
 * 21 22 23 24 25
 * 20  7  8  9 10
 * 19  6  1  2 11
 * 18  5  4  3 12
 * 17 16 15 14 13
 *
 * It can be verified that the sum of both diagonals is 101.
 *
 * What is the sum of both diagonals in a 1001 by 1001 spiral formed in the same way?
 *
 */
unsigned int grid[1001][1001];

void fillGrid(int size)
{
    int counter = 1;
    int iterations = size / 2;
    int centerX = size / 2, centerY = size / 2;
    printf("size=%d, iterations=%d, centerX=%d, centerY=%d\n", size, iterations, centerX, centerY);
    memset(grid, 0, sizeof(grid));
    if ((size % 2) == 0)
    {
        printf("FAIL: need an odd number for grid size\n");
        return;
    }
    // Center square
    grid[centerX][centerY] = counter++;
    // Each circular iteration
    for (int iteration = 1; iteration <= iterations; iteration++)
    {
        // Right edge
        for (int y = 1; y <= iteration * 2; y++)
            grid[centerX + iteration][centerY - iteration + y] = counter++;
        // Bottom edge
        for (int x = 1; x <= iteration * 2; x++)
            grid[centerX + iteration - x][centerY + iteration] = counter++;
        // Left edge
        for (int y = 1; y <= iteration * 2; y++)
            grid[centerX - iteration][centerY + iteration - y] = counter++;
        // Top edge
        for (int x = 1; x <= iteration * 2; x++)
            grid[centerX - iteration + x][centerY - iteration] = counter++;
    }
}

void printGrid(FILE *f, int size)
{
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
            fprintf(f, "%05d ", grid[x][y]);
        fprintf(f, "\n");
    }
}

void calculateDiagonals(int size)
{
    unsigned int sum1 = 0, sum2 = 0;
    for (int position = 0; position < size; position++)
    {
        sum1 += grid[position][position];
        sum2 += grid[size - position - 1][position];
    }
    printf("sum1=%d sum2=%d, sum1+sum2=%d\n", sum1, sum2, sum1 + sum2 - 1 /* -1 because we don't count the center twice */);
}

int main(int argc, char **argv)
{
    const int size = 1001;
    FILE *f;
    fillGrid(size);
    f = fopen("grid.txt", "w");
    printGrid(f, size);
    fclose(f);
    calculateDiagonals(size);
    return 0;
}

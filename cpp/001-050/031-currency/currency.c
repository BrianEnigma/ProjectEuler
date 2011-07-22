#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * In England the currency is made up of pound, $, and pence, p, and there are
 * eight coins in general circulation:
 *
 *  1p, 2p, 5p, 10p, 20p, 50p, $1 (100p) and $2 (200p).
 *
 * It is possible to make $2 in the following way:
 *
 *  1x$1 + 1x50p + 2x20p + 1x5p + 1x2p + 3x1p
 *
 * How many different ways can $2 be made using any number of coins?
 *
 */

int coinCounts[8]; // count of each of 1, 2, 5, 10, 20, 50, 100, 200 in pocket
const int coinValues[8] = {200, 100, 50, 20, 10, 5, 2, 1};//{1, 2, 5, 10, 20, 50, 100, 200};
int permutationCount = 0;
#define TOTAL 200
//#define TOTAL 12

void printCoins(int *coinCounts)
{
    for (int i = 0; i < 8; i++)
        if (*(coinCounts + i))
            printf("(%dp x %d) ", coinValues[i], *(coinCounts + i));
    printf("\n");
}

int coinSum(int *coinCounts)
{
    int result = 0;
    for (int i = 0; i < 8; i++)
        result += *(coinCounts + i) * coinValues[i];
    return result;
}

int recurseCount(int *coinCounts, int nextCoin)
{
    int total = coinSum(coinCounts);
    int maxCount;
    // Fail exit condition - over $2
    if (total > TOTAL)
        return 0;
    // Success exit condition - exactly $2
    if (total == TOTAL)
    {
        permutationCount++;
        printCoins(coinCounts);
        return 0;
    }
    // Fail exit condition - out of coins
    if (nextCoin > 7)
        return 0;
    // For this coin, try all values until we exceed maximum
    maxCount = (TOTAL - total) / coinValues[nextCoin] + 1;
    //if (nextCoin == 7)
    //    printf("Total %d, Coin %dp, max %d\n", total, coinValues[nextCoin], maxCount);
    for (int i = maxCount; i >= 0; i--)
    {
        coinCounts[nextCoin] = i;
        recurseCount(coinCounts, nextCoin + 1);
    }
    return 1;
}

int main(int argc, char **argv)
{
    memset(coinCounts, 0, sizeof(coinCounts));
    recurseCount(coinCounts, 0);
    printf("%d permutations\n", permutationCount);
    return 0;
}

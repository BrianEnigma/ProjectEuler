#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>
/*
Starting in the top left corner of a 2x2 grid, there are 6 routes (without 
backtracking) to the bottom right corner.

[image here]

How many routes are there through a 20x20 grid?


"monotonic path"
See also: 
	http://en.wikipedia.org/wiki/Catalan_number
	http://mathworld.wolfram.com/CatalanNumber.html
2x2 grid has 6 paths   - nCr(4, 2)
3x3 grid has 20 paths  - nC3(6, 3)

C(n,r) = n! / r! (n - r)!
*/

//#define GRID_WIDTH      2
//#define GRID_HEIGHT     2
#define GRID_WIDTH      20
#define GRID_HEIGHT     20
#define PATH_LEN        80

bool visited[GRID_WIDTH + 1][GRID_HEIGHT + 1];
int routeCounter = 0;

void factorialBig(mpz_t result, mpz_t n)
{
	mpz_t counter;
	mpz_set_ui(result, 1);
	for (mpz_init_set(counter, n); mpz_cmp_ui(counter, 1) > 0; mpz_sub_ui(counter, counter, 1))
		mpz_mul(result, result, counter);
}

void chooseBig(mpz_t result, mpz_t n, mpz_t r)
{
	mpz_t numerator;
	mpz_t denominator;
	mpz_t clause1;
	mpz_t clause2;
	mpz_init(numerator);
	mpz_init(denominator);
	mpz_init(clause1);
	mpz_init(clause2);
	factorialBig(numerator, n);
	factorialBig(denominator, r);
	mpz_set(clause1, n);
	mpz_sub(clause1, clause1, r);
	factorialBig(clause2, clause1);
	mpz_mul(denominator, denominator, clause2);
	mpz_cdiv_q(result, numerator, denominator);
}

void chooseBig_ui(mpz_t result, unsigned int n_ui, unsigned int r_ui)
{
	mpz_t n;
	mpz_t r;
	mpz_init_set_ui(n, n_ui);
	mpz_init_set_ui(r, r_ui);
	chooseBig(result, n, r);
}

unsigned int factorial(unsigned int n)
{
	unsigned int result = 1;
	for (unsigned int i = 2; i <= n; i++)
		result *= i;
	return result;
}

unsigned int choose(unsigned int n, unsigned int r)
{
	//return factorial(n) / (factorial(r) * factorial(n - r));
	return factorial(n) / factorial(r) / factorial(n - r);
}

void recurseTraverse(int x, int y, char *path)
{
    int pathLen = strlen(path);
    if (pathLen >= PATH_LEN - 1)
    {
        printf("Path too deep\n");
        exit(1);
    }
    // Out of bounds failure
    if ((x < 0) || (y < 0) || (x > GRID_WIDTH) || (y > GRID_HEIGHT))
    {
        //printf("%s bounds\n", path);
        return;
    }
    // Backtracking failure
    if (visited[x][y]) 
    {
        //printf("%s backtrack\n", path);
        return;
    }
    // Win condition, stop traversing
    if ((x == GRID_WIDTH) && (y == GRID_HEIGHT))
    {
        //printf("%s WIN\n", path);
        routeCounter++;
        return;
    }
    // Mark visited
    visited[x][y] = true;
    // Try each of the four compass directions
    path[pathLen] = 'R'; recurseTraverse(x + 1, y, path);
    path[pathLen] = 'D'; recurseTraverse(x, y + 1, path);
    //path[pathLen] = 'L'; recurseTraverse(x - 1, y, path);
    //path[pathLen] = 'U'; recurseTraverse(x, y - 1, path);
    // Backtrack
    path[pathLen] = '\0';
    visited[x][y] = false;
}

void recurseTraverse2(int x, int y, char *path)
{
    // Out of bounds failure
    if ((x < 0) || (y < 0) || (x > GRID_WIDTH) || (y > GRID_HEIGHT))
        return;
    // Win condition, stop traversing
    if ((x == GRID_WIDTH) && (y == GRID_HEIGHT))
    {
        routeCounter++;
        //printf("%d\n", routeCounter);
        return;
    }
    // Try each of the two non-backtracking directions
    recurseTraverse2(x + 1, y, path);
    recurseTraverse2(x, y + 1, path);
}

int main(int argc, char **argv)
{
	mpz_t factorialTest;
	mpz_t result;
	mpz_init(factorialTest);
	mpz_init(result);
	mpz_set_ui(factorialTest, 2); factorialBig(result, factorialTest); printf("2! %s\n", mpz_get_str(NULL, 10, result));
	mpz_set_ui(factorialTest, 3); factorialBig(result, factorialTest); printf("3! %s\n", mpz_get_str(NULL, 10, result));
	mpz_set_ui(factorialTest, 4); factorialBig(result, factorialTest); printf("4! %s\n", mpz_get_str(NULL, 10, result));
	mpz_set_ui(factorialTest, 5); factorialBig(result, factorialTest); printf("5! %s\n", mpz_get_str(NULL, 10, result));
	chooseBig_ui(result, 2 + 2, 2); printf("%s\n", mpz_get_str(NULL, 10, result));
	chooseBig_ui(result, 3 + 3, 3); printf("%s\n", mpz_get_str(NULL, 10, result));
	chooseBig_ui(result, 20 + 20, 20); printf("%s\n", mpz_get_str(NULL, 10, result));
#if 0
	printf("2! %d\n", factorial(2));
	printf("3! %d\n", factorial(3));
	printf("4! %d\n", factorial(4));
	printf("5! %d\n", factorial(5));
	printf("%d\n", choose(2 + 2, 2));
	printf("%d\n", choose(3 + 3, 3));
	printf("%d\n", choose(GRID_WIDTH + GRID_HEIGHT, GRID_WIDTH));
#endif
#if 0
    char path[PATH_LEN];
    memset(visited, 0, sizeof(visited));
    memset(path, 0, sizeof(path));
    recurseTraverse2(0, 0, path);
    printf("%d\n", routeCounter);
    return 0;
#endif
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//#include <ctype.h>
#include <gmp.h>
/*
 * Let us call an integer sided triangle with sides a <= b <= c barely acute
 * if the sides satisfy
 *   a^(2) + b^(2) = c^(2) + 1.
 *
 * How many barely acute triangles are there with perimeter <= 25,000,000?
 */

mpz_t mpz_a, mpz_b, mpz_p, temp1, temp2;
// Given b and perimeter, calculate a
unsigned int calculateA(unsigned int b, unsigned int perimeter, char failOnBadA)
{
    unsigned int result;
    //printf("calculateA\n");
    mpz_set_ui(mpz_b, b);
    mpz_set_ui(mpz_p, perimeter);
    mpz_set_ui(temp1, 2);           // 2
    mpz_mul(temp1, temp1, mpz_p);   // 2p
    mpz_mul(temp1, temp1, mpz_b);   // 2bp
    mpz_set_ui(temp2, perimeter);   // p
    mpz_mul(temp2, temp2, temp2);   // p^2
    mpz_sub(temp1, temp1, temp2);   // 2bp - p^2
    mpz_sub_ui(mpz_a, temp1, 1);    // 2bp - p^2 - 1
    mpz_sub(temp1, mpz_b, mpz_p);   // b - p
    mpz_mul_ui(temp1, temp1, 2);    // 2(b - p)
    //mpz_out_str(stdout, 10, mpz_a); printf(" / "); mpz_out_str(stdout, 10, temp1); printf("\n");
    if (mpz_cmp_ui(temp1, 0) == 0)
        return -1;
    mpz_tdiv_qr(mpz_a, temp2, mpz_a, temp1);    // (2bp - p^2 - 1) / (2(b - p))
    if (failOnBadA && (mpz_cmp_ui(temp2, 0) != 0))  // a isn't integer, abort
        return 0;
    if (failOnBadA && (mpz_cmp_ui(mpz_a, 0) <= 0))  // a is negative
        return 0;
    //printf("HERE\n");
    result = mpz_get_ui(mpz_a);
    //printf("calculateA got %d\n", result);
    return result;
}

// Not used for calculation, just a nicety. If given a and b, return c.
unsigned int calculateC(unsigned int a, unsigned int b)
{
    mpz_set_ui(mpz_a, a);
    mpz_set_ui(mpz_b, b);
    mpz_mul(temp1, mpz_a, mpz_a);
    mpz_mul(temp2, mpz_b, mpz_b);
    mpz_add(temp1, temp1, temp2);
    mpz_sub_ui(temp1, temp1, 1);
#if 0
    mpz_root(temp1, temp1, 2);
    return mpz_get_ui(temp1);
#else
    mpz_rootrem(temp1, temp2, temp1, 2);
    if (mpz_cmp_ui(temp2, 0) != 0)
        printf("Warning: c is not an integer when a=%d, b=%d\n", a, b);
    return mpz_get_ui(temp1);
#endif
}

// Given a perimeter, use binary search to find the threshold of b where a > b
unsigned int maximumPossibleB(unsigned int perimeter)
{
    unsigned int a = 0;
    unsigned int top = perimeter;
    unsigned int bottom = 1;
    while (top > (bottom + 1))
    {
        unsigned int middle = (top + bottom) / 2;
        //printf("%d %d %d, %d\n", bottom, middle, top, a);
        // Find the nearest "a"
        a = calculateA(middle, perimeter, 0);
        if (a == -1)
            return top;
        if (a < middle /*b*/)
            top = middle;
        else if (a > middle /*b*/)
            bottom = middle;
        else
            return middle;
    }
    return top;
}

unsigned int matchingTriangleCount(unsigned int perimeter)
{
    unsigned int result = 0;
    unsigned int a;
    unsigned int maxB = maximumPossibleB(perimeter);
    //printf("perimeter %d, maxB=%d\n", perimeter, maxB);
    for (int b = 1; b <= maxB; b++)
    {
        a = calculateA(b, perimeter, 1);
        //printf("b=%d => a=%d\n", b, a);
        if (a > 0)
            if (a <= b)
            {
                //unsigned int c = calculateC(a, b);
                //printf("Hit! a=%d b=%d c=%d p=%d\n", a, b, c, a+b+c);
                result++;
            }
    }
    //if ((perimeter % 100) == 0)
    //    printf("perimeter %d has %d triangles\n", perimeter, result);
    return result;
}

void test()
{
    unsigned int b = 20, p = 41;
    unsigned int a = calculateA(b, p, 1);
    unsigned int c = calculateC(a, b);
    printf("calculateA(%d, %d) == %d\n", b, p, a);
    printf("  a=%d, b=%d, c=%d, p=%d\n", a, b, c, a + b + c);
    printf("maximumPossibleB(41) == %d\n", maximumPossibleB(41));
}

void test2()
{
    for (unsigned int a = 1; a <= 5; a++)
        for (unsigned int b = 1; b <= 5; b++)
        {
            unsigned int c = floor(sqrt(a*a+b*b-1));
            if ((c > 0) && (ceil(sqrt(a*a+b*b-1)) == c))
                printf("a=%d b=%d c=%d p=%d\n", a, b, c, a + b + c);
        }
}

int main(int argc, char **argv)
{
    unsigned int hitCount = 0;
    mpz_init(mpz_a);
    mpz_init(mpz_b);
    mpz_init(mpz_p);
    mpz_init(temp1);
    mpz_init(temp2);
    test2();
    test();
    for (unsigned int perimeter = 3; perimeter <= 25000000; perimeter++)
    //for (unsigned int perimeter = 3; perimeter <= 5; perimeter++)
        hitCount += matchingTriangleCount(perimeter);
    return 0;
}

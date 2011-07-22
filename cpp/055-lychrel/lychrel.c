#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
#include <gmp.h>
/* If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
 *
 * Not all numbers produce palindromes so quickly. For example,
 *
 * 349 + 943 = 1292,
 * 1292 + 2921 = 4213
 * 4213 + 3124 = 7337
 *
 * That is, 349 took three iterations to arrive at a palindrome.
 *
 * Although no one has proved it yet, it is thought that some numbers, like
 * 196, never produce a palindrome. A number that never forms a palindrome
 * through the reverse and add process is called a Lychrel number. Due to the
 * theoretical nature of these numbers, and for the purpose of this problem,
 * we shall assume that a number is Lychrel until proven otherwise. In
 * addition you are given that for every number below ten-thousand, it will
 * either (i) become a palindrome in less than fifty iterations, or, (ii) no
 * one, with all the computing power that exists, has managed so far to map
 * it to a palindrome. In fact, 10677 is the first number to be shown to
 * require over fifty iterations before producing a palindrome:
 * 4668731596684224866951378664 (53 iterations, 28-digits).
 *
 * Surprisingly, there are palindromic numbers that are themselves Lychrel
 * numbers; the first example is 4994.
 *
 * How many Lychrel numbers are there below ten-thousand?
 *
 * NOTE: Wording was modified slightly on 24 April 2007 to emphasise the
 * theoretical nature of Lychrel numbers.
 *
 */
#define TOP_VALUE 9999
#define MAX_DEPTH 49

char isLychrelCache[TOP_VALUE + 1];

char isPalindrome(const char *s)
{
    const char *front = s, *back = s + strlen(s) - 1;
    while (front <= back)
    {
        if (*front != *back)
            return 0;
        front++;
        back--;
    }
    return 1;
}

// Yes, there's a more efficient way of doing this than string manipulation, but
// this is quick to write and the performance seems sufficient for this
// purpose.
void addWithReverse(mpz_t result, mpz_t op)
{
    char *op1 = mpz_get_str(NULL, 10, op);
    char *op2;
    mpz_t op2Value;
    op2 = strdup(op1);
    char *front = op2, *back = op2 + strlen(op2) - 1;
    while (front <= back)
    {
        char temp = *front;
        *front = *back;
        *back = temp;
        front++;
        back--;
    }
    mpz_set(result, op);
    mpz_init(op2Value);
    mpz_set_str(op2Value, op2, 10);
    mpz_add(result, result, op2Value);
    //printf("%s + %s = ", op1, op2);
    free(op1);
    free(op2);
    //op2 = mpz_get_str(NULL, 10, result);
    //printf("%s\n", op2);
    //free(op2);
}

char isLychrel(mpz_t value, int depth)
{
    char result = 1;
    char *s;
    mpz_t sum;
    if (depth > MAX_DEPTH)
        return 1;
    if (mpz_cmp_ui(value, 0) <= 0) // out of bounds; return error
        return -1;
    // If already in the cache, return cached value
    if (    (mpz_cmp_ui(value, 0) > 0)                  // value > 0
         && (mpz_cmp_ui(value, TOP_VALUE) <= 0)         // value <= TOP_VALUE
         && (isLychrelCache[mpz_get_ui(value)] != -1)    // cache hit
       )
        return isLychrelCache[mpz_get_ui(value)];
    // Not in cache; must calculate
    mpz_init(sum);
    addWithReverse(sum, value);
    s = mpz_get_str(NULL, 10, sum);
    // Check if sum forms a palindrome, if so it's proven to be not lychrel
    if (isPalindrome(s))
    {
        free(s);
        result = 0;
    } else {
        free(s);
        // Not palindromic yet
        result = isLychrel(sum, depth + 1);
    }
    // Put result in cache
    if (    (mpz_cmp_ui(value, 0) > 0)                  // value > 0
         && (mpz_cmp_ui(value, TOP_VALUE) <= 0)         // value <= TOP_VALUE
       )
        isLychrelCache[mpz_get_ui(value)] = result;
    return result;
}

int main(int argc, char **argv)
{
    int lychrelCount = 0;
    mpz_t current;
    memset(isLychrelCache, -1, sizeof(isLychrelCache));
    mpz_init(current);
    printf("Tests:\n");
    mpz_set_ui(current, 47); printf("47 => %d\n", isLychrel(current, 1));
    mpz_set_ui(current, 349); printf("349 => %d\n", isLychrel(current, 1));
    mpz_set_ui(current, 196); printf("196 => %d\n", isLychrel(current, 1));
    mpz_set_ui(current, 4994); printf("4994 => %d\n", isLychrel(current, 1));
    //return 0;
    printf("Run:\n");
    for (mpz_set_ui(current, TOP_VALUE); mpz_cmp_ui(current, 1) >= 0; mpz_sub_ui(current, current, 1))
    {
        isLychrel(current, 1);
    }
    for (int i = 1; i <= TOP_VALUE; i++)
    {
        printf("%6d is ", i);
        switch(isLychrelCache[i]) {
            case 0:     printf("not"); break;
            case 1:     printf("   "); lychrelCount++; break;
            case -1:    printf("???"); break;
        }
        printf(" lychrel\n");
    }
    printf("Lychrel count is %d\n", lychrelCount);
    return 0;
}

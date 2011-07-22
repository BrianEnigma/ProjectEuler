#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
//#include <gmp.h>
/*
 * The decimal number, 585 = 1001001001_(2) (binary), is palindromic in both
 * bases.
 *
 * Find the sum of all numbers, less than one million, which are palindromic
 * in base 10 and base 2.
 *
 * (Please note that the palindromic number, in either base, may not
 * include leading zeros.)
 *
 */

int isPalindrome(const char *s)
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

// Convert to string. It's actually backward, but if we only care about palindromes, it doesn't matter
void toString(unsigned int n, unsigned int base, char *s)
{
    while (n > 0)
    {
        *s++ = n % base + '0';
        n /= base;
    }
    *s = '\0';
}

void test()
{
    const char *numbers[] = {"12345", "12321", "123321", "9", "99", "999", "10101", "1010"};
    char buffer[80];
    for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++)
    {
        const char *s = numbers[i];
        printf("isPalindrome %s is %d\n", s, isPalindrome(s));
    }
    toString(585, 2, buffer);
    printf("%d = %s\n", 585, buffer);
}

int main(int argc, char **argv)
{
    char buffer[80];
    unsigned int sum = 0;
    //const int MAX = 100;
    const int MAX = 1000000;
    test();
    for (unsigned int n = 1; n < MAX; n++)
    {
        toString(n, 10, buffer);
        if (!isPalindrome(buffer))
            continue;
        toString(n, 2, buffer);
        if (isPalindrome(buffer))
        {
            printf("%d,%s\n", n, buffer);
            sum += n;
        }
    }
    printf("= %d\n", sum);
    return 0;
}

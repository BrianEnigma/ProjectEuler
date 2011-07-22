#include <stdio.h>
#include <string.h>

/*
A palindromic number reads the same both ways. The largest palindrome made 
from the product of two 2-digit numbers is 9009 = 91  99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/

//#define MAX_VAL 99
#define MAX_VAL 999

int isPalindrome(unsigned int i)
{
    char buffer[80];
    char *start, *end;
    snprintf(buffer, sizeof(buffer), "%d", i);
    buffer[sizeof(buffer) - 1] = '\0';
    start = &buffer[0];
    end = &buffer[strlen(buffer) - 1];
    while (start < end)
    {
        if (*start != *end)
            return 0;
        start++;
        end--;
    }
    return 1;
}

void testPalindromes()
{
    printf("1234: %d\n", isPalindrome(1234));
    printf("1: %d\n", isPalindrome(1));
    printf("2222: %d\n", isPalindrome(2222));
    printf("12344321: %d\n", isPalindrome(12344321));
    printf("1234321: %d\n", isPalindrome(1234321));
    printf("12345321: %d\n", isPalindrome(12345321));
}

int main(int argc, char **argv) 
{
    //testPalindromes();
    for (int i = MAX_VAL; i > 0; i--)
        for (int j = MAX_VAL; j >= i; j--)
        {
            unsigned int v = i * j;
            if (isPalindrome(v))
                printf("%d * %d == %d\n", i, j, v);
        }
    return 0;
}

#include <stdio.h>
#include <string.h>

/*
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
a^2 + b^2 = c^2

For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/

int isPythagoreanTriplet(unsigned int a, unsigned int b, unsigned int c)
{
	return (a * a) + (b * b) == (c * c);
}

int main(int argc, char **argv)
{
	for (unsigned int a = 0; a < 1000; a++)
		for (unsigned int b = a; b < 1000; b++)
		{
			int c = 1000 - a - b;
			if ((a < b) && (b < c))
				if (isPythagoreanTriplet(a, b, c))
				{
					printf("%d^2 + %d^2 = %d ^2\n", a, b, c);
					printf("%d + %d + %d = %d\n", a, b, c, a+b+c);
					printf("%d * %d * %d = %d\n", a, b, c, a*b*c);
				}
		}
	return 0;
}

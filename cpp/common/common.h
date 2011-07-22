/*
 * common.h
 *
 *  Created on: Jan 8, 2009
 *      Author: brian
 */

#ifndef COMMON_H_
#define COMMON_H_
#define G_INLINE_FUNC static inline
#ifdef BIGNUM
#include <gmp.h>
#endif

int isPrime_ui(unsigned int value);
#ifdef BIGNUM
int isPrime_mpz(mpz_t n);
#endif

void printCallback(char *s);
int doPermutations(char *charset, int charsetLength, char depth, char *buffer, void (*callback)(char *));
int numberLength(unsigned int n);

#endif /* COMMON_H_ */

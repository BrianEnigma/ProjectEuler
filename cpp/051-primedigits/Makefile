# define if we want to use the GMP bignum library
#BIGNUM=1
# local source file(s)
INPUT=main.c
OUTPUT=out
CFLAGS=-std=c99 -I../common -I/sw/include -L/sw/lib

# ---------------------------
# common source file(s)
COMMON=../common/common.c

# The OS X gcc compiler has issues with std=c99 + gmp. Switch to c++ if needed.
ifeq ($(BIGNUM),1)
CC=g++
CFLAGS += -lgmp
else
CC=gcc
endif

$(OUTPUT): $(INPUT) $(COMMON)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(INPUT) $(COMMON)

.PHONY: run
run: $(OUTPUT)
	@./$(OUTPUT)

.PHONY: clean
clean:
	rm -f $(OUTPUT)



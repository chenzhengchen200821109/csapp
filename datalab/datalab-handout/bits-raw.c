/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return (~((~x)|(~y)));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    int result = x >> (0x8 * n);
    result &= 0xFF;
    return result;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    int sign = ~(((0x1 << 31) >> n) << 1); 
    int result = x >> n;
    result = sign & result;
    return result;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    int result = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    result = (result & 0x33333333) + ((result >> 2) & 0x33333333);
    result = (result & 0x0F0F0F0F ) + ((result >> 4) & 0x0F0F0F0F);
    result = (result & 0x00FF00FF) + ((result >> 8) & 0x00FF00FF);
    result = (result & 0x0000FFFF) + ((result >> 16) & 0x0000FFFF);
    return result;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    int result = (~x) & (x - 1); 
    result = (result >> 31) & 0x1;

    return result;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    return (0x1 << 31);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {

    // int min = (0x1 << (n - 1)); /* THIS IS NOT CORRECT!!! */
    int min = ~(0x1 << (n - 1)) + 0x1;
    int max = ~min;

    int resultleft = ((min | ~x) & ((min ^ x) | ~(x - min)));
    resultleft = (resultleft >> 31) & 0x1;

    int resultright = ((x | ~max) & ((x ^ max) | ~(max - x)));
    resultright = (resultright >> 31) & 0x1;

    return (resultleft & resultright);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {

    /* HOW IT WORK? */
    int sign = x >> 31;
    int mask = (1 << n) + (~0x0);
    int bias = sign & mask;

    return (x + bias) >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    int result = ~x + 0x1;
    return result;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    int result = (x >> 1) - x;
    result = (result >> 31) & 0x1;
    return result;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {

    int result = ((x | ~y) & ((x ^ y) | ~(y - x)));
    result = (result >> 31) & 0x1;

    return result;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    int y, m, n;

    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);

    y = -(x >> 16);
    m = (y >> 16) & 16;
    n = 16 - m;
    x = x >> m;

    y = x - 0x100;
    m = (y >> 16) & 8;
    n = n + m;
    x = x << m;

    y = x - 0x1000;
    m = (y >> 16) & 4;
    n = n + m;
    x = x << m;

    y = x - 0x4000;
    m = (y >> 16) & 2;
    n = n + m;
    x = x << m;

    y = x >> 14;
    m = y & ~(y >> 1);

    return(32 - (n + 2 - m) - 1);
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {

    int exponent = ((uf >> 23) & 0xFF);
    int fraction = (uf & 0x7FFFFF);
    int sign = ((uf >> 31) & 0x1);
    if (exponent == 255 && fraction != 0)
        return uf;
    else
        return(((sign ^ 0x1) << 31) | (exponent << 23) | fraction);
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {

    int i, j, countl, countr, length;
    unsigned value;

    if ( x == 0)
        return 0;
    else if (x == 0x80000000)
        return 0xCF000000;
    else if (x < 0) {
        value = ~x + 0x1;
    } else {
        value = x;

	    i = 0;
	    countl = 0;
	    /* Calculate the number of leading zeros */
	    while (i < 32) {
		    if (((~(value >> (31 - i))) & 0x1) == 0x1) {
        	    countl++;
                i++;
	        } else {
		        break;
		    }
        }

        j = 0;
        countr = 0;
        /* Calculate the number of trailing zeros */
        while (j < 32) {
            if (((~((value >> j) << 31)) & 0x80000000) == 0x80000000) {
                countr++;
                j++;
            } else {
                break;
            }
        }
        length = 32 - countl - countr - 1;

        if (length == 0)
            return 0x4B000000;
        else if (length > 0 && length <= 23) {
            unsigned mask = ~((0x1 << (countr + length)));
            value = value & mask;
            unsigned part2 = (value >> countr) << (23- length);
            unsigned part1 = (countr + length + 127) << 23;
            unsigned part0 = x & 0x80000000;
            return(part0 | part1 | part2);
        } else {
            length = length + 1;
            unsigned part1 = (32 - countl - countr + 127) << 23;
            unsigned part0 = x & 0x80000000;
            return(part0 | part1);
        }

    }

    i = 0;
    countl = 0;
    /* Calculate the number of leading zeros */
    while(i < 32) {
        if (((~(value >> (31 - i))) & 0x1) == 0x1) {
            countl++;
            i++;
        } else {
            break;
        }
    } 

    j = 0;
    countr = 0;
    /* Calculate the number of trailing zeros */
    while (j < 32) {
        if (((~((value >> j) << 31)) & 0x80000000) == 0x80000000) {
            countr++;
            j++;
        } else {
            break;
        }
    }

    length = 32 - countl - countr - 1;
    if (length == 0)
        return 0xCB800000;
    else if (length > 0 && length <= 23) {
        value = value & ~((0x1 << (countr + length)));
        unsigned part2 = (value >> countr) << (23 - length);
        unsigned part1 = (countr + length + 127) << 23;
        unsigned part0 = x & 0x80000000;
        return(part0 | part1 | part2);
    } else {
        length = length + 1;
        unsigned part1 = (32 - countl - countr + 127) << 23;
        unsigned part0 = x & 0x80000000;
        return(part0 | part1);
    }

}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    unsigned exponent = ((uf >> 23) << 1) & 0xFF;
    unsigned fraction = (uf & 0x7FFFFF);
    unsigned sign = ((uf >> 31) & 0x1);
    if (exponent == 255 && fraction != 0)
        return uf;
    else
        return (((sign ^ 0x1) << 31) | (exponent << 23) | fraction);
}

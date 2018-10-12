#include <stdio.h>

unsigned float_i2f(int x) {

    int i, j, k, countl, countr;
    int fracSize; /* number of fraction bits */
    int sign, exp, frac;
    unsigned value, roundUp, roundDown, midValue;
    int flag, mask;

    if ( x == 0)
        return 0;
    /* x is the smallest negative number */
    else if (x == 0x80000000)
        return 0xCF000000;
    else if (x < 0) {
        value = ~x + 0x1;
    } else {
        value = x;
    }

    i = 0;
    countl = 0; /* number of leading zeros */
    /* Calculate the number of leading zeros */
    while(i < 32) {
        if (((~(value >> (31 - i))) & 0x1) == 0x1) {
            countl++;
            i++;
        } else {
            break;
        }
    } 
    printf("countl is %d\n", countl);

    j = 0;
    countr = 0; /* number of trailing zeros */
    /* Calculate the number of trailing zeros */
    while (j < 32) {
        if (((~((value >> j) << 31)) & 0x80000000) == 0x80000000) {
            countr++;
            j++;
        } else {
            break;
        }
    }
    printf("countr is %d\n", countr);

    k = 0;
    while (k < 24) {
        if (((value >> (30 - k - countl)) & 0x1) == 0x1) {
            k++;
        } else {
            break;
        }
    }
    printf("k is %d\n", k);

    fracSize = 32 - countl - countr - 1;
    printf("fracSize is %d\n", fracSize);
    mask = ~(0x1 << (32 - countl - 1));

    if (fracSize == 0) {
        exp = (countr + 127) << 23;
        sign = x & 0x80000000;
        return(sign | exp);
    }
    else if (fracSize > 0 && fracSize <= 23) {
        value = value & ~((0x1 << (countr + fracSize)));
        frac = (value >> countr) << (23 - fracSize);
        exp = (countr + fracSize + 127) << 23;
        sign = x & 0x80000000;
        return(sign | exp | frac);
    } else {
        if (k == 24) {
            printf("k==24\n");
            exp = (countr + fracSize + 1 + 127) << 23;
            sign = x & 0x80000000;
            return(sign | exp);
        } else {
            roundUp = (((value >> (32 - countl - 1 - 23))  + 0x1) << 0x1) << (32 - countl - 1 - 23 - 1);
            roundDown = ((value >> (32 - countl - 1 - 23)) << 0x1) << (32 - countl - 1 - 23 - 1);
            midValue = (((value >> (32 - countl - 1 - 23)) << 0x1) + 0x1) << (32 - countl - 1 - 23 - 1);
            exp = (countr + fracSize + 127) << 23;
            printf("exp is %d\n", exp);
            sign = x & 0x80000000;
            if (value > midValue) {
                printf(">\n");
                frac = (roundUp & mask) >> (32 - countl - 1 - 23);
                return(sign | exp | frac);
            } else if (value < midValue) {
                printf("<\n");
                frac = (roundDown & mask) >> (32 - countl - 1 - 23);
                return(sign | exp | frac);
            } else if (value == midValue) {
                printf("=\n");
                flag = (roundUp >> (32 - countl - 1 - 23)) & 0x1;
                if (flag == 0x1) {
                    frac = (roundDown & mask) >> (32 - countl - 1 - 23);
                    return(sign | exp | frac);
                } else {
                    frac = (roundUp & mask) >> (32 - countl - 1 - 23);
                    return(sign | exp | frac);
                }
            }
            else
                return(0);
        }
    }
}

unsigned float_twice(unsigned uf) {
    unsigned exponent, fraction, sign;
    unsigned new_exp, new_frac;
    unsigned carry_flag;

    exponent = ((uf >> 23) & 0xFF);
    printf("exponent is %d\n", exponent);
    fraction = (uf & 0x7FFFFF);
    printf("fraction is %d\n", fraction);
    sign = ((uf >> 31) & 0x1);
    printf("sign is %d\n", sign);

    /* NaN */
    if (exponent == 255 & fraction != 0)
        return(uf);
    /* infinit */
    else if (exponent == 255 & fraction == 0)
        return(uf);
    /* non-normalization */
    else if (exponent == 0) {
        if (fraction == 0)
            return(uf);
        else {
            new_frac = fraction + fraction;
            return ((sign << 31) | (exponent << 23) | new_frac);
        }
    } 
    /* normalization */
    else {
        if (exponent > 254)
            new_exp = 255 << 23;
        else
            new_exp = (exponent + 0x1) << 23;
        return ((sign << 31) | new_exp | fraction);
    }
}

int main()
{
    int x = 0x7FFFFF;
    int result;

    result = float_twice(x);
    printf("The result = %d\n", result);

    return 0;
}

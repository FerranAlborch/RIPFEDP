/*
* Software Name : RFEDP
* Version: 1.0
* SPDX-FileCopyrightText: Copyright (c) 2024[-2024] Orange Innovation
*
* This software is confidential and proprietary information of Orange Innovation.
* You shall not disclose such Confidential Information and shall not copy, use or distribute it
* in whole or in part without the prior written consent of Orange Innovation
*
* Author: Ferran Alborch Escobar
*/

#include <stdio.h>
#include <gmp.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils/multi_expo.h"
#include "utils/wNAF.h"

/**
 * Function for getting the biggest bit size in an array of mpz_t elements
*/
int get_biggest_bit_size(mpz_t *array, int length) {
    int biggest_bit_size = 0;
    for (int i = 0; i < length; i++)
    {
        int bit_size = mpz_sizeinbase(array[i], 2);
        if (bit_size > biggest_bit_size)
        {
            biggest_bit_size = bit_size;
        }
    }

    return biggest_bit_size;
}

/**
 * Function to get the optimal value of w depending on the bit size
*/
int getOptimalWVal(int m) {
    if(m<13) return 2;
    if(m<41) return 3;
    if(m<121) return 4;
    if(m<337) return 5;
    if(m<897) return 6;
    if(m<2305) return 7;
    return 8;
}


/**
 * Function to do the precomputation for the multi exponentiation
*/
void multi_exponentiation_precomputation(mpz_t **gE, mpz_t *g, unsigned int g_size, int w[], mpz_t mod) {

    size_t k = g_size;
    //    val maxJ = (1 << w) / 2

    // printf("b = %d\n", b);
    //  for(unsigned int i = 0; i<k; i++ ) {
    //      printf("w[%d] = %d\n", i, w[i]);
    //  }

    // mpz_t one;
    // mpz_init(one);
    // mpz_set_ui(one, 1);

    //size_t rows = k;
    //size_t cols = b;

    mpz_t squareG, tmp;
    mpz_inits(squareG, tmp, NULL);

    for (unsigned int i = 0; i < k; i++)
    {
        // gE(i).insert(0, g(i))
        mpz_set(gE[i][0], g[i]);

        // val squareG = mont.monPro(g(i), g(i))
        mpz_mul(squareG, g[i], g[i]);
        mpz_mod(squareG, squareG, mod);
        unsigned int maxJ = (1 << w[i]) / 2;

        // gmp_printf("square[%d] = %Zx\n", i, squareG);

        for (unsigned int j = 1; j < maxJ; j++)
        {
            // compute g_i^1, g_i^3, g_i^5, ... g_i^(2^w -1)
            mpz_mul(tmp, squareG, gE[i][j - 1]);
            mpz_mod(tmp, tmp, mod);
            mpz_set(gE[i][j], tmp);
        }
    }

    mpz_clears(squareG, tmp, NULL);
}


/**
 * Function to free the precomputation
*/
void freePrecomp(mpz_t **matrix, unsigned int rows, unsigned int cols) {
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < cols; j++)
        {
            mpz_clear(matrix[i][j]);
        }
        free(matrix[i]);
    }

    free(matrix);
}


/**
 * Function for multiple exponentiation, base on the wNAF-based interleaving exponentiation method
*/
void multiple_exponentiation(mpz_t result, size_t l, mpz_t *bases, mpz_t *exponents, mpz_t modulo) {
    
    
    mpz_set_ui(result, 1);

    unsigned int k = l;

    // bit size of greatest exponent
    unsigned int b = get_biggest_bit_size(exponents, l);

    int **N = (int **)malloc(sizeof(int *) * k);
    int *w = (int *)malloc(sizeof(int) * k);
    for (unsigned int i = 0; i < k; i++) {
        w[i] = getOptimalWVal(mpz_sizeinbase(exponents[i], 2));
    }

    mpz_t **gN = (mpz_t **)malloc(sizeof(mpz_t) * k);
    
    // Initialize the elements of the matrix
    for (unsigned int i = 0; i < k; i++) {
        gN[i] = (mpz_t *)malloc(sizeof(mpz_t) * b);

        for (unsigned int j = 0; j < b; j++)
        {
            mpz_init(gN[i][j]);
            mpz_set_ui(gN[i][j], 1);
        }
    }

    multi_exponentiation_precomputation(gN, bases, l, w, modulo);

    for (unsigned int i = 0; i < k; i++) {
        wNAFRepresentation nafRep;
        computewNAFRepresentation(&nafRep, exponents[i], w[i]);
        N[i] = (int *)calloc(b, sizeof(int));
        memcpy(N[i], nafRep.naf, nafRep.nafLength * sizeof(int));
        freeNAF(&nafRep);
    }

    free(w);

    for (int j = b - 1; j >= 0; j--)
    {
        mpz_mul(result, result, result);
        mpz_mod(result, result, modulo);

        for (unsigned int i = 0; i < k; i++)
        {
            if (N[i][j] != 0)
            {
                mpz_mul(result, result, gN[i][(N[i][j] / 2)]);
                mpz_mod(result, result, modulo);
            }
        }
    }

    for (unsigned int i = 0; i < k; i++) {
        free(N[i]);
    }
    free(N);
    freePrecomp(gN, k, b);
}


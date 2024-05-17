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

#include <gmp.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Function for getting the giggest bit size in an array of mpz_t elements
*/
int get_biggest_bit_size(mpz_t *array, int length);

/**
 * Function to get the optimal value of w depending on the bit size
*/
int getOptimalWVal(int m);

/**
 * Function to do the precomputation for the multi exponentiation
*/
void multi_exponentiation_precomputation(mpz_t **gE, mpz_t *g, unsigned int g_size, int w[], mpz_t mod);

/**
 * Function to free the precomputation
*/
void freePrecomp(mpz_t **matrix, unsigned int rows, unsigned int cols);

/**
 * Function for multiple exponentiation, base on the wNAF-based interleaving exponentiation method
*/
void multiple_exponentiation(mpz_t result, size_t l, mpz_t *bases, mpz_t *exponents, mpz_t modulo);
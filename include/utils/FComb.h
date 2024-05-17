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
* \file
* \ingroup utils
* \brief Functions for computing the fixed-based comb method for fast exponentiations. See
* Chapter 14, Section 14.6.3 iii in "Handbook of Applied Cryptography" by Menezes.
*/


/**
* \struct FCombInt FComb.h "utils/FComb.h"
* \brief It represents the precomputations for the fixed-based comb method. 
*/
typedef struct FCombInt {
    // Parameters for the scheme
    int h; /**< Parameter h. */
    int v; /**< Parameter v.  */
    int powh; /**< 2^h */

    int n; /**< Bit size of the exponent. */ 
    int a; /**< a = n/h */ 
    int b; /**< b = a/v */ 

    // Precomputation storing
    mpz_t **G; /**< Storage of the procomputation. */
    mpz_t modulo; /**< Modulo. */
    mpz_t g; /**< Base. */
} FCombInt;


/**
* \struct FCombExponentArray FComb.h "utils/FComb.h"
* \brief It represents the exponent array for the fixed-based comb method. 
*/
typedef struct FCombExponentArray {
    int * ea_int; /**< Storage of the exponent array */
    int h; /**< Parameter h. */
    int a; /**< Parameter a. */
    int b; /**< Parameter b. */
    int v; /**< Parameter v. */
} FCombExponentArray;


/**
* \fn int getbit(unsigned char b, int ind)
* \brief Auxiliary function to aid dealing with finding bits inside bytes.
*
* \param b A bit.
* \param ind An index.
*/
int getbit(unsigned char b, int ind);


/**
* \fn int getbitTab(unsigned char* b, int ind)
* \brief Auxiliary function to aid dealing with finding bits inside bytes.
*
* \param b A pointer to a bit.
* \param ind An index.
*/
int getbitTab(unsigned char* b, int ind);


/**
* \fn int setbit(int b, const int ind)
* \brief Auxiliary function to aid dealing with finding bits inside bytes.
*
* \param b A bit.
* \param ind An index.
*/
int setbit(int b, const int ind);


/**
* \fn int setBitvalue(int num, int ind, int isset)
* \brief Auxiliary function to aid dealing with finding bits inside bytes.
*
* \param b A bit.
* \param ind An index.
* \param isset A boolean to indicate whether the bit is set or not.
*/
int setBitvalue(int num, int ind, int isset);


/**
* \fn int clearbit(int b, const int ind)
* \brief Auxiliary function to aid dealing with finding bits inside bytes.
*
* \param b A bit.
* \param ind An index.
*/
int clearbit(int b, const int ind);


/**
* \fn int ceiling(double n)
* \brief It outputs the ceiling of a non-integer number.
*
* \param n The number to round.
*/
int ceiling(double n);


/**
* \fn void FCombExponentArray_init(FCombExponentArray *EAi, mpz_t number, int a, int h, int v, int b)
* \brief It initializes an exponent array for the fixed-based comb method.
*
* \param EAi A pointer to a FCombExponentArray structure.
* \param number The exponent for which the array is computed.
* \param a Parameter for the fixed-based comb method.
* \param h Parameter for the fixed-based comb method.
* \param v Parameter for the fixed-based comb method.
* \param b Parameter for the fixed-based comb method.
*/
void FCombExponentArray_init(FCombExponentArray *EAi, mpz_t number, int a, int h, int v, int b);


/**
* \fn void FCombExponentArray_free(FCombExponentArray *EA)
* \brief It clears an exponent array for the fixed-based comb method and frees allocated memory.
*
* \param EA A pointer to a FCombExponentArray structure.
*/
void FCombExponentArray_free(FCombExponentArray *EA);


/**
* \fn void getSquareArray(mpz_t squareArray[], mpz_t base, mpz_t modulo, int nbSquare)
* \brief Auxiliary function to produce an array of powers of a base.
*
* \param squareArray An array to store the result.
* \param base The base for the exponentiations.
* \param modulo The modulo over which the exponentiations are performed.
* \param nbSquare The size of the array.
*/
void getSquareArray(mpz_t squareArray[], mpz_t base, mpz_t modulo, int nbSquare);


/**
* \fn void FCombInt_alloc(FCombInt *F, mpz_t modulo, mpz_t baseExpo, int lengthexpo, int hparam, int vparam)
* \brief It preallocates the memory for a FCombInt structure.
*
* \param F A pointer to a FCombInt structure.
* \param modulo The modulo for the exponentiation.
* \param baseExpo The base for the exponentiation.
* \param lengthexpo Maximum number of bits of the exponent.
* \param hparam Parameter for the fixed-base comb method.
* \param vparam Parameter for the fixed-base comb method.
*/
void FCombInt_alloc(FCombInt *F, mpz_t modulo, mpz_t baseExpo, int lengthexpo, int hparam, int vparam);


/**
* \fn void FCombInt_init(FCombInt *F)
* \brief It initializes a FCombInt structure.
*
* \param F A pointer to a FCombInt structure.
*/
void FCombInt_init(FCombInt *F);


/**
* \fn void FCombInt_free(FCombInt *F)
* \brief It clears a FCombInt structure and frees allocated memory.
*
* \param F A pointer to a FCombInt structure.
*/
void FCombInt_free(FCombInt *F);

/**
 * Function to compute the multi-exponentiation of two bases with f-comb precomputations
*/
/**
* \fn void FComb_multiMult(mpz_t result, FCombInt * precomps, mpz_t * expos, int nbElems)
* \brief It computes the multi-exponentiation of several bases with fixed-comb method precomputations.
*
* \param result A multiple precision integer to store the result.
* \param precomps A pointer to an array of FCombInt structure.
* \param expos A pointer to an array of exponents.
* \param nbElems The number of bases and exponents.
*/
void FComb_multiMult(mpz_t result, FCombInt * precomps, mpz_t * expos, int nbElems);
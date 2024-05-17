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
* Structure representig the Fcomb precomputations.
*/
typedef struct FCombInt {
    // Parameters for the scheme
    int h;
    int v;
    int powh;

    int n; // size in bits of exp
    int a; // a=n/h
    int b; // b=a/v

    // Precomputation storing
    mpz_t **G;
    mpz_t modulo;
    mpz_t g; //base
} FCombInt;


/**
 * Structure representing the exponent array for the FComb algoryhtm
*/
typedef struct FCombExponentArray {
    int * ea_int;
    int h;
    int a;
    int b;
    int v;
} FCombExponentArray;

/**
 * Auxiliary functions to aid dealing with finding bits inside bytes
*/
int getbit(unsigned char b, int ind);

int getbitTab(unsigned char* b, int ind);

int setbit(int b, const int ind);

int setBitvalue(int num, int ind, int isset);

int clearbit(int b, const int ind);

/**
 * Auxiliary function to compute the ceiling of a double
*/
int ceiling(double n);

/**
 * Function to initialize FComb exponent array
*/
void FCombExponentArray_init(FCombExponentArray *EAi, mpz_t number, int a, int h, int v, int b);

/**
 * Function to free FComb exponent array
*/
void FCombExponentArray_free(FCombExponentArray *EA);

/**
 * Auxiliary function to square an array
*/
void getSquareArray(mpz_t squareArray[], mpz_t base, mpz_t modulo, int nbSquare);

/**
 * Function to preallocate the space for FComb
*/
void FCombInt_alloc(FCombInt *F, mpz_t modulo, mpz_t baseExpo, int lengthexpo, int hparam, int vparam);

/**
 * Function to initialize the precomputations for FComb
*/
void FCombInt_init(FCombInt *F);

/**
 * Function to free the precomputations for FComb
*/
void FCombInt_free(FCombInt *F);

/**
 * Function to compute the multi-exponentiation of two bases with f-comb precomputations
*/
void FComb_multiMult(mpz_t result, FCombInt * precomps, mpz_t * expos, int nbElems);
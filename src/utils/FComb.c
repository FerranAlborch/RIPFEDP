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
#include "utils/FComb.h"

/**
 * Auxiliary functions to aid dealing with finding bits inside bytes
*/
int getbit(unsigned char b, int ind) {

    if (ind > 7) {
        return -1;
    }
    if (ind < 0) {
        return -1;
    }

    unsigned char mask = 0;

    switch (ind) {
        case 0: mask = 128;
            break;
        case 1: mask = 64;
            break;
        case 2: mask = 32;
            break;
        case 3: mask = 16;
            break;
        case 4: mask = 8;
            break;
        case 5: mask = 4;
            break;
        case 6: mask = 2;
            break;
        case 7: mask = 1;
            break;
    }

    if ((b & mask) > 0) {
        return 1;
    } else {
        return 0;
    }
}

int getbitTab(unsigned char* b, int ind) {
    int indtab = ind / 8;
    //int indbit=ind-indtab;
    int indbit = ind % 8;

    if (indbit < 0) {
        indbit += 8;
    }

    return getbit(b[indtab], indbit);
}

int setbit(int b, const int ind) {

    unsigned int _masks_int [] = {0x80000000, 0x40000000, 0x20000000, 0x10000000,
        0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x00800000, 0x00400000, 0x00200000,
        0x00100000, 0x00080000, 0x00040000, 0x00020000, 0x00010000, 0x00008000, 0x00004000,
        0x00002000, 0x00001000, 0x00000800, 0x00000400, 0x00000200, 0x00000100, 0x00000080,
        0x00000040, 0x00000020, 0x00000010, 0x00000008, 0x00000004, 0x00000002, 0x00000001};


    if (ind > 31) {
        //            throw new RuntimeException("can't find a bit of indice > 7 in a byte!");
        return b;
    }
    if (ind < 0) {
        //            throw new RuntimeException("can't find a bit of indice < 0 in a byte!");
        return b;
    }

    int mask = _masks_int[ind];
    b |= mask;

    return b;
}

int setBitvalue(int num, int ind, int isset) {
    if (isset == 1) {
        return setbit(num, ind);
    } else if (isset == 0) {
        return clearbit(num, ind);
    } else {
        return num;
    }
}

int clearbit(int b, const int ind) {

    unsigned int _masks_int [] = {0x80000000, 0x40000000, 0x20000000, 0x10000000,
        0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x00800000, 0x00400000, 0x00200000,
        0x00100000, 0x00080000, 0x00040000, 0x00020000, 0x00010000, 0x00008000, 0x00004000,
        0x00002000, 0x00001000, 0x00000800, 0x00000400, 0x00000200, 0x00000100, 0x00000080,
        0x00000040, 0x00000020, 0x00000010, 0x00000008, 0x00000004, 0x00000002, 0x00000001};

    if (ind > 31) {
        //            throw new RuntimeException("can't find a bit of indice > 31 in an int!");
        return b;
    }
    if (ind < 0) {
        return b;
        //            throw new RuntimeException("can't find a bit of indice < 0 in an int!");
    }

    int mask = _masks_int[ind];
    b &= ~mask; // b^=mask;

    return b;
}

bool isBitSet(int b, const int ind) {
    unsigned int _masks_int [] = {0x80000000, 0x40000000, 0x20000000, 0x10000000,
        0x08000000, 0x04000000, 0x02000000, 0x01000000, 0x00800000, 0x00400000, 0x00200000,
        0x00100000, 0x00080000, 0x00040000, 0x00020000, 0x00010000, 0x00008000, 0x00004000,
        0x00002000, 0x00001000, 0x00000800, 0x00000400, 0x00000200, 0x00000100, 0x00000080,
        0x00000040, 0x00000020, 0x00000010, 0x00000008, 0x00000004, 0x00000002, 0x00000001};

    if (ind > 31 || ind < 0) {
        //        printf("toolsbyte isBitSet range error");
        return false;
    }
    if (ind == 0) {
        return b < 0;
    }
    int mask = _masks_int[ind];

    if ((b & mask) > 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * Auxiliary function to compute the ceiling of a double
*/
int ceiling(double n) {
    int nint = (int) n;

    if (n > nint) {
        return nint + 1;
    } else {
        return nint;
    }
}

/**
 * Function to initialize FComb exponent array
*/
void FCombExponentArray_init(FCombExponentArray *EAi, mpz_t number, int a, int h, int v, int b) {

    EAi->a = a;
    EAi->h = h;
    EAi->v = v;
    EAi->b = b;


    // bit length of exponent
    int bitlength = mpz_sizeinbase(number, 2);
    int bytelength = (bitlength + 7) / 8 ; 

    // convert to byte array
    unsigned char * bytebuf = (unsigned char *) malloc(sizeof(unsigned char) * bytelength);
        
    mpz_export(bytebuf, NULL, 1, bytelength, 1, 0, number);


    // as a byte is 8 bits lengh, the byte array is a little too big:
    // get the index of the first bit of number
    int zeroIndbyteBuf = (bytelength * 8) - bitlength;

    int bufint = 0;

    // the int we will construct will be a most a h-bit number
    // zeroIndBufint represent the index of the first bit of this number
    int zeroIndBufint = (sizeof(int))*8 - h;


    int length = b * (v + 1);
    //ea_int = new int[length];
    EAi->ea_int = (int *) malloc(sizeof(int) *length);

    // init tab to zero
    for (int i=0; i<length; i++) {
        EAi->ea_int[i] = 0;
    }

    int k;
    int aJ;


    for (int i = 0; i < a; i++) {

        int index = h - 1;
        aJ = bitlength - 1 - i + a;

        for (int j = 0; j < h; j++) {
            // aJ=aJ-a;
            aJ -= a;
            k = aJ;

            
            if ((index >= 0) && (k >= 0)) {
                int readbit = getbitTab(bytebuf, zeroIndbyteBuf + k);
                bufint = setBitvalue(bufint, zeroIndBufint + index, readbit);
            } 
            else {
                bufint = clearbit(bufint, zeroIndBufint + index);
            }
            
            index--;
        }


        EAi->ea_int[i] = bufint;
        bufint=0;
    }

    free(bytebuf);

}

/**
 * Function to free FComb exponent array
*/
void FCombExponentArray_free(FCombExponentArray *EA) {
    free(EA->ea_int);
}


/**
 * Auxiliary function to square an array
*/
void getSquareArray(mpz_t squareArray[], mpz_t base, mpz_t modulo, int nbSquare) {
    mpz_set(squareArray[0], base);
    for (int i = 1; i < nbSquare; i++) {
        mpz_powm_ui(squareArray[i], squareArray[i - 1], 2, modulo);
    }
}

/**
 * Function to preallocate the space for FComb
*/
void FCombInt_alloc(FCombInt *F, mpz_t modulo, mpz_t baseExpo, int lengthexpo, int hparam, int vparam) {
    // Allocate the memory
    F->n = lengthexpo;
    F->h = hparam;
    F->v = vparam;
    F->a = ceiling((double) (lengthexpo + 1) / F->h);

    if (F->v < 1 || F->v > F->a) {
        printf("v out of range");
    }

    F->b = ceiling((double) F->a / F->v);
    F->powh = 2 << (F->h - 1); // _2powh = 2^h

    mpz_init(F->g);
    mpz_set(F->g, baseExpo);
    
    mpz_init(F->modulo);
    mpz_set(F->modulo, modulo);

    F->G = (mpz_t**) malloc(sizeof (mpz_t) * F->v);

    for (int i = 0; i < F->v; i++) {
        //G[i] = new mpz_t [_2powh];
        F->G[i] = (mpz_t*) malloc(sizeof (mpz_t) * F->powh);
        for (int j = 0; j < F->powh; j++) {
            mpz_init(F->G[i][j]);
        }
    }
}

/**
 * Function to initialize the precomputations for FComb
*/
void FCombInt_init(FCombInt *F) {

    // computation of the g_i
    mpz_t * g_i = (mpz_t*) malloc(sizeof (F->g) * F->h);

    int sizeHTwiceArray = ((F->h - 1) * F->a) + 1;
    int sizeVTwiceArray = ((F->v - 1) * F->b) + 1;

    int sizeTwiceArray = sizeHTwiceArray;
    if (sizeVTwiceArray > sizeHTwiceArray) sizeTwiceArray = sizeVTwiceArray;

    mpz_t * squareArray = (mpz_t*) malloc(sizeof (F->g) * sizeTwiceArray);
    for (int i = 0; i < sizeTwiceArray; i++) {
        mpz_init(squareArray[i]);
    }

    // step one
    // g_i=g^(2^(ia))
    getSquareArray(squareArray, F->g, F->modulo, sizeHTwiceArray);
    for (int i = 0; i < F->h; i++) {
        mpz_init(g_i[i]);
        mpz_set(g_i[i], squareArray[i * F->a]);
    }
    
    
    // step two
    // G[j][i]
    for (int i = 1; i < F->powh; i++) {
        mpz_set_ui(F->G[0][i], 1);

        // step 2.1
        // compute G[0][i]
        for (int j = 0; j < F->h; j++) {
            if (isBitSet(i, 31 - j)) {
                mpz_mul(F->G[0][i], F->G[0][i], g_i[j]);
                mpz_mod(F->G[0][i], F->G[0][i], F->modulo);
            }
        }

        // step 2.2
        // compute G[j][i]
        getSquareArray(squareArray, F->G[0][i], F->modulo, sizeVTwiceArray);
        int jb = F->b;
        for (int j = 1; j < F->v; j++) {
            mpz_set(F->G[j][i], squareArray[jb]);
            jb += F->b;
        }

    }
      
    // Here all the precomputation are achieved


    for (int j = 0; j < F->h; j++) {
        mpz_clear(g_i[j]);
    }

    free(g_i);

    for (int i = 0; i < sizeTwiceArray; i++) {
        mpz_clear(squareArray[i]);
    }
    free(squareArray);

}

/**
 * Function to free the precomputations for FComb
*/
void FCombInt_free(FCombInt *F) {
    mpz_clears(F->g, F->modulo, NULL);
    for (int i = 0; i < F->v; i++) {
        //G[i] = new mpz_t [_2powh];
        for (int j = 0; j < F->powh; j++) {
            mpz_clear(F->G[i][j]);
        }
        free(F->G[i]);
    }
    free(F->G);
}


/**
 * Function to compute the multi-exponentiation of two bases with f-comb precomputations
*/
void FComb_multiMult(mpz_t result, FCombInt * precomps, mpz_t * expos, int nbElems) {

    int a = precomps[0].a;
    int h = precomps[0].h;
    int v = precomps[0].v;
    int b = precomps[0].b;

    // ExponentArray ** EA = (ExponentArray **) malloc(sizeof (ExponentArray *) * nbElems);
    // FcombExponentArray ** EA = new FcombExponentArray * [nbElems];
    FCombExponentArray * EA = (FCombExponentArray *) malloc(sizeof (FCombExponentArray) * nbElems);

    // array of EA for each exponent
    for (int i = 0; i < nbElems; i++) {
        //EA[i] = (FCombExponentArray *) malloc(sizeof (FCombExponentArray) * );
        FCombExponentArray_init(&EA[i], expos[i], a, h, v, b);
    }


    mpz_t mod;
    mpz_init(mod);
    mpz_set(mod, precomps[0].modulo); 


    mpz_t R[3];
    mpz_inits(R[0], R[1], R[2], NULL);

    mpz_set_ui(R[0], 1);
    mpz_set_ui(R[1], 1);

    int I = 0;
    int ki = 0;
    int Ii = 0;


    for (int k = b - 1; k >= 0; k--) {
        mpz_powm_ui(R[0], R[0], 2, mod);

        for (int i = 0; i < nbElems; i++) {
            for (int j = v - 1; j >= 0; j--) {
                //I = EA[i]->getNumberColumn(j, k);
                I = EA[i].ea_int[j * b + k];
                if (I != 0) {
                    ki = 0;
                    Ii = I;
                } else { // to protect against SPA
                    ki = 2;
                    Ii = 1;
                }

                mpz_mul(R[ki], R[0], precomps[i].G[j][Ii]);
                mpz_mod(R[ki], R[ki], mod);

            }
        }
    }


    I = 0;
    ki = 0;
    Ii = 0;

    mpz_set(result, R[0]);

    
    // free memory   
    mpz_clears(R[0], R[1], R[2], NULL);

  
    for (int i = 0; i < nbElems; i++) {
        FCombExponentArray_free(&EA[i]);
    }

    free(EA);

    mpz_clear(mod);

}
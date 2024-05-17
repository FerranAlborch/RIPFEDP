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
#include "utils/wNAF.h"

/**
 * Function for computing the wNAF representation
*/
void computewNAFRepresentation(wNAFRepresentation *naf, mpz_t num, int w) {
    int pow2wB = (1 << w);
       
    int i = 0;
       
    mpz_t n;
    mpz_init_set(n, num);
    mpz_t tmp;
    mpz_init(tmp);
       
    int sizeNi = mpz_sizeinbase(num, 2) + 1;
    // printf("SizeNi %d\n", sizeNi);
    int * ni = (int *) malloc(sizeNi * sizeof(int *));
    for(i=0; i<sizeNi; i++) {
        ni[i] = 0;
    }
       
    i = 0;
       
    while(mpz_cmp_si(n, 0) > 0 ) {
        if(mpz_tstbit(n, 0)==1) {// if odd
            ni[i] = mpz_mod_ui(tmp, n, pow2wB);
            // printf("ni[%d] = %d\n", i, ni[i]);
            mpz_sub_ui(n, n, ni[i]);
        }
           
        mpz_div_ui(n, n, 2);
        i++;
    }
       
        
    naf->naf = ni;
    naf->nafLength = i;
    naf->reqPreCompLen =  (1 << (w - 1));

    mpz_clears(n, tmp, NULL);

    // free(ni);
}


/**
 * Function to free the wNAF representation
*/
void freeNAF(wNAFRepresentation * naf) {
    free(naf->naf);
}
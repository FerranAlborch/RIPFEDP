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
* Structure representig the NAF structure.
*/
typedef struct wNAFRepresentation {
    int * naf;
    int nafLength;
    int reqPreCompLen; 
} wNAFRepresentation;

/**
 * Function for computing the wNAF representation
*/
void computewNAFRepresentation(wNAFRepresentation *naf, mpz_t num, int w);


/**
 * Function to free the wNAF representation
*/
void freeNAF(wNAFRepresentation * naf);
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
* \brief Functions for computing the windowed NAF representation for simultaneous 
* multiple exponentiation.
*/


/**
* \struct wNAFRepresentation wNAF.h "utils/wNAF.h"
* \brief It represents the windowed NAF. 
*/
typedef struct wNAFRepresentation {
    int * naf; /**< Storage of the NAF. */
    int nafLength; /**< Length of the NAF. */
    int reqPreCompLen; /**< Required precomputation lenght. */
} wNAFRepresentation;


/**
* \fn void computewNAFRepresentation(wNAFRepresentation *naf, mpz_t num, int w)
* \brief It computes the windowed NAF representation.
*
* \param naf A pointer to a wNAFRepresentation structure.
* \param num The value for which the representation is computed.
* \param w The parameter w.
*/
void computewNAFRepresentation(wNAFRepresentation *naf, mpz_t num, int w);


/**
* \fn void freeNAF(wNAFRepresentation * naf)
* \brief It frees the windowed NAF representation and clears allocated memory.
*
* \param naf A pointer to a wNAFRepresentation structure.
*/
void freeNAF(wNAFRepresentation * naf);
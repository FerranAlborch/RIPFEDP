/*
* Software Name : RIPFEDP
* Version: 1.1
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at 
*     http://www.apache.org/licenses/LICENSE-2.0 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Author: Ferran Alborch Escobar <ferran.alborch@gmail.com>
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
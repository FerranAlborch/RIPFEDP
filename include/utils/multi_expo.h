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
* \brief Functions for computing simultaneous multiple exponentiations using the windowed 
* NAF-based interleaving method. See Section 3.2 in the paper "Algorithms for Multi-exponentiation"
* by Bodo Möller.
*/


/**
* \fn int get_biggest_bit_size(mpz_t *array, int length)
* \brief Auxliiary function for getting the giggest bit size in an array of multiple precision integers.
*
* \param array A pointer to an array of multiple precision integers.
* \param length The length of the array.
*/
int get_biggest_bit_size(mpz_t *array, int length);


/**
* \fn int getOptimalWVal(int m)
* \brief Auxliiary function for getting the optimal value of the parameter w depending on the bit size 
* of the exponent.
*
* \param m Bit size of the exponent.
*/
int getOptimalWVal(int m);


/**
* \fn void multi_exponentiation_precomputation(mpz_t **gE, mpz_t *g, unsigned int g_size, int w[], mpz_t mod)
* \brief It performs the precomputation for the simultaneous multiple exponentiations algorithm.
*
* \param gE A pointer to an array where the precomputations will be stored.
* \param g An array with the bases.
* \param g_size Number of elements in the array.
* \param w An array with the optimal parameter w for each base.
* \param mod The modulo.
*/
void multi_exponentiation_precomputation(mpz_t **gE, mpz_t *g, unsigned int g_size, int w[], mpz_t mod);


/**
* \fn void freePrecomp(mpz_t **matrix, unsigned int rows, unsigned int cols)
* \brief It clears the precomputation for the simultaneous multiple exponentiations algorithm and frees 
* allocated memory.
*
* \param matrix A pointer to the precomputations to be freed.
* \param rows The number of rows in the matrix.
* \param cols The number of columns in the matrix.
*/
void freePrecomp(mpz_t **matrix, unsigned int rows, unsigned int cols);


/**
* \fn void multiple_exponentiation(mpz_t result, size_t l, mpz_t *bases, mpz_t *exponents, mpz_t modulo)
* \brief It computes the simultaneous multiple exponentiations algorithm.
*
* \param result A multiple precision integer to store the result.
* \param l The amount of elements in the multiple exponentiation.
* \param bases An array of the bases for the multiple exponentiation.
* \param exponents An array of the exponents for the multiple exponentiation.
* \param modulo The modulo.
*/
void multiple_exponentiation(mpz_t result, size_t l, mpz_t *bases, mpz_t *exponents, mpz_t modulo);
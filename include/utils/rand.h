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
* \brief Functions for sampling the different random variables needed.
*/


/**
* \fn void geometric_search(mpz_t e, double p)
* \brief It samples a one-sided geometric with parameter p >= 1/3.
*
* \param e A multiple precision integer to store the result.
* \param p The parameter p.
*/
void geometric_search(mpz_t e, double p);


/**
* \fn void geometric_inversion(mpz_t e, double p)
* \brief It samples a one-sided geometric with parameter p < 1/3.
*
* \param e A multiple precision integer to store the result.
* \param p The parameter p.
*/
void geometric_inversion(mpz_t e, double p);


/**
* \fn void sample_one_sided_geometric(mpz_t e, double p)
* \brief It samples a one-sided geometric with any parameter p.
*
* \param e A multiple precision integer to store the result.
* \param p The parameter p.
*/
void sample_one_sided_geometric(mpz_t e, double p);


/**
* \fn void sample_geometric(mpz_t e, double epsilon, mpz_t bound, int Q)
* \brief It samples a two-sided geometric with the parameter 
* p = exp(-epsilon / (Q * bound_Y) ).
*
* \param e A multiple precision integer to store the result.
* \param epsilon The privacy budget for differential privacy.
* \param bound The bound for the linear functions to evaluate.
* \param Q The number of functional key queries supported.
*/
void sample_geometric(mpz_t e, double epsilon, mpz_t bound, int Q);


/**
* \fn void generate_seed(mpz_t result, size_t seed_size)
* \brief It generates a a secure multiple precision integer seed for random number 
* generation of size seed_size * 64.
*
* \param result A multiple precision integer to store the result.
* \param seed_size Number of bytes in the generated seed.
*/
void generate_seed(mpz_t result, size_t seed_size);
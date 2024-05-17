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
 * Sample a one-sided geometric with p >= 1/3
*/
void geometric_search(mpz_t e, double p);

/**
 * Sample a one-sided geometric with p < 1/3
*/
void geometric_inversion(mpz_t e, double p);

/**
 * Sample a discrete one-sided geometric distribution
*/
void sample_one_sided_geometric(mpz_t e, double p);

/**
 * Function for sampling a discrete double geometric distribution
*/
void sample_geometric(mpz_t e, double epsilon, mpz_t bound, int Q);

/**
* Function to generate a secure mpz seed for random number generation of size size_t * 64 
*/
void generate_seed(mpz_t result, size_t seed_size);
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

/**
* \file
* \ingroup utils
* \brief Function for computing discrete logarithm using the baby giant steps algorithm, in a 
* C version.
*/


/**
* \fn int baby_giant_2(mpz_t res, mpz_t h, mpz_t g, mpz_t p, mpz_t bound)
* \brief It computes the discrete logarithm modulo p.
*
* \param res A multiple precision integer to store the result.
* \param h The value from which the discrete logarithm is computed.
* \param g The base over which the discrete logarithm is computed.
* \param p The modulo over which the discrete logarithm is computed.
* \param bound A bound on the result of the discrete logarithm.
*/
int baby_giant_2(mpz_t res, mpz_t h, mpz_t g, mpz_t p, mpz_t bound);
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


/**
* \file
* \ingroup utils
* \brief Functions for performing fast modulo operations.
*/


/**
 *Function for adding two mpz modulo a number
*/
/**
* \fn void mpz_add_mod(mpz_t res, mpz_t a, mpz_t b, mpz_t modulo)
* \brief It adds two multiple precision integers with a modulo.
*
* \param res A multiple precision integer to store the result.
* \param a The first element to add.
* \param b The second element to add.
* \param modulo The modulo.
*/
void mpz_add_mod(mpz_t res, mpz_t a, mpz_t b, mpz_t modulo);


/**
* \fn void mpz_sub_mod(mpz_t res, mpz_t a, mpz_t b, mpz_t modulo)
* \brief It substracts two multiple precision integers with a modulo.
*
* \param res A multiple precision integer to store the result.
* \param a The first element of the substraction.
* \param b The element being substracted.
* \param modulo The modulo.
*/
void mpz_sub_mod(mpz_t res, mpz_t a, mpz_t b, mpz_t modulo);
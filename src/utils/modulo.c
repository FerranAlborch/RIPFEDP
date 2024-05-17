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
#include "utils/modulo.h"



void mpz_add_mod(mpz_t res, mpz_t a, mpz_t b, mpz_t modulo) {
    mpz_add(res, a, b);
    if(mpz_cmp(res, modulo) < 0) return;
    else {
        mpz_sub(res, res, modulo);
        return;
    }
}


void mpz_sub_mod(mpz_t res, mpz_t a, mpz_t b, mpz_t modulo) {
    mpz_sub(res, a, b);
    if(mpz_cmp(res, 0) >= 0) return;
    else {
        mpz_add(res, res, modulo);
        return;
    }
} 
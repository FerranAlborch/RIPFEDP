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
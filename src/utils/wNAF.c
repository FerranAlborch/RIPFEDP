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
#include "utils/wNAF.h"


void computewNAFRepresentation(wNAFRepresentation *naf, mpz_t num, int w) {
    int pow2wB = (1 << w);
       
    int i = 0;
       
    mpz_t n;
    mpz_init_set(n, num);
    mpz_t tmp;
    mpz_init(tmp);
       
    int sizeNi = mpz_sizeinbase(num, 2) + 1;
    // printf("SizeNi %d\n", sizeNi);
    int * ni = (int *) malloc(sizeNi * sizeof(int *));
    for(i=0; i<sizeNi; i++) {
        ni[i] = 0;
    }
       
    i = 0;
       
    while(mpz_cmp_si(n, 0) > 0 ) {
        if(mpz_tstbit(n, 0)==1) {// if odd
            ni[i] = mpz_mod_ui(tmp, n, pow2wB);
            // printf("ni[%d] = %d\n", i, ni[i]);
            mpz_sub_ui(n, n, ni[i]);
        }
           
        mpz_div_ui(n, n, 2);
        i++;
    }
       
        
    naf->naf = ni;
    naf->nafLength = i;
    naf->reqPreCompLen =  (1 << (w - 1));

    mpz_clears(n, tmp, NULL);

    // free(ni);
}


void freeNAF(wNAFRepresentation * naf) {
    free(naf->naf);
}
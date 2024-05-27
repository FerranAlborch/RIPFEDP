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

#include <stdbool.h>
#include <gmp.h>
#include "IPFE/fe_DDH.h"

/**
* \file
* \ingroup RIPFE
* \brief This is the secret-key randomized inner-product functional encryption in Section 4 
* from the paper "Computational Differential Privacy for Encrypted Databases Supporting Linear 
* Queries" by Alborch Escobar, Canard, Laguillaumie and Phan, based on the DDH scheme from 
* Section 3 from the paper "Adaptive simulation security for inner product functional encryption" 
* by Agrawal, Libert, Maitra and Titiu.
*/

/**
* \struct rfe_DDH rfe_DDH.h "RIPFE/rfe_DDH.h"
* \brief It represents the public parameters of the randomized inner-product scheme. 
*/
typedef struct rfe_DDH {
    fe_DDH s; /**< Public parameters of the non-randomized scheme. */
    float epsilon; /**< Privacy budget for the scheme. */
    int Q; /**< Number of functional key queries allowed. */
} rfe_DDH;

/**
* \struct rfe_DDH_sec_key rfe_DDH.h "RIPFE/rfe_DDH.h"
* \brief It represents a master secret key of the randomized inner-product scheme.
*/
typedef struct rfe_DDH_sec_key {
    fe_DDH_sec_key msk; /**< Master secret key of the non-randomized scheme. */
    mpz_t seed_u; /**< One-time pad u. */
} rfe_DDH_sec_key;

/**
* \struct rfe_DDH_fe_key rfe_DDH.h "RIPFE/rfe_DDH.h"
* \brief It represents a functional decryption key of the randomized inner-product scheme.
*/
typedef struct rfe_DDH_fe_key {
    fe_DDH_fe_key fe_key; /**< Functional decryption key of the non-randomized scheme. */
    mpz_t d; /**< Padded differentially private noise. */
    mpz_t zk; /**< Extra terms. */
} rfe_DDH_fe_key;

/**
* \fn bool rfe_DDH_precomp_init(rfe_DDH *S, size_t l, mpz_t bound_X, int Q, mpz_t bound_Y)
* \brief It initializes public parameters of the randomized inner-product scheme for a 
* precomputed set of safe prime values. 
*
* \param s A pointer to a fe_DDH structure.
* \param l The dimension of the vectors for the inner-product scheme.
* \param bound_X The bound on the plaintext inputs.
* \param Q The maximum number of functional queries to be asked.
* \param bound_Y the bound on the function.
*/
bool rfe_DDH_precomp_init(rfe_DDH *S, size_t l, mpz_t bound_X, int Q, mpz_t bound_Y);

/**
* \fn void rfe_DDH_free(rfe_DDH *S)
* \brief It clears public parameters of the randomized inner-product scheme and frees allocated memory.
*
* \param S A pointer to a rfe_DDH structure.
*/
void rfe_DDH_free(rfe_DDH *S);

/**
* \fn void rfe_DDH_sec_key_init(rfe_DDH_sec_key *MSK)
* \brief It initializes a master secret key of the randomized inner-product scheme.
*
* \param MSK A pointer to a rfe_DDH_sec_key structure.
*/
void rfe_DDH_sec_key_init(rfe_DDH_sec_key *MSK);

/**
* \fn void rfe_DDH_sec_key_free(rfe_DDH_sec_key *MSK)
* \brief It clears a master secret key of the randomized inner-product scheme and frees allocated memory.
*
* \param MSK A pointer to a rfe_DDH_sec_key structure.
*/
void rfe_DDH_sec_key_free(rfe_DDH_sec_key *MSK);

/**
* \fn void rfe_DDH_fe_key_init(rfe_DDH_fe_key *FE_key)
* \brief It initializes a functional decryption key of the randomized inner-product scheme.
*
* \param FE_key A pointer to a rfe_DDH_fe_key structure.
*/
void rfe_DDH_fe_key_init(rfe_DDH_fe_key *FE_key);

/**
* \fn void rfe_DDH_fe_key_free(rfe_DDH_fe_key *FE_key)
* \brief It clears a functional decryption key of the randomized inner-product scheme and frees 
* allocated memory.
*
* \param FE_key A pointer to a rfe_DDH_fe_key structure.
*/
void rfe_DDH_fe_key_free(rfe_DDH_fe_key *FE_key);

/**
* \fn void rfe_DDH_generate_master_keys(rfe_DDH_sec_key *MSK, rfe_DDH *S, double timesSetUp[])
* \brief It generates a master secret key for the randomized inner-product scheme.
*
* \param MSK A pointer to a rfe_DDH_sec_key structure.
* \param S A pointer to a rfe_DDH structure.
* \param timesSetUp An array to store the timings of this protocol.
*/
void rfe_DDH_generate_master_keys(rfe_DDH_sec_key *MSK, rfe_DDH *S, double timesSetUp[]);

/**
* \fn bool rfe_DDH_encrypt(fe_DDH_ciphertext *c, rfe_DDH *S, mpz_t *x, rfe_DDH_sec_key *MSK, double timesEnc[])
* \brief It encrypts a message following the randomized inner-product scheme.
*
* \param c A pointer to a fe_DDH_ciphertext structure.
* \param S A pointer to a rfe_DDH structure.
* \param x An array of multiple precision integers as plaintext message.
* \param MSK A pointer to a rfe_DDH_sec_key structure.
* \param timesEnc An array to store the timings of this protocol.
*/
bool rfe_DDH_encrypt(fe_DDH_ciphertext *c, rfe_DDH *S, mpz_t *x, rfe_DDH_sec_key *MSK, double timesEnc[]);

/**
* \fn bool rfe_DDH_derive_fe_key(rfe_DDH_fe_key *FE_key, rfe_DDH *S, rfe_DDH_sec_key *MSK, mpz_t *y, mpz_t e_verification, double timesKeyGen[])
* \brief It derives functional decryption keys following the randomized inner-product scheme.
*
* \param FE_key A pointer to a rfe_DDH_fe_key structure.
* \param S A pointer to a rfe_DDH structure.
* \param MSK A pointer to a rfe_DDH_fe_key structure.
* \param y An array of multiple precision integers as a function.
* \param e_verification A multiple precision integer to store the noise e for verification purposes.
* \param timesKeyGen An array to store the timings of this protocol.
*/
bool rfe_DDH_derive_fe_key(rfe_DDH_fe_key *FE_key, rfe_DDH *S, rfe_DDH_sec_key *MSK, mpz_t *y, mpz_t e_verification, double timesKeyGen[]);

/**
* \fn bool rfe_DDH_decrypt(mpz_t result, rfe_DDH *S, fe_DDH_ciphertext *ciphertext, rfe_DDH_fe_key *FE_key, mpz_t *y, double timesDec[])
* \brief It decrypts a ciphertext with a functional decryption key following the randomized inner-product 
* scheme.
*
* \param result A multiple precision integer to store the result.
* \param S A pointer to a rfe_DDH structure.
* \param ciphertext A pointer to a fe_DDH_ciphertext structure.
* \param FE_key A pointer to a rfe_key structure.
* \param y A pointer to a function array.
* \param timesDec An array to store the timings of this protocol.
*/
bool rfe_DDH_decrypt(mpz_t result, rfe_DDH *S, fe_DDH_ciphertext *ciphertext, rfe_DDH_fe_key *FE_key, mpz_t *y, double timesDec[]);
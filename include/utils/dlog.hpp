#include <gmp.h>

#ifdef __cpluplus
extern "C" {
#endif 

/**
* \file
* \ingroup utils
* \brief Function for computing discrete logarithm using the baby giant steps algorithm, in a 
* C++ version. Thi is to be able to use the standard C++ hash-map implementation.
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

#ifdef __cpluplus
}
#endif 
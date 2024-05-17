#include <functional>
#include <unordered_map>
#include <cstdint>
#include "utils/dlog.h"

#ifdef __cpluplus
extern "C" {
#endif 

class GMPInt{
public:
    mpz_t _val;

    GMPInt(){
        mpz_init(_val);
    }

    GMPInt(const mpz_t& x){
        mpz_init_set(_val, x);
    }

    GMPInt(int x){
        mpz_init_set_ui(_val, x);
    }

    GMPInt(const GMPInt& other){
        mpz_init_set(_val, other._val);
    }

    GMPInt& operator=(const GMPInt& other) {
        if (this != &other) {
            mpz_set(_val, other._val);
        }
        return *this;
    }

    ~GMPInt() {
        mpz_clear(_val);
    }

    // Define equality comparison for use by unordered_map
    bool operator==(const GMPInt& other) const {
        return mpz_cmp(_val, other._val) == 0;
    }
};

struct GmpHasher {
    std::size_t operator()(const GMPInt& k) const {
        // This is a simplistic approach; you might need a more sophisticated one.
        size_t hash_val = 0;
        mp_limb_t *limbs = k._val[0]._mp_d;
        size_t num_limbs = std::abs(k._val[0]._mp_size);
        for (size_t i = 0; i < num_limbs; ++i) {
            // Combine the hash of individual limbs.
            hash_val ^= std::hash<mp_limb_t>()(limbs[i]) + 0x9e3779b9;// + (hash_val << 6) + (hash_val >> 2);
        }
        return hash_val;
    }
};

#ifdef __cpluplus
extern }
#endif 

int baby_giant_2(mpz_t res, mpz_t h, mpz_t g, mpz_t p, mpz_t bound){
    mpz_t tmp, z;
    mpz_inits(tmp, z, NULL);

    int err = -1;

    uint64_t m;
    mpz_sqrt(tmp, bound);

    if(mpz_fits_ulong_p(tmp)){
        m = static_cast<uint64_t>(mpz_get_ui(tmp));
        m += 1;
    }else{
        return -1;
    }

    std::unordered_map<GMPInt, uint64_t, GmpHasher> map;
    map.reserve(m);
    GMPInt x;
    mpz_set_ui(x._val, 1);

    // mpz_t mu, q;
    // mpz_inits(mu, q, NULL);
    // precomp_b(mu, g, p);
    // size_t s = mpz_sizeinbase(p, 2);

    for(uint64_t i = 0 ; i < m ; ++i){
        map.insert({x, i});
        // mul_precomp_b(x._val, q, tmp, x._val, g, mu, p, s);
        mpz_mul(x._val, x._val, g);
        mpz_mod(x._val, x._val, p);
    }

    // mpz_clears(mu, q, NULL);

    mpz_invert(z, g, p);
    mpz_powm_ui(z, z, m, p);

    mpz_set(x._val, h);

    for(uint64_t i = 0 ; i < m ; ++i){
        auto it = map.find(x);
        if (it != map.end()){
            uint64_t r = i*m + it->second;
            mpz_set_ui(res, r);
            err = 0;
            break;
        }
        mpz_mul(x._val, x._val, z);
        mpz_mod(x._val, x._val, p);
    }

    mpz_clears(tmp, z, NULL);
    return err;
}
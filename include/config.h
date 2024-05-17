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


// LOOP defines how many times the experiment is performed to average afterwards
#define LOOP 10

// SEED_SIZE defines how long the secure randomness seeds will be, they are SEED_SIZE * 64 bits
#define SEED_SIZE 4

// MODULUS_LEN defines the security of the scheme, the higher the better
// for precomputed parameters it needs to be in {1024, 1536, 2048, 2560, 3072, 4096}
#define MODULUS_LEN 3072

// EPSILON defines the privacy budget of the scheme
#define EPSILON 0.1


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


/**
* \file Configuration
* \brief This file contains the configuration values for the schemes.
*/


/**
* \def LOOP
* \brief It defines how many times the experiment is performed to average afterwards.
*/
#define LOOP 10


/**
* \def SEED_SIZE
* \brief It defines how long the secure randomness seeds will be, they are SEED_SIZE * 64 bits.
*/
#define SEED_SIZE 4


/**
* \def MODULUS_LEN
* \brief It defines the security of the scheme, the higher the better. It needs to be in 
* {1024, 1536, 2048, 2560, 3072, 4096} for precomputed values.
*/
#define MODULUS_LEN 3072


/**
* \def EPSILON
* \brief It defines the privacy budget of the scheme.
*/
#define EPSILON 0.1


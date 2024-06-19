#
# Software Name : RIPFEDP
# Version: 1.1
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at 
#     http://www.apache.org/licenses/LICENSE-2.0 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Author: Ferran Alborch Escobar <ferran.alborch@gmail.com>
#

#!/bin/bash

# Install library?

# Compile the code
# make

# Execute the code for the preselected values
printf "Process for ell = 10 has begun.\n"
./RFEDP 10 16 24 7 > results/Output1.txt
printf "Process for ell = 10 has finished.\n\n"
printf "Process for ell = 100 has begun.\n"
./RFEDP 100 16 21 7 > results/Output2.txt
printf "Process for ell = 100 has finished.\n\n"
printf "Process for ell = 1000 has begun.\n"
./RFEDP 1000 16 18 7 > results/Output3.txt
printf "Process for ell = 1000 has finished.\n\n"
printf "Process for ell = 10000 has begun.\n"
./RFEDP 10000 16 16 7 > results/Output4.txt
printf "Process for ell = 10000 has finished.\n\n"
printf "Process for ell = 100000 has begun.\n"
./RFEDP 100000 16 16 7 > results/Output5.txt
printf "Process for ell = 100000 has finished.\n\n"
printf "Process for ell = 1000000 has begun.\n"
./RFEDP 1000000 16 16 7 > results/Output6.txt
printf "Process for ell = 1000000 has finished.\n\n"

make clean
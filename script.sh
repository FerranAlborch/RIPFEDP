#
# Software Name : RFEDP
# Version: 1.0
# SPDX-FileCopyrightText: Copyright (c) 2024[-2024] Orange Innovation
#
# This software is confidential and proprietary information of Orange Innovation.
# You shall not disclose such Confidential Information and shall not copy, use or distribute it
# in whole or in part without the prior written consent of Orange Innovation
#
# Author: Ferran Alborch Escobar
#

#!/bin/bash

# Install library?

# Compile the code
# make

# Execute the code for the preselected values
./RFEDP 10 16 24 7 > results/Output1.txt
./RFEDP 100 16 21 7 > results/Output2.txt
./RFEDP 1000 16 18 7 > results/Output3.txt
./RFEDP 10000 16 16 7 > results/Output4.txt
./RFEDP 100000 16 16 7 > results/Output5.txt
./RFEDP 1000000 16 16 7 > results/Output6.txt

make clean
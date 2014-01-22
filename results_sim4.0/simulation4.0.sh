#!/bin/bash


# RNG simulation 4.0

# varied (noisy) schema selection weights, basic WM implementation

# all parameter settings and conditions same as simulation 1



# simulation4_data.txt is data per subject (ie 36 rows per condition)
# - used for statistical tests (simulation3.R)
# see paper (eg., dissertation) for details of conditions (40, 33, 26, 18, 11, 4)

# simulation4_summary.txt is summary per condition including z-scores
# used for graphs (rng_graphs_main.R)
# Z-scores and SDs need to be processed using 'data - simulations3.ods' spreadsheet
# see that spreadsheet for details of conditions (40, 36, 32, 28, 24, 20, 16, 12, 8, 6, 4)



echo 'manipulating generation rate (interval = 40c ~ 3.0s)' >> simulation4_summary.txt
../rng -g 40 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation4_summary.txt
cat output_log.dat >> simulation4_data.txt


echo 'manipulating generation rate (interval = 36c ~ 3.0s)' >> simulation4_summary.txt
../rng -g 36 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation4_summary.txt



../rng -g 33 -u 0.98 -d 25 -m 0.11 -t 92 
cat output_log.dat >> simulation4_data.txt



echo 'manipulating generation rate (interval = 32c ~ 3.0s)' >> simulation4_summary.txt
../rng -g 32 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation4_summary.txt



echo 'manipulating generation rate (interval = 28c ~ 3.0s)' >> simulation4_summary.txt
../rng -g 28 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation4_summary.txt



../rng -g 26 -u 0.98 -d 25 -m 0.11 -t 92 
cat output_log.dat >> simulation4_data.txt




echo 'manipulating generation rate (interval = 24c ~ 3.0s)' >> simulation4_summary.txt
../rng -g 24 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation4_summary.txt





echo 'manipulating generation rate (interval = 20c ~ 3.0s)' >> simulation4_summary.txt
../rng -g 20 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation4_summary.txt



../rng -g 18 -u 0.98 -d 25 -m 0.11 -t 92 
cat output_log.dat >> simulation4_data.txt


echo 'manipulating generation rate (interval = 16c ~ 1.0s)' >> simulation4_summary.txt
./rng -g 16 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation4_summary.txt





echo 'manipulating generation rate (interval = 12c ~ 0.5s)' >> simulation4_summary.txt
./rng -g 13 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation4_summary.txt



../rng -g 11 -u 0.98 -d 25 -m 0.11 -t 92 
cat output_log.dat >> simulation4_data.txt


echo 'manipulating generation rate (interval = 8c ~ 0.5s)' >> simulation4_summary.txt
./rng -g 8 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation4_summary.txt


echo 'manipulating generation rate (interval = 6c ~ 0.5s)' >> simulation4_summary.txt
./rng -g 6 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation4_summary.txt


echo 'manipulating generation rate (interval = 4c ~ 0.5s)' >> simulation4_summary.txt
../rng -g 4 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation4_summary.txt
cat output_log.dat >> simulation4_data.txt



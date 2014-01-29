#!/bin/bash


# RNG simulation 2
# flat schema selection weights, ACT-R like WM implementation

# genetic algorithm converging - Jahanshahi 2006 condition 3


# simulation2_data.txt is data per subject (ie 36 rows per condition)
# - used for statistical tests (simulation2.R)
# see paper (eg., dissertation) for details of conditions (40, 33, 26, 18, 11, 4)

# simulation4_summary.txt is summary per condition including z-scores
# used for graphs (rng_graphs_main.R)
# Z-scores and SDs need to be processed using 'data - simulations3.ods' spreadsheet
# see that spreadsheet for details of conditions (40, 36, 32, 28, 24, 20, 16, 12, 8, 6, 4)


echo '---	rate	R	RNG	RG	CS1	CS2	CST	Associates' >> simulation2_summary.txt
echo 'R	RNG	RG	CS1	CS2	CST	A-9	A-8	A-7	A-6	A-5	A-4	A-3	A-2	A-1	A0	A1	A2	A3	A4	A5	A6	A7	A8	A9' >> simulation2_data.txt





#echo 'manipulating generation rate (interval = 40c ~ 3.0s)' >> simulation2_summary.txt
./rng -g 40 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2_summary.txt
cat output_log.dat >> simulation2_data.txt

#echo 'manipulating generation rate (interval = 34c ~ 2.5s)' >> simulation2_summary.txt
./rng -g 34 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2_summary.txt
cat output_log.dat >> simulation2_data.txt

# echo 'manipulating generation rate (interval = 32c )' >> simulation2.csv
# ./rng -g 32 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.csv

#echo 'manipulating generation rate (interval = 29c )' >> simulation2.01.txt
./rng -g 29 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2_summary.txt
cat output_log.dat >> simulation2_data.txt

# echo 'basic parameter settings (interval = 24c  ~ 1.5s)' >> simulation2.csv
# ./rng -g 24 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.csv

#echo 'manipulating generation rate (interval = 23c)' >> simulation2.01.txt
./rng -g 23 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2_summary.txt
cat output_log.dat >> simulation2_data.txt

# echo 'manipulating generation rate (interval = 20c)' >> simulation2.csv
# ./rng -g 20 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.csv

#echo 'manipulating generation rate (interval = 18c  ~ 1.0s)' >> simulation2.01.txt
./rng -g 18 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2_summary.txt
cat output_log.dat >> simulation2_data.txt

# echo 'manipulating generation rate (interval = 16c)' >> simulation2.csv
# ./rng -g 16 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.csv

# echo 'manipulating generation rate (interval = 14c)' >> simulation2.csv
# ./rng -g 14 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.csv

#echo 'manipulating generation rate (interval = 12c)' >> simulation2.01.txt
./rng -g 12 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2_summary.txt
cat output_log.dat >> simulation2_data.txt

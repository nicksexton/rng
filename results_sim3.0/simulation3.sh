#!/bin/bash


# RNG simulation 3
# individually varying schema selection weights, otherwise like sim2

# all parameter settings same as simulation 2




# condition - 40/3.0
echo 'manipulating generation rate (interval = 40c ~ 3.0s)' >> simulation3_summary.txt
../rng -g 40 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation3_summary.txt
cat output_log.dat >> simulation3_data.txt

echo 'manipulating generation rate (interval = 36c ~ 2.5s)' >> simulation3_summary.txt
../rng -g 36 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation3_summary.txt


# condition - 33/2.5
../rng -g 33 -u 1.0 -d 0.410 -m 0.36 -t 50.7
cat output_log.dat >> simulation3_data.txt


echo 'manipulating generation rate (interval = 32c )' >> simulation3_summary.txt
../rng -g 32 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation3_summary.txt
cat output_log.dat >> simulation3_data.txt

echo 'manipulating generation rate (interval = 28c )' >> simulation3_summary.txt
../rng -g 28 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation3_summary.txt
cat output_log.dat >> simulation3_data.txt


#condition - 26/2.0
../rng -g 26 -u 1.0 -d 0.410 -m 0.36 -t 50.7
cat output_log.dat >> simulation3_data.txt


echo 'basic parameter settings (interval = 24c  ~ 1.5s)' >> simulation3_summary.txt
../rng -g 24 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation3_summary.txt


echo 'manipulating generation rate (interval = 22c)' >> simulation3_summary.txt
../rng -g 22 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation3_summary.txt


echo 'manipulating generation rate (interval = 20c)' >> simulation3_summary.txt
../rng -g 20 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation3_summary.txt



#condition - 18/1.5
echo 'manipulating generation rate (interval = 18c  ~ 1.0s)' >> simulation3_summary.txt
../rng -g 18 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation3_summary.txt
cat output_log.dat >> simulation3_data.txt

echo 'manipulating generation rate (interval = 16c)' >> simulation3_summary.txt
../rng -g 16 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation3_summary.txt


echo 'manipulating generation rate (interval = 14c)' >> simulation3_summary.txt
../rng -g 14 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation3_summary.txt


echo 'manipulating generation rate (interval = 12c)' >> simulation3_summary.txt
../rng -g 12 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation3_summary.txt
cat output_log.dat >> simulation3_data.txt


# condition - 11/1.0
../rng -g 11 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation3_summary.txt
cat output_log.dat >> simulation3_data.txt


# condition - 4/0.5
../rng -g 4 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation3_summary.txt
cat output_log.dat >> simulation3_data.txt
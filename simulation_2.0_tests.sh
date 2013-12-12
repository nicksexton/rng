#!/bin/bash


# RNG simulation 2
# flat schema selection weights, ACT-R like WM implementation

# genetic algorithm converging - Jahanshahi 2006 condition 3





echo 'manipulating generation rate (interval = 40c ~ 3.0s)' >> simulation2.01.txt
./rng -g 40 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.01.txt
cat output_log.dat >> simulation2.01_data.txt

echo 'manipulating generation rate (interval = 34c ~ 2.5s)' >> simulation2.01.txt
./rng -g 34 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.01.txt
cat output_log.dat >> simulation2.01_data.txt

# echo 'manipulating generation rate (interval = 32c )' >> simulation2.csv
# ./rng -g 32 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.csv

echo 'manipulating generation rate (interval = 29c )' >> simulation2.01.txt
./rng -g 29 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.01.txt
cat output_log.dat >> simulation2.01_data.txt

# echo 'basic parameter settings (interval = 24c  ~ 1.5s)' >> simulation2.csv
# ./rng -g 24 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.csv

echo 'manipulating generation rate (interval = 23c)' >> simulation2.01.txt
./rng -g 23 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.01.txt
cat output_log.dat >> simulation2.01_data.txt

# echo 'manipulating generation rate (interval = 20c)' >> simulation2.csv
# ./rng -g 20 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.csv

echo 'manipulating generation rate (interval = 18c  ~ 1.0s)' >> simulation2.01.txt
./rng -g 18 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.01.txt
cat output_log.dat >> simulation2.01_data.txt

# echo 'manipulating generation rate (interval = 16c)' >> simulation2.csv
# ./rng -g 16 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.csv

# echo 'manipulating generation rate (interval = 14c)' >> simulation2.csv
# ./rng -g 14 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.csv

echo 'manipulating generation rate (interval = 12c)' >> simulation2.01.txt
./rng -g 12 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2.01.txt
cat output_log.dat >> simulation2.01_data.txt

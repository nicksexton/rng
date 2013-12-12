#!/bin/bash


# RNG simulation 2
# flat schema selection weights, ACT-R like WM implementation

# genetic algorithm converging - Jahanshahi 2006 condition 3





echo 'manipulating generation rate (interval = 40c ~ 3.0s)' >> simulation2all.csv
./rng -g 40 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2all.csv

echo 'manipulating generation rate (interval = 36c ~ 2.5s)' >> simulation2all.csv
./rng -g 36 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2all.csv

echo 'manipulating generation rate (interval = 32c )' >> simulation2all.csv
./rng -g 32 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2all.csv

echo 'manipulating generation rate (interval = 28c )' >> simulation2all.csv
./rng -g 28 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2all.csv

echo 'basic parameter settings (interval = 24c  ~ 1.5s)' >> simulation2all.csv
./rng -g 24 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2all.csv

echo 'manipulating generation rate (interval = 22c)' >> simulation2all.csv
./rng -g 22 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2all.csv

echo 'manipulating generation rate (interval = 20c)' >> simulation2all.csv
./rng -g 20 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2all.csv

echo 'manipulating generation rate (interval = 18c  ~ 1.0s)' >> simulation2all.csv
./rng -g 18 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2all.csv

echo 'manipulating generation rate (interval = 16c)' >> simulation2all.csv
./rng -g 16 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2all.csv

echo 'manipulating generation rate (interval = 14c)' >> simulation2all.csv
./rng -g 14 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2all.csv

echo 'manipulating generation rate (interval = 12c)' >> simulation2all.csv
./rng -g 12 -u 1.0 -d 0.410 -m 0.36 -t 50.7 >> simulation2all.csv


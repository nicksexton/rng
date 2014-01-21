#!/bin/bash


# RNG simulation 1.1
# flat schema selection weights, basic WM implementation

# genetic algorithm converging - Jahanshahi 2006 condition 3





echo 'manipulating generation rate (interval = 28c ~ 3.0s)' >> simulation1.csv
./rng -g 28 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation1.csv

echo 'manipulating generation rate (interval = 25c ~ 2.5s)' >> simulation1.csv
./rng -g 25 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation1.csv

echo 'basic parameter settings (interval = 22c ~ 2.0s)' >> simulation1.csv
./rng -g 22 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation1.csv

echo 'basic parameter settings (interval = 19c ~ 1.5s)' >> simulation1.csv
./rng -g 19 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation1.csv

echo 'manipulating generation rate (interval = 16c ~ 1.0s)' >> simulation1.csv
./rng -g 16 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation1.csv

echo 'manipulating generation rate (interval = 13c ~ 0.5s)' >> simulation1.csv
./rng -g 13 -u 0.98 -d 25 -m 0.11 -t 92 >> simulation1.csv


echo 'note problem - excessive production of +2 responses' >> simulation1.csv
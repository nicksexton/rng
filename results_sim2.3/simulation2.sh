#!/bin/bash


# RNG simulation 3
# individually varying schema selection weights, otherwise like sim2

# all parameter settings same as simulation 2


# simulation3_data.txt is data per subject (ie 36 rows per condition)
# - used for statistical tests (simulation3.R)

# simulation3_summary.txt is summary per condition including z-scores
# used for graphs (rng_graphs_main.R)
# Z-scores and SDs need to be processed using 'data - simulations3.ods' spreadsheet


echo '---	rate	R	RNG	RG	CS1	CS2	CST	Associates' >> simulation2_summary.txt
echo 'R	RNG	RG	CS1	CS2	CST	A-9	A-8	A-7	A-6	A-5	A-4	A-3	A-2	A-1	A0	A1	A2	A3	A4	A5	A6	A7	A8	A9' >> simulation2_data.txt

UPDATING=1.0
DECAY=40
MONITORING=0.09
TEMPERATURE=10



../rng -g 40 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> simulation2_summary.txt
cat output_log.dat >> simulation2_data.txt


../rng -g 36 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> simulation2_summary.txt



../rng -g 34 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE 
cat output_log.dat >> simulation2_data.txt


../rng -g 32 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> simulation2_summary.txt


../rng -g 29 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE 
cat output_log.dat >> simulation2_data.txt

../rng -g 28 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> simulation2_summary.txt


../rng -g 24 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> simulation2_summary.txt


../rng -g 23 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> simulation2_summary.txt
cat output_log.dat >> simulation2_data.txt



../rng -g 22 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> simulation2_summary.txt


../rng -g 20 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> simulation2_summary.txt


../rng -g 18 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> simulation2_summary.txt
cat output_log.dat >> simulation2_data.txt


../rng -g 16 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> simulation2_summary.txt

../rng -g 14 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> simulation2_summary.txt


../rng -g 12 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> simulation2_summary.txt
cat output_log.dat >> simulation2_data.txt








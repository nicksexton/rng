#!/bin/bash


# RNG simulations 1.3, 4.3

# genetic algorithm - 20 generations
# intvl 23, thrsh 10, mon .339, updt .704


# simulation1_data.txt is data per subject (ie 36 rows per condition)
# - used for statistical tests (simulation3.R)
# see paper (eg., dissertation) for details of conditions (40, 33, 26, 18, 11, 4)

# simulation1_summary.txt is summary per condition including z-scores
# used for graphs (rng_graphs_main.R)
# Z-scores and SDs need to be processed using 'data - simulations3.ods' spreadsheet
# see that spreadsheet for details of conditions (40, 36, 32, 28, 24, 20, 16, 12, 8, 6, 4)

SUMMARYDATA="simulation4_summary.txt"
TRIALSDATA="simulation4_data.txt"
ZSCORES="simulation4_summary_zscores.txt" # for plotting main DV graphs 


echo 'R	RNG	RG	CS1	CS2	CST	A-9	A-8	A-7	A-6	A-5	A-4	A-3	A-2	A-1	A0	A1	A2	A3	A4	A5	A6	A7	A8	A9' >> $TRIALSDATA
echo 'stat	rate	R	RNG	RG	CS1	CS2	CST	A-9	A-8	A-7	A-6	A-5	A-4	A-3	A-2	A-1	A0	A1	A2	A3	A4	A5	A6	A7	A8	A9' >> $ZSCORES
echo 'stat	rate	R	RNG	RG	CS1	CS2	CST	A-9	A-8	A-7	A-6	A-5	A-4	A-3	A-2	A-1	A0	A1	A2	A3	A4	A5	A6	A7	A8	A9' >> $SUMMARYDATA

UPDATING=1.0
DECAY=40
MONITORING=0.09
TEMPERATURE=10


../rng -g 40 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> $SUMMARYDATA
cat output_log.dat >> $TRIALSDATA


../rng -g 36 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> $SUMMARYDATA


../rng -g 33 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE 
cat output_log.dat >> $TRIALSDATA


../rng -g 32 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> $SUMMARYDATA


../rng -g 28 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> $SUMMARYDATA


../rng -g 26 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE 
cat output_log.dat >> $TRIALSDATA


../rng -g 24 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> $SUMMARYDATA



../rng -g 20 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> $SUMMARYDATA


../rng -g 18 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE 
cat output_log.dat >> $TRIALSDATA


../rng -g 16 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> $SUMMARYDATA



../rng -g 13 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> $SUMMARYDATA



../rng -g 11 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE 
cat output_log.dat >> $TRIALSDATA


../rng -g 8 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> $SUMMARYDATA


../rng -g 6 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> $SUMMARYDATA


../rng -g 4 -u $UPDATING -d $DECAY -m $MONITORING -t $TEMPERATURE | awk 'NF' >> $SUMMARYDATA
cat output_log.dat >> $TRIALSDATA

grep 'Z' $SUMMARYDATA >> $ZSCORES
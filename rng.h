#ifndef _rng_h_

#define _rng_h_

#include <stdio.h>
#include <math.h>
#include <glib.h>
#include "lib_string.h"
#include "oos.h"

// NS 2013-07-21 remove if volatile
// #include "rng_subject_data.h"


#undef DEBUG


/* Note - for Monte Carlo pseudorandom sims, change MAX_SUBJECTS to eg. 1000 */
#define MAX_SUBJECTS 10000 // for rng cognitive simulation, use 36
#define MAX_TRIALS  250

typedef struct rng_scores {
    Boolean display_if_true;
    double r;
    double rng;
    double tpi;
    double rg;
    double cs1;
    double cs2;
    double cst;
    double associates[19];

} RngScores;




typedef struct activation_parameters {
  double act_self;
  double act_next;
  double act_prev;
  double act_inhi;
  double persistence;
} ActParameters;

typedef struct rng_parameters {
    double temperature;
    double monitoring_efficiency;
    double wm_update_rate;
    double wm_threshold;
    int    generation_period; 
    ActParameters activation_parameters;
} RngParameters;


typedef struct rng_subject_data {
    int n;
    int response[MAX_TRIALS];
  
    // testing variable schema strengths
    double ** my_schema_strengths;

    RngScores scores;
} RngSubjectData;


typedef struct rng_data {
    RngParameters  params;
    RngSubjectData trial[MAX_SUBJECTS];
    RngScores group_means;
    RngScores group_sd;
    int n;
} RngData;


typedef struct rng_dataset {
  RngScores subject_c1_means;
  RngScores subject_c2_means;
  RngScores subject_c3_means;
  RngScores subject_c4_means;
  RngScores subject_c5_means;
  RngScores subject_c6_means;
  RngScores subject_c1_sd;
  RngScores subject_c2_sd;
  RngScores subject_c3_sd;
  RngScores subject_c4_sd;
  RngScores subject_c5_sd;
  RngScores subject_c6_sd;
  RngScores subject_ctl_means;   // NB defining ctrl group important for calculating z scores
                                  // could do by pointer to selected ctrl condition?
  RngScores subject_ctl_sd;
} RngDataset;


extern RngScores subject_ctl_means;
extern RngScores subject_ctl_sd;


// extern RngDataset dataset_jahanshahi_2006;
// extern RngDataset dataset_towse_1998;





extern void rng_analyse_group_data(OosVars *gv, FILE *fp, RngScores *zscore_ref_means, RngScores *zscore_ref_sd);
extern void rng_print_scores(FILE *fp, RngScores *scores);
extern void rng_print_subject_sequence(FILE *fp, RngSubjectData *subject, int n);
extern void rng_analyse_subject_responses(FILE *fp, OosVars *gv, int id);
 Boolean rng_create(OosVars *gv, RngParameters *pars);
extern void rng_initialise_model(OosVars *gv);
extern void rng_globals_destroy(RngData *task_data);
extern void rng_run(OosVars *gv);
extern Boolean oos_step_wrapper(OosVars *gv);
extern void fprint_rng_scores(FILE *fp, RngScores *score);
extern void rng_score_subject_data(RngSubjectData *subject, int trials);
extern void rng_scores_convert(RngScores *means, RngScores *reference_means, RngScores *reference_sd, RngScores *z_scores);
extern void rng_sd_convert(RngScores *before, RngScores *reference_sd, RngScores *after);
extern double rng_global_fit_max(RngScores *data, RngScores *reference_sd, RngScores *model);

extern void rng_print_schema_selection_probabilities(FILE *fp, double temperature);

#endif

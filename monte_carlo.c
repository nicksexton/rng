/*******************************************************************************

    File:     monte_carlo.c
    Author:   Nick Sexton
    Created:  06/07/13
    Edited:   
    Contents: Uses the RNG model & data analysis to generate & analyse 100-item
              pseudorandom sequences according to various metrics. Can do set sizes
              of 9 and 10 (to compare with Jahanshahi & Towse data)

    Arguments: if a text file is supplied as an argument, program will
    treat it as random source file and use it to fill subject
    responses. WARNING - NOT ROBUST - file should consist of single
    integer per line, and should be long enough


       

*******************************************************************************/

/* Note - need to change #define MAX_SUBJECTS in rng.h to a bigger number for production of Monte-Carlo stats */

#include "rng.h"
#include <gsl/gsl_rng.h>

#define NUMBER_OF_TRIALS 100
#define LOWER_BOUND 1
#define UPPER_BOUND 9

/* need a container to hold RNG stats as gv not available */


gsl_rng * random_generator_create ()
{
  gsl_rng * r;
  const gsl_rng_type *R;
  R = gsl_rng_default;
  r = gsl_rng_alloc (R);
  gsl_rng_env_setup ();
  // gsl_rng_set (r, time(0));  // set random seed, default is 0, prob ok for this application
  return r;
}


void random_generator_destroy (gsl_rng *r)
{
  gsl_rng_free (r);
}


/* generates 100 responses using pseudorandom function */
void generate_random_responses ( RngSubjectData *this_subject_data, unsigned long int lower, unsigned long int upper, gsl_rng *random_generator)
{
  int i;

  for (i = 0; i < NUMBER_OF_TRIALS; i++) {
    this_subject_data->response[i] = lower + (gsl_rng_uniform_int (random_generator, upper - lower));
  }
 
}



int fill_random_responses_from_file ( RngSubjectData *this_subject_data, FILE *random_source_file)
{
  /* expects file format of 1 integer per line. Note checking for EOF
     does not work so need to ensure all subjects data is filled
     manually! */

  char file_buffer [8];
  int trial = 0;
  int response = 0;
  int * response_iterator;
  response_iterator = &(this_subject_data->response[0]);
  
  while (fgets (file_buffer, 8, random_source_file) && trial < NUMBER_OF_TRIALS) {
    if (file_buffer[0] == ';' || file_buffer[0] == '#') {                 // ignore comments
      continue;
    }
    
    /* doesn't work - need to fix! */
    if (feof(random_source_file)) {
      printf ("End of file reached!\n");
      return (1);
    
    }
    response = file_buffer[0] - '0';
    if (response >= LOWER_BOUND && response <= UPPER_BOUND) {
      *response_iterator = response;
      trial ++;
    }
    response_iterator = &(this_subject_data->response[trial]);
    
  }
  /* put error condition in here - check that all subjects
	   responses have been filled (and not just that file has
	   finished) */
	
  return 0;
}


/* function copied from rng_analyse_group_data in rng_analyse.c to handle RngData as an argument type */
void analyse_group_data(RngData *group_data)
{
    RngScores sum, ssq;
    int i, k;

    group_data->n = MAX_SUBJECTS;

    sum.r = 0.0;
    sum.rng = 0.0;
    sum.tpi = 0.0;
    sum.rg = 0.0;
    sum.cs1 = 0; 
    sum.cs2 = 0;
    sum.cst = 0;
    for (k = 0; k < 19; k++) {
        sum.associates[k] = 0.0;
    }

    ssq.r = 0.0;
    ssq.rng = 0.0;
    ssq.tpi = 0.0;
    ssq.rg = 0.0;
    ssq.cs1 = 0;
    ssq.cs2 = 0;
    ssq.cst = 0;
    for (k = 0; k < 19; k++) {
        ssq.associates[k] = 0.0;
    }

    for (i = 0; i < group_data->n; i++) {
        RngSubjectData *subject = &(group_data->trial[i]);

        sum.r += subject->scores.r;
        ssq.r += (subject->scores.r*subject->scores.r);
        sum.rng += subject->scores.rng;
        ssq.rng += (subject->scores.rng*subject->scores.rng);
        sum.tpi += subject->scores.tpi;
        ssq.tpi += (subject->scores.tpi*subject->scores.tpi);
        sum.rg += subject->scores.rg;
        ssq.rg += (subject->scores.rg*subject->scores.rg);

	/* Jahanshahi metrics*/
	sum.cs1 += subject->scores.cs1;
	ssq.cs1 += (subject->scores.cs1 * subject->scores.cs1);
	sum.cs2 += subject->scores.cs2;
	ssq.cs2 += (subject->scores.cs2 * subject->scores.cs2);	
	sum.cst += subject->scores.cst;
	ssq.cst += (subject->scores.cst * subject->scores.cst);

        for (k = 0; k < 19; k++) {
            sum.associates[k] += subject->scores.associates[k];
            ssq.associates[k] += (subject->scores.associates[k]*subject->scores.associates[k]);
        }
    }
    if (group_data->n > 0) {
        group_data->group_means.r = sum.r / (double) group_data->n;
        group_data->group_means.rng = sum.rng / (double) group_data->n;
        group_data->group_means.tpi = sum.tpi / (double) group_data->n;
        group_data->group_means.rg = sum.rg / (double) group_data->n;
	group_data->group_means.cs1 = sum.cs1 / (double) group_data->n;
	group_data->group_means.cs2 = sum.cs2 / (double) group_data->n;
	group_data->group_means.cst = sum.cst / (double) group_data->n;
        for (k = 0; k < 19; k++) {
            group_data->group_means.associates[k] = sum.associates[k] / (double) group_data->n;
        }
    }
    if (group_data->n > 1) {
        group_data->group_sd.r = sqrt((ssq.r - (sum.r*sum.r/ (double) group_data->n))/((double) group_data->n - 1));
        group_data->group_sd.rng = sqrt((ssq.rng - (sum.rng*sum.rng/ (double) group_data->n))/((double) group_data->n - 1));
        group_data->group_sd.tpi = sqrt((ssq.tpi - (sum.tpi*sum.tpi/ (double) group_data->n))/((double) group_data->n - 1));
        group_data->group_sd.rg = sqrt((ssq.rg - (sum.rg*sum.rg/ (double) group_data->n))/((double) group_data->n - 1));
	group_data->group_sd.cs1 = sqrt((ssq.cs1 - (sum.cs1*sum.cs1/ (double) group_data->n))/((double) group_data->n - 1));
	group_data->group_sd.cs2 = sqrt((ssq.cs2 - (sum.cs2*sum.cs2/ (double) group_data->n))/((double) group_data->n - 1));
	group_data->group_sd.cst = sqrt((ssq.cst - (sum.cst*sum.cst/ (double) group_data->n))/((double) group_data->n - 1));

        for (k = 0; k < 19; k++) {
            group_data->group_sd.associates[k] = sqrt((ssq.associates[k]- (sum.associates[k]*sum.associates[k]/ (double) group_data->n))/((double) group_data->n - 1));
        }
    }


}




int main (int argc, char **argv)
{

  FILE *fp;
  FILE *fp_random_source_file;

    /* Uncomment one of the following to save trial-by-trial output */
//    fp = NULL; /* Supress output */
    fp = stdout; /* Send output to the terminal */
//    fp = fopen("output_log.dat", "w"); /* Save output to output_log.dat file */

  RngData * monte_carlo_data;
  gsl_rng * random_generator;
  


  if ((monte_carlo_data = malloc (sizeof (RngData))) == NULL) {
    fprintf (stdout, "ABORTING: Cannot allocate memory\n");
  }

  else if ((random_generator = random_generator_create()) == NULL) {
    fprintf (stdout, "ABORTING: Cannot create random generator\n");
  }

  else {

    /* main code goes here */

    /* If a txt file is included as an argument, use that for random number source */
    if (argc > 1) {

      if ((fp_random_source_file = fopen (argv[1], "r")) == NULL) {
	   printf ("error - could not open file!\n");
	   exit (1);
      }
	
      else {
	printf ("success! opened file\n");
	/* process file input here */
	int i;
	for (i = 0; i < MAX_SUBJECTS; i++) {
	fill_random_responses_from_file (&(monte_carlo_data->trial[i]), fp_random_source_file);
	
	rng_print_subject_sequence (fp, &(monte_carlo_data->trial[i]), NUMBER_OF_TRIALS);
	rng_score_subject_data (&(monte_carlo_data->trial[i]), NUMBER_OF_TRIALS);
	rng_print_scores (fp, &(monte_carlo_data->trial[i].scores));

	}
      }
    }


/* else, use pseudorandom generator */
    else {
      int i;
      for (i = 0; i < MAX_SUBJECTS; i++) {
	generate_random_responses (&(monte_carlo_data->trial[i]), LOWER_BOUND, UPPER_BOUND+1, random_generator);
	
	// rng_print_subject_sequence (fp, &(monte_carlo_data->trial[i]), NUMBER_OF_TRIALS);
	rng_score_subject_data (&(monte_carlo_data->trial[i]), NUMBER_OF_TRIALS);
	// rng_print_scores (fp, &(monte_carlo_data->trial[i].scores));
	
      }
    }
    
    analyse_group_data (monte_carlo_data);
    
    /* Print group data */

    fprintf(fp, "Stats: set %d-%d, n=%d\n", LOWER_BOUND, UPPER_BOUND, MAX_SUBJECTS);    
    fprintf(fp, "\tR\tRNG\tRG\tCS1\tCS2\tCST\tAssociates\n");
    fprintf(fp, "Mean:\t");    
    fprint_rng_scores(fp, &(monte_carlo_data->group_means));
    fprintf(fp, "SD:\t");
    fprint_rng_scores(fp, &(monte_carlo_data->group_sd)); 




  random_generator_destroy (random_generator);
  g_free (monte_carlo_data);
  }

  
  exit (0);
}

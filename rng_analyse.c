#include "rng.h"

// commented 2013-07-21
// #include "rng_subject_data.h"

// #define PRINT_DIFFERENCE_MATRIX
#undef  PRINT_DIFFERENCE_MATRIX
#define SET_SIZE 10.0




typedef enum cs_type {
  CS1, CS2
} CsType;


/*----------------------------------------------------------------------------*/

static double calculate_mean(int list[], int i)
{
    int sum = 0, n;

    for (n = 0; n < i; n++) {
        sum += list[n];
    }
    return(sum / (double) i);
}

int compare_integers ( const void * p1, const void * p2)
{
  int x = *(int *)p1;
  int y = *(int *)p2;
  return (x < y) ? -1 : ((x == y) ? 0 : 1);
}

static double calculate_median (int list[], int i)
{
  int index_middle;
  int index_middle_upper;
 
/* could return int? return type double retained for legacy compatability */
  qsort (&(list[0]), i, sizeof(int), compare_integers );
  if ((i % 2) == 1) {
    index_middle = (i - 1) / 2;
    return list[index_middle];
  }
  else {
    index_middle = (i / 2) - 1;
    index_middle_upper = (i / 2);
    return ((list[index_middle] + list[index_middle_upper]) / 2);
  }
}




static Boolean is_count (int step_size, int n1, int n2)
{

  if (n2 == (n1-step_size) || n2 == (n1+step_size)) {
    return (TRUE);
  }
  else return (FALSE);

}

/* see Jahanshahi 1998. nb. How to handle wrapping? ie. is 9-0-1-2 a
   consecutive sequence? Current implementation - does not count as
   counting. */
static double calculate_metric_cs(CsType cs_type, int rg_list[], int trials)
{
  int i, n1, n2;
  int length_of_consecutive_string = 0;
  int count_score = 0;
 

  for (i = 1; i < trials; i++) {
    n1 = rg_list[i-1];
    n2 = rg_list[i];

    switch (cs_type){
    case CS1: {
       if (is_count(1, n1, n2))
	{
	  length_of_consecutive_string ++;
	}
      else if (length_of_consecutive_string > 0) {
	count_score += (length_of_consecutive_string * length_of_consecutive_string);
	length_of_consecutive_string = 0;
      }
      break;
    }

    case CS2: {
      if (is_count(2, n1, n2))
	{
	  length_of_consecutive_string ++;
	}
      else if (length_of_consecutive_string > 0) {
	count_score += (length_of_consecutive_string * length_of_consecutive_string);
	length_of_consecutive_string = 0;
      }
      break;
    }
    }
 
  }

  if (length_of_consecutive_string > 0) {
    count_score += (length_of_consecutive_string * length_of_consecutive_string);
  }
  return (count_score);
}
      

    



// static void rng_score_subject_data(RngSubjectData *subject, int trials)
void rng_score_subject_data(RngSubjectData *subject, int trials)
{
    /* Read a data file and return the various RNG dvs. */
    /* Also return misses (times participant failed to generate a response) */
    /* and hits (responses generated, excluding misses). */

    int f[10], ff[10][10], last[10];
    int rg_list[MAX_TRIALS];
    double rt, rt_sum, sum, h_s, h_m;
    double num, denom;
    long v1, v2, fr, k;
    int tp_direction, tp_count, n, d, i, j;
    int hits = 0, misses = 0;

    for (v1 = 0; v1 < 10; v1++) {
        f[v1] = 0;
        last[v1] = -1;
        for (v2 = 0; v2 < 10; v2++) {
            ff[v1][v2] = 0;
        }
    }

    /* Score the data: */

    v1 = -1; fr = -1; tp_direction = 0; n = 0; i = 0; tp_count = 0; rt_sum = 0.0;

    for (j = 0; j < trials; j++) {
        v2 = subject->response[j];
        rt = 0.0; // TO DO: Handle RT?

        rt_sum += rt;
        /* Record the first valid response, for wrap-around: */
        if ((v2 >= 0) && (fr == -1)) {
            fr = v2;
        }

        /* Score hits and misses, and count frequencies for hits: */
        if (v2 < 0) {
            misses++;
        }
        else {
            hits++;
            f[v2]++;
        }

        /* Count frequencies for pairs: */
        if ((v1 >= 0) && (v2 >= 0)) {
            ff[v1][v2]++;
        }

        /* Score turning points: */
        d = (v2 < v1) ? (v2 + 10 - v1) : (v2 - v1);
        if ((v1 >= 0) && (d != 0)) {
            if ((tp_direction == 0) && (d != 5)) {
                /* First response ... just set the initial direction: */
                tp_direction = (d > 5) ? -1 : 1;
            }
            else if ((tp_direction > 0) && (d > 5)) {
                /* Sequence was going clockwise, but is no longer: */
                tp_direction = -1;
                tp_count++;
            }
            else if ((tp_direction < 0) && (d < 5)) {
                /* Sequence was going counter-clockwise, but is no longer: */
                tp_direction = +1;
                tp_count++;
            }
        }

        if (v2 >= 0) {
            /* If v2 is -1 we ignore this in ff; */
            v1 = v2;
        }

        if ((v2 >= 0) && (i < trials)) {
            if (last[v2] == -1) {
                last[v2] = n;
            }
            else {
                rg_list[i++] = n - last[v2];
                last[v2] = n;
            }
        }

        n++;
    }

    /* Add in the wrap-around: */
    if ((fr >= 0) && (v2 >= 0)) {
        ff[v2][fr]++;
    }

    /* Calculation of R: */
    sum = 0.0;
    for (v1 = 0; v1 < 10; v1++) {
        if (f[v1] > 1) {
            sum = sum + f[v1] * log(f[v1]) / log(2.0);
        }
    }
    h_s = log(hits) / log(2.0) - (1.0 / (double) (hits)) * sum;
    h_m = log(SET_SIZE) / log(2.0);

    subject->scores.r = 100.0 * (1 - h_s / h_m);

    /* Calculation of RNG: */
    num = 0.0;
    denom = 0.0;

    for (v1 = 0; v1 < 10; v1++) {
        for (v2 = 0; v2 < 10; v2++) {
            if (ff[v1][v2] > 1) {
                num = num + ff[v1][v2] * log(ff[v1][v2]) / log(2.0);
            }
        }
        if (f[v1] > 1) {
            denom = denom + f[v1] * log(f[v1]) / log(2.0);
        }
    }
    subject->scores.rng = num / denom;

    /* DEBUG - print out ff matrix */
#ifdef PRINT_DIFFERENCE_MATRIX

    int j_total[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int i_total = 0;
    printf ("\nDigram Associate Matrix\n\t");
    for (j = 0; j < 10; j++) { printf ("%d   ", j); }
    /* print divider to look nice */
    printf ("\n\t");
    for (j = 0; j < 10; j++) { printf ("--  "); }
    printf ("\n");
    for (i = 0; i < 10; i++) {
      printf ("%d:\t", i);
      for (j = 0; j < 10; j++) {
	printf ("%d,  ", ff[i][j]);
	i_total += ff[i][j];
	j_total[i] += ff[i][j];
      }
      printf ("\t: %d \n", i_total);
      i_total = 0;
    }
    /* print divider to look nice */
    printf ("\t");
    for (j = 0; j < 10; j++) { printf ("--  "); }
    /* print totals */
    printf ("\n\t");
    for (j = 0; j < 10; j++) 
      { if (j_total[j]<10) 
	  printf ("%d   ", j_total[j]);
	else 
	  printf ("%d  ", j_total[j]); }
    printf ("\n");
#endif


    /* Calculation of associates (RR, OA, AA, etc.): */

    /* for associate k, k9 = k+9 ie index of associates[] 
       in other words, associate 0 = associates[9] */

    for (k = -9; k < 10; k++) {
        num = 0.0;
        denom = 0.0;
        for (v1 = 0; v1 < 10; v1++) {
	  if (((v1+k) >= 0) && ((v1+k) <= 9))
	    {
	      num = num + ff[v1][(v1 + k)];
      	    }
	  denom = denom + f[v1];
        }
        subject->scores.associates[k+9] = num / denom;
    }

    /*
    for (k = 0; k < 10; k++) {
        num = 0.0;
        denom = 0.0;
        for (v1 = 0; v1 < 10; v1++) {
            num = num + ff[v1][(v1 + k) % 10];
            denom = denom + f[v1];
        }
        subject->scores.associates[k] = num / denom;
    }
    */


    /* Calculation of tpi: */
    subject->scores.tpi = 100.0 * (tp_count / (2.0 * (n - 2.0) / 3.0));

    /* Calculate RG (repetition gap): */
    // subject->scores.rg = calculate_mean(rg_list, i); // / 100.0;                        
    subject->scores.rg = calculate_median(rg_list, i);                        

    /* Calculate count scores: */
    subject->scores.cs1 = calculate_metric_cs(CS1, subject->response, trials);
    subject->scores.cs2 = calculate_metric_cs(CS2, subject->response, trials);
    subject->scores.cst = calculate_metric_cs(CS1, subject->response, trials) + calculate_metric_cs(CS2, subject->response, trials);
}

/*----------------------------------------------------------------------------*/

void rng_print_subject_sequence(FILE *fp, RngSubjectData *subject, int trials)
{
    if (fp != NULL) {
        int i;

        fprintf(fp, "SEQUENCE: ");
        for (i = 0; i < trials; i++) {
            fprintf(fp, "%d ", subject->response[i]);
        }
        fprintf(fp, "\n");
    }
}

void fprint_rng_scores(FILE *fp, RngScores *score)
{
    if (fp != NULL) {
        int k;


	/* NS - include CS1, CS2, CST and other metrics here */
        // fprintf(fp, "%5.3f\t%5.3f\t%5.3f\t%5.3f", score->r, score->rng, score->tpi, score->rg);
	fprintf(fp, "%5.3f\t%5.3f\t%5.3f", score->r, score->rng, score->rg);
	fprintf(fp, "\t%5.3f\t%5.3f\t%5.3f", score->cs1, score->cs2, score->cst); 
        for (k = 0; k < 19; k++) {
            fprintf(fp, "\t%5.3f", score->associates[k]);
        }
        fprintf(fp, "\n");
    }
}

void rng_print_scores(FILE *fp, RngScores *scores)
{
    if (fp != NULL) {
      
      // fprintf(fp, "R\tRNG\tRG\tCS1\tCS2\tCST\tAssociates\n");
      
      fprint_rng_scores(fp, scores);
      // fprintf(fp, "\n");
    }
}

void rng_analyse_subject_responses(FILE *fp, OosVars *gv, int id)
{
    RngSubjectData *subject;

    subject = &(((RngData *)gv->task_data)->trial[id]);

    // rng_print_subject_sequence(fp, subject, gv->trials_per_subject);
    rng_score_subject_data(subject, gv->trials_per_subject);
    rng_print_scores(fp, &(subject->scores));
}


void rng_analyse_group_data(OosVars *gv, FILE *fp, RngScores *zscore_ref_means, RngScores *zscore_ref_sd)
{
    RngData *task_data = (RngData *)gv->task_data;
    RngScores sum, ssq;
    int i, k;

    task_data->n = gv->block;

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

    for (i = 0; i < task_data->n; i++) {
        RngSubjectData *subject = &(task_data->trial[i]);

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
    if (task_data->n > 0) {
        task_data->group_means.r = sum.r / (double) task_data->n;
        task_data->group_means.rng = sum.rng / (double) task_data->n;
        task_data->group_means.tpi = sum.tpi / (double) task_data->n;
        task_data->group_means.rg = sum.rg / (double) task_data->n;
	task_data->group_means.cs1 = sum.cs1 / (double) task_data->n;
	task_data->group_means.cs2 = sum.cs2 / (double) task_data->n;
	task_data->group_means.cst = sum.cst / (double) task_data->n;
        for (k = 0; k < 19; k++) {
            task_data->group_means.associates[k] = sum.associates[k] / (double) task_data->n;
        }
    }
    if (task_data->n > 1) {
        task_data->group_sd.r = sqrt((ssq.r - (sum.r*sum.r/ (double) task_data->n))/((double) task_data->n - 1));
        task_data->group_sd.rng = sqrt((ssq.rng - (sum.rng*sum.rng/ (double) task_data->n))/((double) task_data->n - 1));
        task_data->group_sd.tpi = sqrt((ssq.tpi - (sum.tpi*sum.tpi/ (double) task_data->n))/((double) task_data->n - 1));
        task_data->group_sd.rg = sqrt((ssq.rg - (sum.rg*sum.rg/ (double) task_data->n))/((double) task_data->n - 1));
	task_data->group_sd.cs1 = sqrt((ssq.cs1 - (sum.cs1*sum.cs1/ (double) task_data->n))/((double) task_data->n - 1));
	task_data->group_sd.cs2 = sqrt((ssq.cs2 - (sum.cs2*sum.cs2/ (double) task_data->n))/((double) task_data->n - 1));
	task_data->group_sd.cst = sqrt((ssq.cst - (sum.cst*sum.cst/ (double) task_data->n))/((double) task_data->n - 1));

        for (k = 0; k < 19; k++) {
            task_data->group_sd.associates[k] = sqrt((ssq.associates[k]- (sum.associates[k]*sum.associates[k]/ (double) task_data->n))/((double) task_data->n - 1));
        }
    }

    // TO DO: Also calculate SD for each variable:

   if (fp != NULL) {

     RngScores z_scores, z_score_sd;

	//        fprintf(fp, "---\tR\tRNG\tRG\tCS1\tCS2\tCST\tAssociates\n");
	// print rate first
	// fprintf(fp, "---\trate\tR\tRNG\tRG\tCS1\tCS2\tCST\tAssociates\n");
        fprintf(fp, "means:\t");
	fprintf(fp, "%d\t", task_data->params.generation_period);// print rate 
	fprint_rng_scores(fp, &(task_data->group_means));

        fprintf(fp, "SD:\t");
	fprintf(fp, "%d\t", task_data->params.generation_period);// print rate 
	fprint_rng_scores(fp, &(task_data->group_sd));

        fprintf(fp, "mn(Z):\t");
	fprintf(fp, "%d\t", task_data->params.generation_period);// print rate 
        rng_scores_convert(&(task_data->group_means), zscore_ref_means, zscore_ref_sd, &z_scores);
        fprint_rng_scores(fp, &z_scores);

        fprintf(fp, "SD(Z):\t");
	fprintf(fp, "%d\t", task_data->params.generation_period);// print rate 
        rng_scores_convert(&(task_data->group_sd), zscore_ref_means, zscore_ref_sd, &z_score_sd);
        fprint_rng_scores(fp, &z_score_sd);
        fprintf(fp, "\n");
   }

}



/******************************************************************************/

void rng_scores_convert(RngScores *means, RngScores *reference_means, RngScores *reference_sd, RngScores *z_scores)
{
    int k;

    /* only create z scores if data != 0 */

    z_scores->r = (means->r ? ((means->r - reference_means->r) / reference_sd->r) : 0); // no data
    z_scores->rng = (means->rng ? ((means->rng - reference_means->rng) / reference_sd->rng) : 0);
    // z_scores->tpi = (means->tpi - subject_ctl_means.tpi) / subject_ctl_sd.tpi; // no data
    z_scores->rg = (means->rg ? ((means->rg - reference_means->rg) / reference_sd->rg) : 0);
    z_scores->cs1 = (means->cs1 ? ((means->cs1 - reference_means->cs1) / reference_sd->cs1) : 0);
    z_scores->cs2 = (means->cs2 ? ((means->cs2 - reference_means->cs2) / reference_sd->cs2) : 0);    
    z_scores->cst = (means->cst ? ((means->cst - reference_means->cst) / reference_sd->cst) : 0);

    
    for (k = 0; k < 19; k++) {
      z_scores->associates[k] = (means->associates[k] ? ((means->associates[k] - reference_means->associates[k]) / reference_sd->associates[k]) : 0);
    
    }
    
}

/* function before starting to mess with it */
/*
void rng_scores_convert(RngScores *means, RngScores *z_scores)
{
    int cok;
    
    // z_scores->r = (means->r - subject_ctl_means.r) / subject_ctl_sd.r; // no data
    z_scores->rng = (means->rng - subject_ctl_means.rng) / subject_ctl_sd.rng;
    // z_scores->tpi = (means->tpi - subject_ctl_means.tpi) / subject_ctl_sd.tpi; // no data
    z_scores->rg = (means->rg - subject_ctl_means.rg) / subject_ctl_sd.rg;
    z_scores->cs1 = (means->cs1 - subject_ctl_means.cs1) / subject_ctl_sd.cs1;
    z_scores->cs2 = (means->cs2 - subject_ctl_means.cs2) / subject_ctl_sd.cs2;    
    z_scores->cst = (means->cst - subject_ctl_means.cst) / subject_ctl_sd.cst;

    
    // for (k = 0; k < 10; k++) {
    //    z_scores->associates[k] = (means->associates[k] - subject_ctl_means.associates[k]) / subject_ctl_sd.associates[k];
    
    }
    
}
*/


void rng_sd_convert(RngScores *before, RngScores *reference_sd, RngScores *after)
{
    int k;
    
    after->r   = before->r   / reference_sd->r; // no data
    after->rng = before->rng / reference_sd->rng;
    // after->tpi = before->tpi / subject_ctl_sd.tpi; // no data
    after->rg  = before->rg  / reference_sd->rg;
    after->cs1 = before->cs1 / reference_sd->cs1;
    after->cs2 = before->cs2 / reference_sd->cs2;    
    after->cst = before->cst / reference_sd->cst;
    /*
    for (k = 0; k < 10; k++) {
        after->associates[k] = before->associates[k] / subject_ctl_sd.associates[k];
    }
    */

}

double rng_global_fit_max(RngScores *empirical_data, RngScores *reference_sd, RngScores *model)
{
    double fit = 0.0;
    double error_z_score;

    /* Rick's model fit algorithm
    // comment until R stat fixed for set size of 9 (Jahanshahi) 
    // fit = MAX(fit, fabs((data>-r - model->r) / reference_sd->r));


    fit = MAX(fit, fabs((empirical_data->rng - model->rng) / reference_sd->rng));
    // fit = MAX(fit, fabs((data->tpi - model->tpi) / subject_ctl_sd.tpi));
    fit = MAX(fit, fabs((empirical_data->rg - model->rg) / reference_sd->rg));
    fit = MAX(fit, fabs((empirical_data->cs1 - model->cs1) / reference_sd->cs1));
    fit = MAX(fit, fabs((empirical_data->cs2 - model->cs2) / reference_sd->cs2));    
    fit = MAX(fit, fabs((empirical_data->cst - model->cst) / reference_sd->cst));
    */

    
    if (empirical_data->r != 0) {
      /* don't penalise model fit if no empirical data for a DV */
      error_z_score = ((model->r - empirical_data->r) / reference_sd->r);
      fit += (error_z_score * error_z_score);
    }

    if (empirical_data->rng != 0) {
      error_z_score = ((model->rng - empirical_data->rng) / reference_sd->rng);
      fit += (error_z_score * error_z_score);
    }

    if (empirical_data->rg != 0) {
      error_z_score = ((model->rg - empirical_data->rg) / reference_sd->rg);
      fit += (error_z_score * error_z_score);
    }

    if (empirical_data->cs1 != 0) {
      error_z_score = ((model->cs1 - empirical_data->cs1) / reference_sd->cs1);
      fit += (error_z_score * error_z_score);
    }

    if (empirical_data->cs2 != 0) { 
      error_z_score = ((model->cs2 - empirical_data->cs2) / reference_sd->cs2);
      fit += (error_z_score * error_z_score);
    }


    /* associate -1 */
    if (empirical_data->associates[8] != 0) {
      error_z_score = ((model->associates[8] - empirical_data->associates[8]) / reference_sd->associates[8]);
      fit += (error_z_score * error_z_score);
    }
    /* associate 0 */
    if (empirical_data->associates[9] != 0) {
      error_z_score = ((model->associates[9] - empirical_data->associates[9]) / reference_sd->associates[9]);
      fit += (error_z_score * error_z_score);
    }

    /* associate +1 */
    if (empirical_data->associates[10] != 0) {
      error_z_score = ((model->associates[10] - empirical_data->associates[10]) / reference_sd->associates[10]);
      fit += (error_z_score * error_z_score);
    }



    /* don't need to include cst as it is composite of cs1 and cs2 */

    return(fit);
}

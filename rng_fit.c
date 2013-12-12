/* Use a genetic algorithm to find best fitting parameters */

#include "rng.h"
#include "oos.h"
#include "rng_subject_data.h" 

// #define GENERATION_MAX  1000
// #define POPULATION_SIZE 120

// test params
#define GENERATION_MAX  100
#define POPULATION_SIZE 120 

#define DEFAULT_LOGFILE "FIT_V1_j2006_c3.log"

#define DATA_TO_FIT dataset_jahanshahi_2006.subject_c3_means
#define REFERENCE_SD dataset_towse_1998.subject_ctl_sd // monte-carlo SD values


static RngParameters para_pop[POPULATION_SIZE];
static double para_fit[POPULATION_SIZE];
static int generation = 0;


/// These are good parameter values:
//    RngParameters pars = {30, 80, 1.0, 1.0};

/******************************************************************************/

double clip(double low, double high, double x)
{
    if (x < low) {
        return(low);
    }
    else if (x > high) {
        return(high);
    }
    else {
        return(x);
    }
}

double random_normal(double mean, double sd)
{
    /* This generates a random integer with given mean and standard deviation */

    double r1 = rand() / (double) RAND_MAX;
    double r2 = rand() / (double) RAND_MAX;

    return(mean + sd * sqrt(-2 * log(r1)) * cos(2.0 * M_PI * r2));
}

static void ga_generate_seed_population()
{
    int i;

    for (i = 0; i < POPULATION_SIZE; i++) {
        para_pop[i].temperature = random_uniform(1.0, 100.0);
        para_pop[i].monitoring_efficiency = random_uniform(0.1, 1.0);
        // para_pop[i].wm_decay_rate = random_integer(60, 500);
	para_pop[i].wm_threshold = random_uniform(-1, 1);
        para_pop[i].wm_update_rate = random_uniform(0.1, 1.0);
	para_pop[i].generation_period = random_integer(8, 24);
    }
}

static void ga_generate_next_generation()
{
// Take best 25% of current population
// cross these to get next 25%
// add 25% mutatations from first group
// finish with 25% totally new

    int i;
    int l[3];

    l[0] = POPULATION_SIZE * 0.25;
    l[1] = POPULATION_SIZE * 0.50;
    l[2] = POPULATION_SIZE * 0.75;

    for (i = l[0]; i < l[1]; i++) {
        // 25% from originals crossed
        int m = random_integer(0, l[0]);
        int n = random_integer(0, l[0]);
	int p = random_integer(0, l[0]);

        para_pop[i].wm_threshold = para_pop[m].wm_threshold;
        para_pop[i].temperature = para_pop[m].temperature;
        para_pop[i].monitoring_efficiency = para_pop[n].monitoring_efficiency;
        para_pop[i].wm_update_rate = para_pop[n].wm_update_rate;
	para_pop[i].generation_period = para_pop[p].generation_period;
    }

    for (i = l[1]; i < l[2]; i++) {
        // 25% mutatations from original good cases
        para_pop[i].wm_threshold = clip(-1, 1, random_normal(para_pop[i-l[1]].wm_threshold, 0.1));
        para_pop[i].temperature = clip(0, 100, random_normal(para_pop[i-l[1]].temperature, 10.0));
        para_pop[i].monitoring_efficiency = clip(0.1, 1.0, random_normal(para_pop[i-l[1]].monitoring_efficiency, 0.2));
        para_pop[i].wm_update_rate = clip(0.1, 1.0, random_normal(para_pop[i-l[1]].wm_update_rate, 0.2));
	para_pop[i].generation_period = clip(4.0, 24.0, random_normal(para_pop[i-l[1]].generation_period, 4));
    }

    for (i = l[2]; i < POPULATION_SIZE; i++) {
        para_pop[i].wm_threshold = random_uniform(-1, 1);
        para_pop[i].temperature = random_uniform(0.01, 100.0);
        para_pop[i].monitoring_efficiency = random_uniform(0.1, 1.0);
        para_pop[i].wm_update_rate = random_uniform(0.1, 1.0);
	para_pop[i].generation_period = random_integer(4, 24);
    }
}

/******************************************************************************/

static void ga_generate_population(int generation)
{
    if (generation == 0) {
        ga_generate_seed_population();
    }
    else {
        ga_generate_next_generation();
    }
}

/******************************************************************************/

static void ga_sort_by_fit()
{
    /* A quick to code but dirty ripple sort procedure... */

    int i, j;
    double f;
    RngParameters p;

    for (i = 0; i < POPULATION_SIZE; i++) {
        for (j = i+1; j < POPULATION_SIZE; j++) {
            if (para_fit[i] > para_fit[j]) {
                /* Swap i and j: */
            
                f = para_fit[i];
                para_fit[i] = para_fit[j];
                para_fit[j] = f;

		/*
                p.wm_decay_rate = para_pop[i].wm_decay_rate;
                para_pop[i].wm_decay_rate = para_pop[j].wm_decay_rate;
                para_pop[j].wm_decay_rate = p.wm_decay_rate;
		*/

		p.wm_threshold = para_pop[i].wm_threshold;
                para_pop[i].wm_threshold = para_pop[j].wm_threshold;
                para_pop[j].wm_threshold = p.wm_threshold;

                p.temperature = para_pop[i].temperature;
                para_pop[i].temperature = para_pop[j].temperature;
                para_pop[j].temperature = p.temperature;

                p.monitoring_efficiency = para_pop[i].monitoring_efficiency;
                para_pop[i].monitoring_efficiency = para_pop[j].monitoring_efficiency;
                para_pop[j].monitoring_efficiency = p.monitoring_efficiency;

                p.wm_update_rate = para_pop[i].wm_update_rate;
                para_pop[i].wm_update_rate = para_pop[j].wm_update_rate;
                para_pop[j].wm_update_rate = p.wm_update_rate;

		p.generation_period = para_pop[i].generation_period;
                para_pop[i].generation_period = para_pop[j].generation_period;
                para_pop[j].generation_period = p.generation_period;

            }
        }
    }
}

static void ga_print_statistics(FILE *fp, int generation)
{
    int i;

    fprintf(fp, "Generation %3d\t[Intvl;\tThrsh;\tTemp;\tMon;\tUpdt]\n", generation);
    for (i = 0; i < POPULATION_SIZE; i++) {
      fprintf(fp, "%3d: %f\t[%2d,\t%5.3f,\t%5.3f,\t%5.3f,\t%6.3f]\n", i, para_fit[i], para_pop[i].generation_period, para_pop[i].wm_threshold, para_pop[i].temperature, para_pop[i].monitoring_efficiency, para_pop[i].wm_update_rate);
    }
}

/******************************************************************************/

static double rng_model_fit(OosVars *gv, RngParameters *pars)
{
    rng_create(gv, pars);
    rng_initialise_model(gv);
    rng_run(gv);
    // rng_analyse_group_data((RngData *)gv->task_data);
    rng_analyse_group_data(gv, NULL, &reference_montecarlo_means, &reference_montecarlo_sd); 


    // return(rng_data_calculate_fit((RngData *)gv->task_data));
      // is rng_data_calculate_fit same as rng_global_fit_max?


    // RngData *group_means = (RngData *)gv->task_data->group_means;
    return (rng_global_fit_max(&(DATA_TO_FIT), &(REFERENCE_SD), &(((RngData *)gv->task_data)->group_means)));
    
}

/******************************************************************************/

int main(int argc, char **argv)
{
    FILE *fp;
    OosVars *gv;
    int i;

    if ((gv = oos_globals_create()) == NULL) {
        fprintf(stdout, "ABORTING: Cannot allocate global variable space\n");
    }
    else {
        gv->random_generator = gaussian_random_generator_create();
        for (generation = 0; generation < GENERATION_MAX; generation++) {
            ga_generate_population(generation);
            for (i = 0; i < POPULATION_SIZE; i++) {
                para_fit[i] = rng_model_fit(gv, &para_pop[i]);
            }
            ga_sort_by_fit();
            fp = fopen(DEFAULT_LOGFILE, "a");
            ga_print_statistics(fp, generation);
            fclose(fp);
	}

        rng_globals_destroy((RngData *)gv->task_data);
        oos_globals_destroy(gv);
    }
    exit(1);
}

/******************************************************************************/

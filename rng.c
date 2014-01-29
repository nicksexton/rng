#include "rng.h"
#include "oos.h"


/* comment if volatile */
 #include "rng_subject_data.h"

/******************************************************************************/

int main(int argc, char **argv)
{

    OosVars *gv;
    int c;
 
    opterr = 0;


    /* task set temp, mon efficiency, wm update rate, WM decay rate, generation period */
    RngParameters pars = {23.0, 0.26, 1.0, 0.0, 8, {0.60, 0.55, 0.40, -0.25, 0.87}};
    
    
   
    while ((c = getopt (argc, argv, "t:m:u:d:g:")) != -1) {
      switch (c) {
      case 't' : 
	// arg_t = optarg;
	// pars.temperature = atof (arg_t);
	pars.temperature = atof (optarg);
	break;
      case 'm' :
	pars.monitoring_efficiency = atof (optarg);
	break;
      case 'u' :
	pars.wm_update_rate = atof (optarg);
	break;
      case 'd' :
	pars.wm_threshold = atof (optarg);
	break;
      case 'g' :
	pars.generation_period = atoi (optarg);
	break;
      case '?' :
	if (optopt == 'c')
	  fprintf (stderr, "option -%c requires an argument. \n", optopt);
	else if (isprint (optopt))
	  fprintf (stderr, "unknown option -%c.\n", optopt);
	else 
	  fprintf (stderr, "unknown option character '\\x%x'.\n", optopt);
	return (1);
      default: 
	abort ();
      }
    }
    

    if ((gv = oos_globals_create()) == NULL) {
        fprintf(stdout, "ABORTING: Cannot allocate global variable space\n");
    }
    else {
        gv->random_generator = gaussian_random_generator_create();
        rng_create(gv, &pars);
        rng_initialise_model(gv);
        rng_run(gv);
 	// Report data here
 	/*
 	printf ("ts_temp = %4.2f, mon_eff = %4.2f, wm_update_rate = %4.2f, wm_decay_rate = %d, gen_period = %d\n", 
 		pars.temperature, pars.monitoring_efficiency, pars.wm_update_rate, pars.wm_decay_rate, pars.generation_period);
 	*/
          rng_analyse_group_data(gv, stdout, &reference_montecarlo_means, &reference_montecarlo_sd);
  
 	//now clean up and finish

        rng_globals_destroy((RngData *)gv->task_data);
        oos_globals_destroy(gv);
    }
    exit(1);
}

/******************************************************************************/
 

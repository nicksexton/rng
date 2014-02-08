/*******************************************************************************

Hypothesis / assumption:

* DVs that pattern together in dual task experiment do so as a result of
sharing a common process (which is tapped by the secondary task).

Implications:

* RNG, TPI and all second order measures are due to process A (greater
emphasis on existing biases in schema selection)

* R and RG are due to process B (failure to update W)Mlinu

So, the basic model should capture RNG and TPI through the schema selection
bias, not through a monitoring subprocess. That is, schema selection should
impose the clockwise / anti-clockwise idea.

Note that these assumptions also have implications for WCST and ToL, given the
dual-task experiment.

*******************************************************************************/

#include "rng.h"
// #include "oos.h" // nick 
// #include "oos.c" 
#include "lib_string.h"
#include "lib_maths.c"


#define BOX_TASK_SETTING        11
#define BOX_MONITORING          12
#define BOX_APPLY_SET           13
#define BOX_GENERATE_RESPONSE   14
#define BOX_PROPOSE_RESPONSE    15

#define BOX_CURRENT_SET         21
#define BOX_WORKING_MEMORY      22
#define BOX_RESPONSE_BUFFER     23
#define BOX_RESPONSE_NODES      24

// #define ECHO // echo responses to screen
#undef ECHO
#define SUPERVISORY_ON    // comment to toggle messages sent from supervisory system
#define MATCH_THRESHOLD 0.80



// #define SET_SWITCH_LATENCY 4 // number of cycles before MONITORING tries a new set
#define SET_SWITCH_LATENCY 6 // tried on 02/02/14 to get randomness check a bit better


#define ACT_SELF 0.68		
#define ACT_NEXT -0.025
#define ACT_PREV -0.026
#define ACT_INHI -0.048
#define ACT_NEXT_WR -0.026 // activation from next node when wrapping round
#define ACT_PREV_WR -0.031 // activation from prev node when wrapping round
#define PERSISTENCE 0.905
#define STARTING_RESPONSE_NODE_ACTIVATION_MAX 0.3

	// #define SPREADING_ACTIVATION_ITERATIONS_PER_STEP 8 // debug
#define SPREADING_ACTIVATION_ITERATIONS_PER_STEP 14 // debug

#define WM_RETRIEVAL_NOISE 0.0
#define WM_RETRIEVAL_SPREAD 0.15
#define WM_RETRIEVAL_LATENCY_SCALE 4




/*  Schema selection strengths */
//  #define SCHEMA_BIAS
#define SS_RP 0.01
#define SS_FL 0.11      // flat selection strengths

// #define DEBUG
 #undef DEBUG



#ifdef DEBUG
static int schema_counts[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif

static double total_monitoring_messages = 0;
static double total_taskset_messages = 0;
static double total_applyset_messages = 0;


/* OLD schema selection strength */
// theoretical idea is that effortful schemas are higher weighted eg. +/-2, +/-3, +/-4 etc
static double strength[10] = {0.1, 0.15, 0.18, 0.05, 0.05, 0.05, 0.18, .15, .10, 0.08};

/* NEW schema selection strengths */


#ifndef SCHEMA_BIAS
/* -------------- FLAT schema selection strengths ------------- */
/* _0[10] schemas are for 0 to +9; _1[10] schemas for -1 to +8 etc. */
static double schema_strengths[10][10] = {
  { SS_RP, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL},  // 0, schemas  0 - +9
  { SS_FL, SS_RP, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL},  // 1, schemas -1 - +8 
  { SS_FL, SS_FL, SS_RP, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL},
  { SS_FL, SS_FL, SS_FL, SS_RP, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL},
  { SS_FL, SS_FL, SS_FL, SS_FL, SS_RP, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL},
  { SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_RP, SS_FL, SS_FL, SS_FL, SS_FL},
  { SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_RP, SS_FL, SS_FL, SS_FL},
  { SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_RP, SS_FL, SS_FL},
  { SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_RP, SS_FL}, // 8, schemas -8 - +1
  { SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_FL, SS_RP}, // 9, schemas -9 - 0
};
#endif


#ifdef SCHEMA_BIAS
/* ----------------BIAS Schema selection strengths ---------- */
static double schema_strengths[10][10] = {
  { 0.001,  0.06,  0.07,  0.08,  0.12,  0.12,  0.12,  0.13,  0.14,  0.15 },  // 0, schemas  0 - +9
  { 0.06,  0.001,  0.07,  0.08,  0.08,  0.12,  0.12,  0.13,  0.14,  0.14 },  // 1, schemas -1 - +8 
  { 0.07,  0.07,  0.001,  0.08,  0.08,  0.12,  0.12,  0.13,  0.13,  0.13 },
  { 0.08,  0.08,  0.08,  0.001,  0.08,  0.12,  0.12,  0.12,  0.12,  0.12 },
  { 0.10,  0.10,  0.10,  0.10,  0.001,  0.10,  0.10,  0.10,  0.10,  0.10 },
  { 0.10,  0.10,  0.10,  0.10,  0.10,  0.001,  0.10,  0.10,  0.10,  0.10 },
  { 0.12,  0.12,  0.12,  0.12,  0.12,  0.08,  0.001,  0.08,  0.08,  0.08 },
  { 0.13,  0.13,  0.13,  0.12,  0.12,  0.08,  0.08,  0.001,  0.07,  0.07 },
  { 0.14,  0.14,  0.13,  0.12,  0.12,  0.08,  0.08,  0.07,  0.001,  0.06 }, // 8, schemas -8 - +1
  { 0.15,  0.14,  0.13,  0.12,  0.12,  0.08,  0.08,  0.07,  0.06,  0.001 }, // 9, schemas -9 - 0
};
#endif





/* Response nodes spreading activation weights matrix */

/* 
 NB flip matrix along the diagonal - is from the j's perspective
 ie node[3][4] represents NEXT node from i's perspective but PREV node from j's perspective
  */

static double response_nodes_weights[10][10] = { 
  { ACT_SELF, ACT_PREV, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_NEXT_WR},
  { ACT_NEXT, ACT_SELF, ACT_PREV, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI},
  { ACT_INHI, ACT_NEXT, ACT_SELF, ACT_PREV, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI},
  { ACT_INHI, ACT_INHI, ACT_NEXT, ACT_SELF, ACT_PREV, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI},
  { ACT_INHI, ACT_INHI, ACT_INHI, ACT_NEXT, ACT_SELF, ACT_PREV, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI},
  { ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_NEXT, ACT_SELF, ACT_PREV, ACT_INHI, ACT_INHI, ACT_INHI},
  { ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_NEXT, ACT_SELF, ACT_PREV, ACT_INHI, ACT_INHI},
  { ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_NEXT, ACT_SELF, ACT_PREV, ACT_INHI},
  { ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_NEXT, ACT_SELF, ACT_PREV},
  { ACT_PREV_WR, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_NEXT, ACT_SELF}, 
};
 
						 


/*****************************************************************************/

#ifdef DEBUG
static void fprint_schema_counts(FILE *fp, OosVars *gv)
{
    if (fp != NULL) {
      	int sum = 0, i;

	for (i = 0; i < 10; i++) {
	    sum += schema_counts[i];
	}
	fprintf(fp, "Empirical distribution with %d samples with %d subjects:\n", sum, gv->block);
	if (sum > 0) {
	    for (i = 0; i < 10; i++) {
		fprintf(fp, "%2d: %6.4f\n", i, schema_counts[i] / (double) sum);
	    }
	}
	else {
	    fprintf(fp, "NONE\n");
	}
	fprintf(fp, "\n");
    }
}
#endif


static void fprint_message_counts(FILE *fp, OosVars *gv)
{
  if (fp != NULL) {

    fprintf (fp, "cycles: %d, mon msgs: %2.0f (%2.3f/100c), task set msgs: %2.0f (%2.3f/100c) apply set msgs: %2.0f (%2.3f/100c) \n", 
	     gv->cycle, total_monitoring_messages, total_monitoring_messages * 100 / gv->cycle, 
	     total_taskset_messages, total_taskset_messages * 100 / gv->cycle,
	     total_applyset_messages, total_applyset_messages * 100 / gv->cycle);

    total_monitoring_messages = 0;
    total_taskset_messages = 0;
    total_applyset_messages = 0;
  }
}



void rng_print_schema_selection_probabilities(FILE *fp, double temperature)
{
    double weighted_sum;
    int i;

    weighted_sum = 0;

     /* NEW (BROKEN) */
    /*

    for (i = 0; i < 10; i++) {
      weighted_sum += exp((-schema_strengths[0][i]) / temperature);
    }
    fprintf(fp, "STRENGTH AT %5.3f\n", temperature);
    for (i = 0; i < 10; i++) { 
	 fprintf(fp, "%2d: baseline strength of %6.4f maps to probability of %6.4f\n", i, schema_strengths[0][i], exp( (-schema_strengths[0][i]) / temperature) / weighted_sum);
	 }
      */

      /* ------------ OLD ---------------- */

    for (i = 0; i < 10; i++) {
      weighted_sum += exp(temperature*schema_strengths[0][i]);
    }
    
    fprintf(fp, "STRENGTH AT %5.3f\n", temperature);
    for (i = 0; i < 10; i++) {
      fprintf(fp, "%2d: baseline strength of %6.4f maps to probability of %6.4f\n", i, schema_strengths[0][i], exp(temperature*schema_strengths[0][i]) / weighted_sum);
      
    }

    /* -------------------------- */

    fprintf(fp, "\n");

}

/******************************************************************************/

double get_total_wm_activation (OosVars *gv)
{
  TimestampedClauseList *contents = NULL;
  double total_activation = 0;

  contents = oos_buffer_get_contents(gv, BOX_WORKING_MEMORY);

  while (!(contents == NULL)) {

    if (contents->activation < -5.0) { total_activation -= 3.0; }
    else if (contents->activation > 5.0) { total_activation += 3.0; }
    else { total_activation += contents->activation; }

    contents = contents->tail;
  }

  return total_activation;
}

void set_wm_item_last_retrieved(OosVars *gv, long item, Boolean last_retrieved)
{
  TimestampedClauseList *contents = NULL;
  long wm_item;

  contents = oos_buffer_get_contents(gv, BOX_WORKING_MEMORY);

  while (!(contents == NULL)) {

    pl_is_integer(pl_arg_get(contents->head, 1), &wm_item);
    if (item == wm_item) {
      contents->last_retrieval_success = last_retrieved;
      contents->last_retrieval_timestamp = gv->cycle;
      break;
    }
    contents = contents->tail;
  }
}

double wm_retrieval_latency(OosVars *gv, long item)
{
  TimestampedClauseList *contents = NULL;
  long wm_item;
  double retrieval_latency, activation, mean_activation;

  contents = oos_buffer_get_contents(gv, BOX_WORKING_MEMORY);

  while (!(contents == NULL)) {

    pl_is_integer(pl_arg_get(contents->head, 1), &wm_item);
    if (item == wm_item) {
      activation = contents->activation;

      mean_activation = get_total_wm_activation(gv) / 10;

      /* CORRECT (?) code */
      retrieval_latency = (WM_RETRIEVAL_LATENCY_SCALE * exp(-1 * (activation - mean_activation)));

      /* OLD (reverted) code (WRONG??) */
      // retrieval_latency = (WM_RETRIEVAL_LATENCY_SCALE * exp(-1 * (activation - mean_activation)));


      return (ceil (retrieval_latency)); // round up
    }
    contents = contents->tail;
  }

  return (-1);
}


Boolean item_retrieved_from_wm(OosVars *gv, double item_activation)
{
  /* implements schochastic ACT-R memory retrieval */
  /* see Anderson 2007 p.111 WM p.142 */

  RngData *task_data = (RngData *)(gv->task_data);

  double noise = 1;
  double p, probability;

  /* debug vars */
  double debug_activation = item_activation;
  double mean_activation = get_total_wm_activation(gv) / 10;
  
  noise = gsl_ran_logistic(gv->random_generator, WM_RETRIEVAL_NOISE);

  /* ACT-R equation */
  
  double exponent = ( -1 * (item_activation - mean_activation - task_data->params.wm_threshold + noise) 
		      / WM_RETRIEVAL_SPREAD);
  


  /* implementation - WM retrieval threshold is relative to total activation */
  // probability = 1 / (1 + exp ( -1 * (item_activation + noise - threshold) / WM_RETRIEVAL_SPREAD));
  probability = 1 / (1 + exp (exponent));

  p = random_uniform(0.0, 1.0);
  // printf ("retrieving from wm, p = %f: %f\n", probability, p);

  return (probability > p);
}


static long get_WM_latest(OosVars *gv)
{
  long wm_item;
  long latest_item;
  TimestampedClauseList *contents = NULL;
  long latest_timestamp = 0;
  contents = oos_buffer_get_contents(gv, BOX_WORKING_MEMORY);

  while (!(contents == NULL)) {

    pl_is_integer(pl_arg_get(contents->head, 1), &wm_item);      

    if (contents->timestamp > latest_timestamp) {

      if (item_retrieved_from_wm(gv, contents->activation)) {
	set_wm_item_last_retrieved (gv, wm_item, TRUE);      
	latest_timestamp = contents->timestamp;
	latest_item = wm_item;
      }

      else {
	set_wm_item_last_retrieved (gv, wm_item, FALSE);
      }  
    }
  
    contents = contents->tail;
  }

  if (latest_timestamp > 0) { 
      
      return (latest_item);
    }

  else return (-1);
}


static Boolean match_item_in_wm (OosVars *gv, long item_to_match)
{
  TimestampedClauseList *contents = NULL;
  long wm_item;
  double item_activation;

  contents = oos_buffer_get_contents(gv, BOX_WORKING_MEMORY);

  while (!(contents == NULL)) {

    pl_is_integer(pl_arg_get(contents->head, 1), &wm_item);
    if (item_to_match == wm_item) {
      item_activation = contents->activation;
      break;
    }
    contents = contents->tail;
  }
  
  if (item_retrieved_from_wm(gv, item_activation)) {
    set_wm_item_last_retrieved (gv, item_to_match, TRUE);      
    return (1);
  }

  else {
    set_wm_item_last_retrieved (gv, item_to_match, FALSE);      
    return 0;
  }
}




static ClauseType *select_weighted_schema(OosVars *gv, long latest_response)
{
    RngData *task_data = (RngData *)(gv->task_data);
    double limit;
    double weighted_sum;
    static Boolean clockwise = TRUE;
    int i;
    // long latest_response;




    if (clockwise) {
	weighted_sum = 0;
	for (i = 0; i < 10; i++) {
	    weighted_sum += schema_strengths[latest_response][i];
	}

	limit = weighted_sum * random_uniform(0.0, 1.0);
	i = -1;
	do {
	    i++;
	    limit -= schema_strengths[latest_response][i];
	} while ((limit > 0) && (i < 10));


    }





#ifdef DEBUG
    // If DEBUG is defined then kee track of how many times each schema is
    // selected, so we can compare this to the expected distribution based on
    // the calculated probabilities:
    // disabled 26/06/13
    //    schema_counts[i]++;
#endif

    /* schema in position i is relative to previously generated item */
    switch (i - latest_response) {
    case -9: { return(pl_clause_make_from_string("minus_nine.")); break; }
    case -8: { return(pl_clause_make_from_string("minus_eight.")); break; }
    case -7: { return(pl_clause_make_from_string("minus_seven.")); break; }
    case -6: { return(pl_clause_make_from_string("minus_six.")); break; }
    case -5: { return(pl_clause_make_from_string("minus_five.")); break; }
    case -4: { return(pl_clause_make_from_string("minus_four.")); break; }
    case -3: { return(pl_clause_make_from_string("minus_three.")); break; }
    case -2: { return(pl_clause_make_from_string("minus_two.")); break; }
    case -1: { return(pl_clause_make_from_string("minus_one.")); break; }
    case 0: { return(pl_clause_make_from_string("repeat.")); break; }

    case 1: { return(pl_clause_make_from_string("plus_one.")); break; }
    case 2: { return(pl_clause_make_from_string("plus_two.")); break; }
    case 3: { return(pl_clause_make_from_string("plus_three.")); break; }
    case 4: { return(pl_clause_make_from_string("plus_four.")); break; }
    case 5: { return(pl_clause_make_from_string("plus_five.")); break; }
    case 6: { return(pl_clause_make_from_string("plus_six.")); break; }
    case 7: { return(pl_clause_make_from_string("plus_seven.")); break; }
    case 8: { return(pl_clause_make_from_string("plus_eight.")); break; }
    case 9: { return(pl_clause_make_from_string("plus_nine.")); break; }
    default: { return(pl_clause_make_from_string("error.")); break; }
    }
}





static void task_setting_output(OosVars *gv)
{
  ClauseType *current_set, *schema;
  // ClauseType *response;
  // response = pl_clause_make_from_string("response(_,_).");
    current_set = pl_clause_make_from_string("_.");

    long latest_response;

    // if (oos_match(gv, BOX_WORKING_MEMORY, response) && !oos_match(gv, BOX_CURRENT_SET, current_set)) {

    /* If there is a previous response in working memory, but no current set */
    /* (schema), then select a new schema at random subject to individual weights */
    latest_response = get_WM_latest (gv);

    /* handle case where get_wm_latest fails to return any item */
    if ((latest_response >= 0) && 
	(!oos_match(gv, BOX_CURRENT_SET, current_set))) {
      
      // printf ("task setting: item in WM\n");
	schema = pl_clause_make_from_string("schema(_).");
	pl_arg_set(schema, 1, select_weighted_schema(gv, latest_response));


            #ifdef SUPERVISORY_ON
	oos_message_create(gv, MT_ADD, BOX_TASK_SETTING, BOX_CURRENT_SET, schema);
	total_taskset_messages ++;
            #endif
    }

    // else printf ("task setting: nothing in wm\n");

    pl_clause_free(current_set);
    // pl_clause_free(response);
}

/*----------------------------------------------------------------------------*/

static long get_response_buffer_timestamp(OosVars *gv)
{
  long response_timestamp = -1;

  TimestampedClauseList *contents;
  contents = oos_buffer_get_contents(gv, BOX_RESPONSE_BUFFER);


  /* if (functor_comp(response, "response", 2)) {
      // response_value = pl_functor(pl_arg_get(response, 2));
      response_value = pl_arg_get(response, 1);
  */

  pl_is_integer(pl_arg_get(contents->head, 2), &response_timestamp); 

	    
  return (response_timestamp);
}


static Boolean check_random(OosVars *gv, long r)
{

  long response_buffer_timestamp = get_response_buffer_timestamp(gv);

    /* Return TRUE if this item appears to be random */

    /* If it matches WM, then it isn't random: */

  /*
  if (match_item_in_wm(gv, r) && 
      ((gv->cycle - response_buffer_timestamp) >= r_latency) ) {
      
    printf ("monitoring: matched WM after %4.2f cycles\n", r_latency);
      
       return(FALSE);

    }
    else {
	Boolean result = TRUE;
  */
	// pl_clause_free(template);

// #if FALSE

	TimestampedClauseList *contents, *buffer;
	long temp_wm_value;

	long previous[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	double latency[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	long gaps[10] = {-99, -99, -99, -99, -99, -99, -99, -99, -99, -99 };

	long latest_timestamp, find_next_latest_timestamp = 0;

	latest_timestamp = gv->cycle;

	buffer = NULL;

	int i, j = 0;
	for (i = 0; i < 10; i++) { // outer loop incrementally fills arrays

	  contents = oos_buffer_get_contents(gv, BOX_WORKING_MEMORY);
	  find_next_latest_timestamp = 0;
	  while (!(contents == NULL)) { // inner loop looks for highest timestamp
	    
	    if (contents->timestamp > find_next_latest_timestamp && contents->timestamp < latest_timestamp) {
	      buffer = contents;
	      find_next_latest_timestamp = buffer->timestamp;
	    }
	    contents = contents->tail;
	  }



	  // buffer now contains next latest WM item not already processed
	  if (buffer != NULL) {
	    pl_is_integer(pl_arg_get(buffer->head, 1), &temp_wm_value); 
	    if (item_retrieved_from_wm(gv, buffer->activation)) {
	      
	      previous[j] = temp_wm_value; 
	      latency[j] = wm_retrieval_latency(gv, previous[j]);
	      set_wm_item_last_retrieved (gv, temp_wm_value, TRUE);
	      latest_timestamp = buffer->timestamp;
	      
	      
	      if (j == 0) {
		gaps[0] = r - previous[0];
	      }
	      if (j > 0) {
		gaps[j] = previous[j-1] - previous[j];
	      }
	      j ++;

	    }
	    else {
	      set_wm_item_last_retrieved (gv, temp_wm_value, FALSE);
	    }
	    buffer = NULL;
	  }
	

	}
	
	printf ("working memory contents: ");
	for (i = 0; i < 10; i++) {
	  if (previous[i] == -1) {
	    break;
	  }
	  printf ("%ld(%2.1f), ", previous[i], latency[i]);
	  
	}
	printf ("\n");
	


	for (i=0; i < 10; i++) { 
	  if (previous[i] == -1) {
	    break;
	  } 

	  /* ----------- CHECK if item is contained in WM -------------- */
	  if ((gv->cycle - response_buffer_timestamp) >= latency[i]) {
	    if ((previous[i] > 0) && (r == previous[i])) {
	      // printf ("monitoring: item %ld matched WM position %d, after %4.2f cycles\n", r, i, latency[i]); // debug
	      return (FALSE);
	    }
	  }

	      /* -------------- CHECK if response is step of 1  --------------- */
	  /*
	  if (gv->cycle - response_buffer_timestamp >= latency[0]) {
	    if (gaps[0] == 1) {
	      // printf ("monitoring: g1 == 1, after %4.2f cycles\n", p1_latency); // debug
	      return (FALSE);
	    }
	    
	    if (gaps[0] == -1) {
	      // printf ("monitoring: g1 == -1, after %4.2f cycles\n", p1_latency); // debug
	      return (FALSE);
	    }
	  }

	  */


                /* ----------- CHECK if using associate already contained in WM -------------- */
	  if ((gv->cycle - response_buffer_timestamp) >= latency[i]) {
	    if ((i > 0) && (gaps[0] > -99) && (gaps[0] == gaps[i])) {
	      // printf ("monitoring: gap %ld == gap between %ld and %ld, after %4.2f cycles\n", gaps[0], (i > 0 ? previous[i-1] : r), previous[i], latency[i]); // debug
	      return (FALSE);
	    }
	  }


		/* ------------ END MONITORING RULES ----------------- */
	    
	}

	return(TRUE);
	// }
}

static Boolean check_whether_to_switch (OosVars *gv)
{
  ClauseType *template;
  Boolean whether_to_switch = FALSE;
  long response_value;
  TimestampedClauseList *contents = NULL;
  long latest_timestamp = 0;

   /* only fires if there is something in WM to use as a timestamp */
  // wm_latest_item = pl_clause_make_from_string("response(_,_).");
  // if (oos_match(gv, BOX_WORKING_MEMORY, wm_latest_item)) {

  /* get WM latest - possibly encapsulate this in function */

  
  contents = oos_buffer_get_contents(gv, BOX_WORKING_MEMORY);
  while (!(contents == NULL)) {

    if (contents->timestamp > latest_timestamp) {

      pl_is_integer(pl_arg_get(contents->head, 1), &response_value);

      if (item_retrieved_from_wm(gv, contents->activation)) {
	latest_timestamp = contents->timestamp;
	set_wm_item_last_retrieved (gv, response_value, TRUE);      
      }

      else {
	set_wm_item_last_retrieved (gv, response_value, FALSE);
      }          
    }
  
    contents = contents->tail;
  }

  if ((latest_timestamp > 0) && 
      ((gv->cycle - latest_timestamp) % SET_SWITCH_LATENCY == (SET_SWITCH_LATENCY - 1))) {

      /* if nothing in response buffer */
      template = pl_clause_make_from_string("response(_,_).");
      if (!oos_match(gv, BOX_RESPONSE_BUFFER, template)) {
	whether_to_switch = TRUE;
      }
      pl_clause_free(template);
  }
  
	
	
  // pl_clause_free (wm_latest_item);
  return (whether_to_switch);

}

static void monitoring_output(OosVars *gv)
{
    RngData *task_data = (RngData *)(gv->task_data);


 
    /* ------- Monitoring for nothing happening in response buffer ----------- */
    if (check_whether_to_switch(gv)) {
      // printf ("monitoring: cycle %d - nothing happening, switching set\n", gv->cycle);
#ifdef SUPERVISORY_ON
      oos_message_create(gv, MT_CLEAR, BOX_MONITORING, BOX_CURRENT_SET, NULL);
      total_monitoring_messages ++;
#endif       
    }


    /* ----------------- Monitoring for not sufficiently random -------------- */

    if (task_data->params.monitoring_efficiency > random_uniform(0.0, 1.0)) {
        ClauseType *proposed = NULL, *putative_response = NULL;
	long r;
	

	proposed = pl_clause_make_from_string("response(_,_).");
	if (oos_match_above_threshold(gv, BOX_RESPONSE_BUFFER, proposed, MATCH_THRESHOLD)) {
	    if (pl_is_integer(pl_arg_get(proposed, 1), &r) && !check_random(gv, r)) {
		/* The thing we need to inhibit is of the form "response(_)", */
		/* so adjust the arity of the thing we matched which had the  */
		/* form "response(_,_)" 				      */

	      
#ifdef SUPERVISORY_ON
	      
		pl_arity_adjust(proposed, 1);
		oos_message_create(gv, MT_CLEAR, BOX_MONITORING, BOX_CURRENT_SET, NULL);
		// printf ("monitoring: item in RB not random, clearing current set\n");
		oos_message_create(gv, MT_INHIBIT, BOX_MONITORING, BOX_RESPONSE_NODES, proposed);
	      
		// NS either inhibit (activation based) or simply clear item from BOX_RESPONSE_NODES
		/* inhibition in response buffer
		   first get the putative response, then send inhibit message to it */
	  
	      
	        putative_response = pl_clause_make_from_string("response(_,_).");
		oos_match(gv, BOX_RESPONSE_BUFFER, putative_response);
		oos_message_create(gv, MT_INHIBIT, BOX_MONITORING, BOX_RESPONSE_BUFFER, putative_response); 
	        total_monitoring_messages ++;
#endif


		// Tell BOX_APPLY_SET to fire?
	    }
	    else {
		pl_clause_free(proposed);
	    }
	}
	else {
	    pl_clause_free(proposed);
	}
    }
}


/*----------------------------------------------------------------------------*/

static int apply_schema(ClauseType *schema, long last)
{
  /*
    long last;

    if (!functor_comp(seed, "response", 2)) {
	return(-1);
    }
    else if (!pl_is_integer(pl_arg_get(seed, 1), &last)) {
	return(-1);
    }

  */

    if (functor_comp(schema, "schema", 1)) {
	char *s = pl_functor(pl_arg_get(schema, 1));

	if (strcmp(s, "minus_nine") == 0) { return(last - 9); }
	else if (strcmp(s, "minus_eight") == 0) { return(last - 8); }
	else if (strcmp(s, "minus_seven") == 0) { return(last - 7); }
	else if (strcmp(s, "minus_six") == 0) { return(last - 6); }
	else if (strcmp(s, "minus_five") == 0) { return(last - 5); }
	else if (strcmp(s, "minus_four") == 0) { return(last - 4); }
	else if (strcmp(s, "minus_three") == 0) { return(last - 3);}
	else if (strcmp(s, "minus_two") == 0) { return(last - 2);}
	else if (strcmp(s, "minus_one") == 0) { return(last - 1);}
	else if (strcmp(s, "repeat") == 0) { return(last); }
	else if (strcmp(s, "plus_one") == 0) { return(last + 1); }
	else if (strcmp(s, "plus_two") == 0) { return(last + 2);}
	else if (strcmp(s, "plus_three") == 0) { return(last + 3); }
	else if (strcmp(s, "plus_four") == 0) {return(last + 4);}
	else if (strcmp(s, "plus_five") == 0) {return(last + 5); }
	else if (strcmp(s, "plus_six") == 0) {return(last + 6); }
	else if (strcmp(s, "plus_seven") == 0) {return(last + 7); }
	else if (strcmp(s, "plus_eight") == 0) {return(last + 8); }
	else if (strcmp(s, "plus_nine") == 0) {return(last + 9); }
    }
    return(-1);
}




static void apply_set_output(OosVars *gv)
{
    // ClauseType *seed;
    ClauseType *current_set, *previous, *content, *template;
    long latest_WM_item;

    template = pl_clause_make_from_string("response(_).");
    // seed = pl_clause_make_from_string("response(_,_).");
    previous = pl_clause_make_from_string("_.");
    current_set = pl_clause_make_from_string("schema(_).");


    /* If there is no response already lined up for production, and none of   */
    /* the possible responses are above threshold, then ...		      */

    // NS - this also needs to fire after MONITORING has cleared response buffer
    // current code would do this with no modifications if BOX_RESPONSE_BUFFER were cleared

#ifdef SUPERVISORY_ON


    // if (!oos_match_above_threshold(gv, BOX_RESPONSE_BUFFER, previous, MATCH_THRESHOLD) && !oos_match_above_threshold(gv, BOX_RESPONSE_NODES, template, MATCH_THRESHOLD)) {

    // what happens if we relax constraint that apply_set only fires when there is nothing in response buffer...?
    if (!oos_match_above_threshold(gv, BOX_RESPONSE_NODES, template, MATCH_THRESHOLD)) {

	/* If we have a previous response to use as a seed, then ...	      */
      // if (oos_match(gv, BOX_WORKING_MEMORY, seed)) {
      latest_WM_item = get_WM_latest(gv);
      if (latest_WM_item >= 0) {
	
	    /* If there is also a current schema, then ...		      */
	  if (oos_match(gv, BOX_CURRENT_SET, current_set)) {
		/* Apply the current schema to the seed and excite the result */

	      content = pl_clause_make_from_string("response(_).");
	      pl_arg_set_to_int(content, 1, apply_schema(current_set, latest_WM_item));
	      oos_message_create(gv, MT_EXCITE, BOX_APPLY_SET, BOX_RESPONSE_NODES, content);
	      total_applyset_messages ++;
	    
	  }
      }
      
	    	
		


    }
#endif

    // pl_clause_free(seed);
    pl_clause_free(template);
    pl_clause_free(previous);
    pl_clause_free(current_set);
}

/* ---------------- BUFFER ACTIVATION CODE HERE------------------------------------ */


static void process_spreading_activation(OosVars *gv, double (*spreading_activation_weights)[10])
{
   /* find response nodes buffer */
   // BoxList *response_nodes_temp = oos_locate_box_ptr(gv, 24); // can't get this function to work?!
  BoxList *response_nodes_temp = NULL;
    for (response_nodes_temp = gv->components; response_nodes_temp != NULL; response_nodes_temp = response_nodes_temp->next) {
        if (response_nodes_temp->id == 24) {
            break;
        }
    }


   TimestampedClauseList *element_i = NULL;

    // calculate vector of net excitation

    double net_excitation[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int i = 0;
    for (element_i = response_nodes_temp->content; i < 10; element_i = element_i->tail) {
      // assumption that spreading_activation_weights[0] is the node representing 0... ??
      int j = 0;
      TimestampedClauseList *element_j;
      for (element_j = response_nodes_temp->content; j < 10; element_j = element_j->tail) {
	net_excitation[i] += (element_j->activation * spreading_activation_weights[i][j]);
	j++;
      }

      i ++;
    }
    

    // apply new activations to current activations
    i = 0;
    for (element_i = response_nodes_temp->content; i < 10; element_i = element_i->tail) {
      element_i->activation = apply_equations(element_i->activation, PERSISTENCE, net_excitation[i], MT_SIGMOID);
      i++;
    }  
}






/*----------------------------------------------------------------------------*/

static void propose_response_output(OosVars *gv)
{
  ClauseType *template, *any_response, *node;

    template = pl_clause_make_from_string("response(_).");

    /* NS - now matches item with biggest above-threshold activation in response nodes  */
    if (oos_match_biggest_above_threshold(gv, BOX_RESPONSE_NODES, template, MATCH_THRESHOLD)) {

        node = pl_clause_copy(template);
	pl_arity_adjust(template, 2);	
	/* Note: Arg 2 of template will be "_" - we want it to be a var while */
	/* we check for membership in Response Buffer			      */

	/* implementing activation in response buffer - we want rule
	   to fire if there is a response in the buffer but it is
	   below threshold 
	   original code: */


	/* reassign template to blank to match ANY response in buffer */
	any_response = pl_clause_make_from_string("response(_,_).");

	if (!oos_match_above_threshold(gv, BOX_RESPONSE_BUFFER, any_response, MATCH_THRESHOLD)) {
	    pl_arg_set_to_int(template, 2, gv->cycle);
	   
	    oos_message_create(gv, MT_ADD, BOX_PROPOSE_RESPONSE, BOX_RESPONSE_BUFFER, template);

	    /* Inhibits response node (moved from Generate Response) */
   	    oos_message_create(gv, MT_INHIBIT, BOX_PROPOSE_RESPONSE, BOX_RESPONSE_NODES, node);
	    
	    
	}
	else {
	    /* The response has already been proposed - do nothing:	      */
	    pl_clause_free(template);
	    pl_clause_free (node);
	}

     	pl_clause_free(any_response);
    }
    else {
	pl_clause_free(template);
	
    }
}

static void generate_response_output(OosVars *gv)
{
  ClauseType *template, *node;
    RngData *task_data = (RngData *)(gv->task_data);
    RngSubjectData *subject;
    long r; // t2;

    subject = &(task_data->trial[gv->block]);

    template = pl_clause_make_from_string("response(_,_).");


    /* old code - produces response after 3 cycles in response buffer 
    if (oos_match(gv, BOX_RESPONSE_BUFFER, template)) {
	if (pl_is_integer(pl_arg_get(template, 2), &t2) && (gv->cycle > t2+3)) {
    */

    if (oos_match(gv, BOX_RESPONSE_BUFFER, template)) {
      if (gv->cycle % task_data->params.generation_period == 0) {

	    /* Inhibit a response node when the response is proposed 
	       2013-06-05 this is also now implemented when propose response -> response buffer */
	    node = pl_clause_copy(template);
	    pl_arity_adjust(node, 1);
	    oos_message_create(gv, MT_INHIBIT, BOX_GENERATE_RESPONSE, BOX_RESPONSE_NODES, node);
	    


	    
	    /* Update WM on some well-defined percentage of trails: */
	    
	    if (task_data->params.wm_update_rate > random_uniform(0.0, 1.0)) {
	      /* update timestamp so WM  reflect cycle they were generated */
	      pl_arg_set_to_int(template, 2, gv->cycle);
	      oos_message_create(gv, MT_ADD, BOX_GENERATE_RESPONSE, BOX_WORKING_MEMORY, pl_clause_copy(template));
	    }
	    /* Produce the response - by adding it the current subject's */
	    /* response list: */
	    if (pl_is_integer(pl_arg_get(template, 1), &r)) {
		subject->response[(subject->n)++] = (int) r;

#ifdef ECHO
		fprintf(stdout, "CYCLE %4d\tRESPONSE %3d: %d\n", gv->cycle, subject->n, (int) r); 
#endif

	    }
	    oos_message_create(gv, MT_CLEAR, BOX_GENERATE_RESPONSE, BOX_RESPONSE_BUFFER, NULL);
      }
    }
    
    pl_clause_free(template);
    if (subject->n >= gv->trials_per_subject) {
	oos_message_create(gv, MT_STOP, BOX_GENERATE_RESPONSE, 0, NULL);
    }
}





/******************************************************************************/

CairoxPoint *coordinate_list_create(int points)
{
    CairoxPoint *coords = (CairoxPoint *)malloc(sizeof(CairoxPoint)*points);
    return(coords);
}

static void coordinate_list_set(CairoxPoint *coordinates, int index, double x, double y)
{
    coordinates[index-1].x = x;
    coordinates[index-1].y = y;
}

Boolean rng_create(OosVars *gv, RngParameters *pars)
{
    RngData *task_data;
    CairoxPoint *coordinates;

    

    oos_messages_free(gv);
    oos_components_free(gv);
    g_free(gv->task_data);

    gv->name = string_copy("RNG");
    gv->cycle = 0;
    gv->block = 0;
    gv->stopped = FALSE;

      
    /* 
double response_nodes_weights[10][10] = { 
  { ACT_SELF, ACT_NEXT, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_PREV},
  { ACT_PREV, ACT_SELF, ACT_NEXT, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI},
  { ACT_INHI, ACT_PREV, ACT_SELF, ACT_NEXT, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI},
  { ACT_INHI, ACT_INHI, ACT_PREV, ACT_SELF, ACT_NEXT, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI},
  { ACT_INHI, ACT_INHI, ACT_INHI, ACT_PREV, ACT_SELF, ACT_NEXT, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI},
  { ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_PREV, ACT_SELF, ACT_NEXT, ACT_INHI, ACT_INHI, ACT_INHI},
  { ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_PREV, ACT_SELF, ACT_NEXT, ACT_INHI, ACT_INHI},
  { ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_PREV, ACT_SELF, ACT_NEXT, ACT_INHI},
  { ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_PREV, ACT_SELF, ACT_NEXT},
  { ACT_NEXT, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_INHI, ACT_PREV, ACT_SELF}, 
};
    */



    oos_process_create(gv, "Task Setting", BOX_TASK_SETTING, 0.2, 0.1, task_setting_output);
    oos_process_create(gv, "Monitoring", BOX_MONITORING, 0.8, 0.1, monitoring_output);
    oos_process_create(gv, "Apply Set", BOX_APPLY_SET, 0.2, 0.7, apply_set_output);
    oos_process_create(gv, "Generate Response", BOX_GENERATE_RESPONSE, 0.8, 0.7, generate_response_output);
    oos_process_create(gv, "Propose Response", BOX_PROPOSE_RESPONSE, 0.5, 0.9, propose_response_output);

    oos_buffer_create(gv, "Current Set", BOX_CURRENT_SET, 0.2, 0.4, BUFFER_DECAY_NONE, 0, BUFFER_CAPACITY_UNLIMITED, 0, BUFFER_EXCESS_IGNORE, BUFFER_ACCESS_RANDOM);   
    
    oos_buffer_create(gv, "Working Memory", BOX_WORKING_MEMORY, 0.8, 0.4, BUFFER_DECAY_ACT_R, 0, BUFFER_CAPACITY_UNLIMITED, 0, BUFFER_EXCESS_IGNORE, BUFFER_ACCESS_LIFO);
    
    oos_buffer_create(gv, "Response Nodes", BOX_RESPONSE_NODES, 0.2, 0.9, BUFFER_DECAY_NONE, 0, BUFFER_CAPACITY_LIMITED, 10, BUFFER_EXCESS_RANDOM, BUFFER_ACCESS_RANDOM);
    
    oos_buffer_create(gv, "Response Buffer", BOX_RESPONSE_BUFFER, 0.5, 0.7, BUFFER_DECAY_NONE, 0, BUFFER_CAPACITY_LIMITED, 1, BUFFER_EXCESS_OLDEST, BUFFER_ACCESS_LIFO);
    

    

    // Task Setting sends to Current Set
    coordinates = coordinate_list_create(2);
    coordinate_list_set(coordinates, 1, 0.19, 0.145);
    coordinate_list_set(coordinates, 2, 0.19, 0.355);
    oos_arrow_create(gv, TRUE, AH_SHARP, coordinates, 2, 1.0);
    // Task Setting reads from Current Set
    coordinates = coordinate_list_create(2);
    coordinate_list_set(coordinates, 1, 0.20, 0.145);
    coordinate_list_set(coordinates, 2, 0.20, 0.355);
    oos_arrow_create(gv, TRUE, AH_BLUNT, coordinates, 2, 1.0);
    // Task Setting reads from Working Memory
    coordinates = coordinate_list_create(4);
    coordinate_list_set(coordinates, 1, 0.21, 0.145);
    coordinate_list_set(coordinates, 2, 0.21, 0.230);
    coordinate_list_set(coordinates, 3, 0.794, 0.230);
    coordinate_list_set(coordinates, 4, 0.794, 0.355);
    oos_arrow_create(gv, FALSE, AH_BLUNT, coordinates, 4, 1.0);

    // Monitoring sends to Current Set
    coordinates = coordinate_list_create(4);
    coordinate_list_set(coordinates, 1, 0.794, 0.145);
    coordinate_list_set(coordinates, 2, 0.794, 0.270);
    coordinate_list_set(coordinates, 3, 0.21, 0.270);
    coordinate_list_set(coordinates, 4, 0.21, 0.355);
    oos_arrow_create(gv, FALSE, AH_SHARP, coordinates, 4, 1.0);
    // Monitoring sends to Response Nodes
    coordinates = coordinate_list_create(4);
    coordinate_list_set(coordinates, 1, 0.794, 0.145);
    coordinate_list_set(coordinates, 2, 0.794, 0.270);
    coordinate_list_set(coordinates, 3, 0.495, 0.270);
    coordinate_list_set(coordinates, 4, 0.495, 0.655);
    oos_arrow_create(gv, FALSE, AH_SHARP, coordinates, 4, 1.0);
    // Monitoring reads from Response Nodes
    coordinates = coordinate_list_create(4);
    coordinate_list_set(coordinates, 1, 0.806, 0.145);
    coordinate_list_set(coordinates, 2, 0.806, 0.285);
    coordinate_list_set(coordinates, 3, 0.505, 0.285);
    coordinate_list_set(coordinates, 4, 0.505, 0.655);
    oos_arrow_create(gv, FALSE, AH_BLUNT, coordinates, 4, 1.0);
    // Monitoring reads from Working Memory
    coordinates = coordinate_list_create(2);
    coordinate_list_set(coordinates, 1, 0.806, 0.145);
    coordinate_list_set(coordinates, 2, 0.806, 0.355);
    oos_arrow_create(gv, TRUE, AH_BLUNT, coordinates, 2, 1.0);

    // Apply Set reads from Current Set
    coordinates = coordinate_list_create(2);
    coordinate_list_set(coordinates, 1, 0.20, 0.655);
    coordinate_list_set(coordinates, 2, 0.20, 0.445);
    oos_arrow_create(gv, TRUE, AH_BLUNT, coordinates, 2, 1.0);
    // Apply Set reads from Working Memory
    coordinates = coordinate_list_create(4);
    coordinate_list_set(coordinates, 1, 0.20, 0.655);
    coordinate_list_set(coordinates, 2, 0.20, 0.55);
    coordinate_list_set(coordinates, 3, 0.794, 0.55);
    coordinate_list_set(coordinates, 4, 0.794, 0.445);
    oos_arrow_create(gv, FALSE, AH_BLUNT, coordinates, 4, 1.0);
    // Generate Response sends to Working Memory
    coordinates = coordinate_list_create(2);
    coordinate_list_set(coordinates, 1, 0.806, 0.655);
    coordinate_list_set(coordinates, 2, 0.806, 0.445);
    oos_arrow_create(gv, TRUE, AH_SHARP, coordinates, 2, 1.0);
    // Apply Set reads from Response Buffer
    coordinates = coordinate_list_create(2);
    coordinate_list_set(coordinates, 1, 0.265, 0.70);
    coordinate_list_set(coordinates, 2, 0.435, 0.70);
    oos_arrow_create(gv, TRUE, AH_BLUNT, coordinates, 2, 1.0);
    // Apply Set seads to Response Nodes
    coordinates = coordinate_list_create(2);
    coordinate_list_set(coordinates, 1, 0.20, 0.745);
    coordinate_list_set(coordinates, 2, 0.20, 0.855);
    oos_arrow_create(gv, TRUE, AH_SHARP, coordinates, 2, 1.0);

    // Generate Response sends to Response Buffer (0.735, 0.79 -> 0.565, 0.79)
    coordinates = coordinate_list_create(2);
    coordinate_list_set(coordinates, 1, 0.735, 0.69);
    coordinate_list_set(coordinates, 2, 0.565, 0.69);
    oos_arrow_create(gv, TRUE, AH_SHARP, coordinates, 2, 1.0);
    // Generate Response reads from Response Buffer (0.735, 0.81 -> 0.565, 0.81)
    coordinates = coordinate_list_create(2);
    coordinate_list_set(coordinates, 1, 0.735, 0.71);
    coordinate_list_set(coordinates, 2, 0.565, 0.71);
    oos_arrow_create(gv, TRUE, AH_BLUNT, coordinates, 2, 1.0);
    // Generate Response sends to Output 
    coordinates = coordinate_list_create(2);
    coordinate_list_set(coordinates, 1, 0.865, 0.70);
    coordinate_list_set(coordinates, 2, 0.965, 0.70);
    oos_arrow_create(gv, TRUE, AH_SHARP, coordinates, 2, 1.0);

    // Propose Response reads from Response Nodes
    coordinates = coordinate_list_create(2);
    coordinate_list_set(coordinates, 1, 0.435, 0.90);
    coordinate_list_set(coordinates, 2, 0.265, 0.90);
    oos_arrow_create(gv, TRUE, AH_BLUNT, coordinates, 2, 1.0);
    // Propose Response sends to Response Buffer
    coordinates = coordinate_list_create(2);
    coordinate_list_set(coordinates, 1, 0.5, 0.855);
    coordinate_list_set(coordinates, 2, 0.5, 0.745);
    oos_arrow_create(gv, TRUE, AH_SHARP, coordinates, 2, 1.0);

    // Annotations: meta-component labels
    oos_annotation_create(gv, "Supervisory", 0.06, 0.25, 14, 0.0, TRUE);
    oos_annotation_create(gv, "System", 0.06, 0.28, 14, 0.0, TRUE);
    oos_annotation_create(gv, "Contention", 0.06, 0.74, 14, 0.0, TRUE);
    oos_annotation_create(gv, "Scheduling", 0.06, 0.77, 14, 0.0, TRUE);


    
    // Annotations: arrow labels
    oos_annotation_create(gv, "Switch", 0.400, 0.257, 12, 0.0, FALSE);
    oos_annotation_create(gv, "Inhibit", 0.485, 0.490, 12, 90.0, FALSE);
    oos_annotation_create(gv, "Update", 0.796, 0.590, 12, 90.0, FALSE);

    if ((task_data = (RngData *)malloc(sizeof(RngData))) != NULL) {
	int i, j;
	for (i = 0; i < MAX_SUBJECTS; i++) {
	    task_data->trial[i].n = 0;
	    for (j = 0; j < MAX_TRIALS; j++) {
		task_data->trial[i].response[j] = -1;
	    }
	}
	task_data->n = 0;
	task_data->params.temperature = pars->temperature;
	task_data->params.monitoring_efficiency = pars->monitoring_efficiency;
	task_data->params.wm_update_rate = pars->wm_update_rate;
	task_data->params.wm_threshold = pars->wm_threshold;
	// task_data->params.wm_decay_type = pars->wm_decay_type;
	task_data->params.generation_period = pars->generation_period;
	gv->task_data = (void *)task_data;
    }
    return(gv->task_data != NULL);
}

void rng_initialise_model(OosVars *gv)
{
    int i;
    double random_starting_activation;



    for (i = 0; i < 10; i++) {

      /* Initialise response nodes to random starting activation */
	char element[64];
	g_snprintf(element, 64, "response(%d).", (9-i)); // create nodes in reverse order (ie. first node is 0)
	random_starting_activation = random_uniform (0.05, STARTING_RESPONSE_NODE_ACTIVATION_MAX);
	oos_buffer_create_element(gv, BOX_RESPONSE_NODES, element, random_starting_activation);

	/* Initialise  WM chunks to random activation with 0 timestamp*/
	/* response, timestamp, counter */
	g_snprintf(element, 64, "response(%d, 0).", (9-i)); 
	oos_buffer_create_element(gv, BOX_WORKING_MEMORY, element, 0); 

    }


}

void rng_globals_destroy(RngData *task_data)
{
    g_free(task_data);
}

/******************************************************************************/

Boolean oos_step_wrapper(OosVars *gv)
{
  /* because spreading activation needs to be implemented inside
     oos_step for the x oos browser */
  Boolean tmp;
  tmp = oos_step(gv);

  /* process buffer activation */
  // process_wm_activation (gv); // now implemented in oos.c as part of oos_buffer_apply_decay

  int i = 0;
  for (i = 0; i < SPREADING_ACTIVATION_ITERATIONS_PER_STEP; i++)
    {
      process_spreading_activation (gv, response_nodes_weights);
    }
  return tmp;
}





void rng_run(OosVars *gv)
{
    FILE *fp;

    /* Uncomment one of the following to save trial-by-trial output */
//    fp = NULL; /* Supress output */
//    fp = stdout; /* Send output to the terminal */
    fp = fopen("output_log.dat", "w"); /* Save output to output_log.dat file */

 // print output file header
    /*
    fprintf(fp, "R\tRNG\tRG\tCS1\tCS2\tCST");
    int i;
    for (i = -9; i < 10; i++) {
      fprintf (fp, "\tA%d", i);
    }
    fprintf (fp, "\n");
    */

    oos_initialise_session(gv);
    while (gv->block < gv->subjects_per_experiment) {
	oos_initialise_trial(gv);
 	rng_initialise_model(gv);    
	

	while (oos_step_wrapper(gv)) {


#ifdef DEBUG
	    oos_dump(gv, TRUE);
#endif
	}
	rng_analyse_subject_responses(fp, gv, gv->block);
	// fprint_message_counts (stdout, gv);
	oos_step_block(gv);
    }
#ifdef DEBUG
    fprint_schema_counts(fp, gv);
#endif

    if ((fp != NULL) && (fp != stdout)) {
        fclose(fp);
    }
}

/******************************************************************************/

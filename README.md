##simulation_1.3_params##

- tweaking activation parameters so that activation in response nodes is a) doesn't have a bias for going forwards, and b) is more balanced with supervisory system such that they both get a say.
- nice param settings

rng_model.c
``` c
#define ACT_SELF 0.500	  // .665	
#define ACT_NEXT -0.0239  // -0.0248
#define ACT_PREV -0.0241  // -0.0252
#define ACT_INHI -0.033   // -0.047
#define ACT_NEXT_WR -0.0247 // activation from next node when wrapping round
#define ACT_PREV_WR -0.0252 // activation from prev node when wrapping round
#define PERSISTENCE 0.93
#define STARTING_RESPONSE_NODE_ACTIVATION_MAX 0.3
#define SPREADING_ACTIVATION_ITERATIONS_PER_STEP 14 // debug
```

oos.c
``` c
#define STRENGTH_EXCITE 0.18
#define STRENGTH_INHIBIT -8
```


##Simulation_1.3_randomlogic##

- updating the screwy check_random logic in
simulations 1.3 and 1.4 that lead to excessive production of +2
associates


supervisory system - random number generation model

##simulation_1.3_randomlogic_1##
aims: want supervisory and contention scheduling to *interact* a bit more
- changed parameter settings for spreading activation 
- changed parameter setting for EXCITE strength (oos.c) - much slower
- changed set switch latency parameter to give activation time to do its thing
- changed APPLY_SET rule such that it still activates response nodes even when there is a response in buffer



simulation_1.3_randomlogic
- changed check_random logic so model conforms better with simulations 2 and 3
- PROBLEM: model now continues to overproduce +/-1 even at longer rates of generation
- also changed set switch latency to 2 (from 4) to give supervisory system better chance of being heard

simulation_1.3 
- simplified schema selection (removed temperature parameter)

remove_temp_parameter
 - fix branch (merge out to all 4 simulations: simulation_1.3, simulation_2.3, simulation_3.3, simulation_4.3)
 - changes to schema selection in rng_model so schema weights directly control relative probabilities

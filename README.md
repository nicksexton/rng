rng
===

simulation_2.3_params
* included nice parameters from simulation_1.3_params
* reinstated +/-1 explicit monitoring rule




supervisory system - random number generation model

simulation_1.3_randomlogic_1
aims: want supervisory and contention scheduling to *interact* a bit more
- changed parameter settings for spreading activation 
- changed parameter setting for EXCITE strength (oos.c) - much slower
- changed set switch latency parameter to give activation time to do its thing
- changed APPLY_SET rule such that it still activates response nodes even when there is a response in buffer



simulation_1.3 
simulation_2.3
- simplified schema selection (removed temperature parameter)

remove_temp_parameter
 - fix branch (merge out to all 4 simulations: simulation_1.3, simulation_2.3, simulation_3.3, simulation_4.3)
 - changes to schema selection in rng_model so schema weights directly control relative probabilities

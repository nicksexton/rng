rng
===

supervisory system - random number generation model

simulation_1.3_randomlogic_1
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

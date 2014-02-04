rng
===

supervisory system - random number generation model


simulation_1.3_randomlogic
- changed check_random logic so model conforms better with simulations 2 and 3
- PROBLEM: model now continues to overproduce +/-1 even at longer rates of generation
- also changed set switch latency to 2 (from 4) to give supervisory system better chance of being heard

simulation_1.3 
- simplified schema selection (removed temperature parameter)

remove_temp_parameter
 - fix branch (merge out to all 4 simulations: simulation_1.3, simulation_2.3, simulation_3.3, simulation_4.3)
 - changes to schema selection in rng_model so schema weights directly control relative probabilities

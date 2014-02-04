Random Number Generation
===

supervisory system - random number generation model


Simulation 3 - simulating the effects of individual differences in
number schemas on RNG 

cherry-picked commit: simulation_1.3_randomlogic_1 
aims: want supervisory and contention scheduling to *interact* a bit more
- changed parameter settings for spreading activation 
- changed parameter setting for EXCITE strength (oos.c) - much slower
- changed set switch latency parameter to give activation time to do its thing
- changed APPLY_SET rule such that it still activates response nodes even when there is a response in buffer





Uses same assumtions about working memory as Simulation 2 

hypotheses - 

- differences in schema selection weights matrix
(reflecting simulated individual idiosyncracies in schema selection
bias, given the current schema) should increase RNG score (ie, should
be closer to the human range ie. z score of ~2)

- individual difference in schema selection weights (modelled as noise,
calculated for each subject individually) would be unsystematic, hence
should have no systematic effect on averaged indices sensitive to specific
biases eg. CS1, A, CS2, etc. 


simulation_3.3 merged with

remove_temp_parameter
 - fix branch (merge out to all 4 simulations: simulation_1.3, simulation_2.3, simulation_3.3, simulation_4.3)
 - changes to schema selection in rng_model so schema weights directly control relative probabilities


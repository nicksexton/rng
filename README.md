Random Number Generation
===

supervisory system - random number generation model

Simulation 4 - 
between subjects noise in schema selection
simple working memory implementation (same as simulation 1)


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


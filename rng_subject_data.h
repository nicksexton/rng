//#include "xrng.h"

// RngScores subject_c1_means, subject_c2_means, subject_c3_means, subject_c4_means,subject_c5_means, subject_c6_means;
// RngScores subject_c1_sd, subject_c2_sd, subject_c3_sd, subject_c4_sd,subject_c5_sd, subject_c6_sd;

/* R,     RNG,   TPI,   RG,   CS1,  CS2, CST, Associates */

/* associates -9, -8, -7 ... -1, 0, 1, ... 7, 8, 9 */

/* Data from Towse 1998 */

RngDataset dataset_towse_1998 = {


  .subject_c6_means = {FALSE, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
		       0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c6_sd    = {FALSE, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },

 .subject_c5_means = {FALSE, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
		       0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c5_sd    = {FALSE, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },

 .subject_c4_means = {FALSE, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
		       0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c4_sd    = {FALSE, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  
  


/*                            R,     RNG,    TPI,   RG,   CS1,  CS2,  CST, Associates */
  .subject_c3_means = {TRUE, 1.030, 0.255,  0.000, 0.00, 0.00, 0.00, 0.00, 
		       {0.015, 0.025, 0.026, 0.046, 0.057, 0.060, 0.081, 0.094, 0.103, 
			0.015, 0.073, 0.096, 0.070, 0.070, 0.057, 0.034, 0.029, 0.023, 0.008, }
  },
  /* SD is placeholder data */
  .subject_c3_sd    = {TRUE, 0.000, 0.000, 0.000, 0.00, 0.00, 0.00, 0.00,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },


  .subject_c2_means = {TRUE, 1.245, 0.292, 0.000, 0.00, 0.000, 0.000, 0.000, 
		       {0.018, 0.025, 0.028, 0.036, 0.047, 0.048, 0.068, 0.104, 0.126, 
			0.009, 0.139, 0.106, 0.065, 0.065, 0.041, 0.041, 0.025, 0.015, 0.008, }
  },
  /* SD is placeholder data */
  .subject_c2_sd    = {TRUE, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },

/* R,     RNG,   TPI,   RG,   CS1,  CS2, CST, Associates */
  .subject_c1_means = {TRUE, 2.097, 0.328, 0.000, 0.000, 0.000, 0.000, 0.000, 
		       {0.015, 0.018, 0.026, 0.027, 0.043, 0.050, 0.056, 0.086, 0.173, 
			0.017, 0.173, 0.111, 0.056, 0.053, 0.045, 0.031, 0.025, 0.018, 0.008, }
  },
  /* SD is placeholder data */
  .subject_c1_sd    = {TRUE, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },


/* Control data for calculating Z scores... pseudorandom algorithm, set = 0 - 9, n=10,000 */

 /* R,     RNG,   TPI,   RG,   CS1,  CS2, CST, Associates */
  .subject_ctl_means = {TRUE,  1.998, 0.242, 0.000, 8.99, 26.06, 22.39, 48.44, 
			{0.010,	0.020,	0.030,	0.040,	0.050,	0.060,	0.070,	0.080,	0.090,	0.100,	0.090,	0.080,	0.070,	0.060,	0.050,	0.040,	0.030,	0.020,	0.010, }

  },


  .subject_ctl_sd    = {TRUE, 0.940, 0.026, 0.010, 0.331, 9.289, 8.337, 11.621,
			{0.010, 0.014,	0.016,	0.019,	0.021,	0.023,	0.025,	0.027,	0.029,	0.030,	0.028,	0.027,	0.026,	0.023,	0.021,	0.019,	0.016,	0.014,	0.010, }
  },
  


};



/* Data from Jahanshahi 2006 */
RngDataset dataset_jahanshahi_2006 = {


/* condition 6 = 3.0s */
/* --------------------disp? R,     RNG,   TPI,   RG,   CS1,  CS2,  CST,  Associates */
  .subject_c6_means = {TRUE, 0.000, 0.330, 0.000, 7.29, 15.9, 26.8, 42.7, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c6_sd    = {TRUE, 0.000, 0.017, 0.000, 0.21, 7.5, 6.2, 9.2,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  
  /* condition 5 = 2.5s */
  .subject_c5_means = {TRUE, 0.000, 0.317, 0.000, 7.15, 18.4, 27.3, 45.9, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c5_sd    = {TRUE, 0.000, 0.014, 0.000, 0.25, 5.6, 3.6, 7.8,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },

/* condition 4 = 2.0s */


  .subject_c4_means = {TRUE, 0.000, 0.317, 0.000, 7.19, 20.5, 33.9, 53.7, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c4_sd    = {TRUE, 0.000, 0.015, 0.000, 0.34, 8.9, 4.3, 7.8,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },


/* condition 3 = 1.5s */
  .subject_c3_means = {TRUE, 0.000, 0.317, 0.000, 7.41, 28.2, 33.2, 61.5, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c3_sd    = {TRUE, 0.000, 0.022, 0.000, 0.25, 10.0, 6.9, 10.7,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },

/* condition 2 = 1.0s */
  .subject_c2_means = {TRUE, 0.000, 0.340, 0.000, 7.41, 32.7, 30.8, 63.7, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c2_sd    = {TRUE, 0.000, 0.016, 0.000, 0.26, 9.1, 4.8, 9.2,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },


/* conditon 1 0.5s */

  .subject_c1_means = {TRUE, 0.000, 0.349, 0.000, 7.17, 49.0, 30.4, 79.3, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c1_sd    = {TRUE, 0.000, 0.021, 1.000, 0.28, 8.9, 3.6, 7.5,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },



/* Control data for calculating Z scores... pseudorandom algorithm, set = 1 - 9, n = 10000 */
/*                            R,     RNG,    TPI,   RG,   CS1,  CS2,  CST, Associates */
  .subject_ctl_means = {TRUE, 1.857, 0.276, 0.000, 8.205, 29.512, 25.073, 54.585, 
			{0.000,	0.012,	0.025,	0.037,	0.049,	0.062,	0.074,	0.087,	0.099,	0.111,	0.098,	0.086,	0.074,	0.062,	0.049,	0.037,	0.025,	0.012,	0.000,}
  },
  .subject_ctl_sd    = {TRUE, 0.925, 0.024, 0.01, 0.280, 10.254, 9.053, 12.726,
			{ 0.000, 0.011,	0.015,	0.018,	0.021,	0.023,	0.025,	0.028,	0.030,	0.032,	0.029,	0.028,	0.025,	0.023,	0.021,	0.018,	0.015,	0.011, 0.000, }
  },

};

/* TMS Data from Jahanshahi 1998 */
RngDataset dataset_jahanshahi_1998 = {


  /* condition 6 (blank) */
/* --------------------disp? R,     RNG,   TPI,   RG,   CS1,  CS2,  CST,  Associates */
  .subject_c6_means = {FALSE, 0.000, 0.000, 0.000, 0.00, 00.0, 00.0, 00.0,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c6_sd    = {FALSE, 0.000, 0.000, 0.000, 0.00, 0.0, 0.0, 0.0,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  
  /* condition 5 (blank )*/
  .subject_c5_means = {FALSE, 0.000, 0.000, 0.000, 0.00, 00.0, 00.0, 00.0, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c5_sd    = {FALSE, 0.000, 0.014, 0.000, 0.25, 5.6, 3.6, 7.8,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },

/* condition 4 = TMS MFC */
/* --------------------disp? R,     RNG,   TPI,   RG,   CS1,  CS2,  CST,  Associates */
  .subject_c4_means = {TRUE, 0.000, 0.000, 0.000, 7.41, 32.49, 35.38, 67.47, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c4_sd    = {TRUE, 0.000, 0.015, 0.000, 0.23, 0.0, 0.0, 8.65,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },


/* condition 3 = TMS R DLPFC */
/* --------------------disp? R,     RNG,   TPI,   RG,   CS1,  CS2,  CST,  Associates */
  .subject_c3_means = {TRUE, 0.000, 0.000, 0.000, 7.41, 31.55, 38.61, 70.19, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c3_sd    = {TRUE, 0.000, 0.022, 0.000, 0.30, 0.0, 0.0, 4.97,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },

/* condition 2 = TMS L DLPFC */
/* --------------------disp? R,     RNG,   TPI,   RG,   CS1,  CS2,  CST,  Associates */
  .subject_c2_means = {TRUE, 0.000, 0.000, 0.000, 7.55, 36.74, 29.14, 65.71, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c2_sd    = {TRUE, 0.000, 0.016, 0.000, 0.22, 0.0, 0.0, 8.01,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },


/* conditon 1 control (no stim) */
/* --------------------disp? R,     RNG,   TPI,   RG,   CS1,  CS2,  CST,  Associates */
  .subject_c1_means = {TRUE, 0.000, 0.000, 0.000, 7.74, 22.07, 36.84, 57.21, 
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },
  .subject_c1_sd    = {TRUE, 0.000, 0.000, 0.000, 0.17, 0.0, 0.0, 4.49,
		       {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 
			0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, }
  },



/* Control data for calculating Z scores... pseudorandom algorithm, set = 1 - 9, n = 10000 */
/*                            R,     RNG,    TPI,   RG,   CS1,  CS2,  CST, Associates */
  .subject_ctl_means = {TRUE, 1.857, 0.276, 0.000, 8.205, 29.512, 25.073, 54.585, 
			{0.000,	0.012,	0.025,	0.037,	0.049,	0.062,	0.074,	0.087,	0.099,	0.111,	0.098,	0.086,	0.074,	0.062,	0.049,	0.037,	0.025,	0.012,	0.000,}
  },
  .subject_ctl_sd    = {TRUE, 0.925, 0.024, 0.01, 0.280, 10.254, 9.053, 12.726,
			{ 0.000, 0.011,	0.015,	0.018,	0.021,	0.023,	0.025,	0.028,	0.030,	0.032,	0.029,	0.028,	0.025,	0.023,	0.021,	0.018,	0.015,	0.011, 0.000, }
  },

};



/* Control data for calculating Z scores in non-X model... pseudorandom algorithm, set size [0 - 9] n=10,000 */
/*                                              R,     RNG,   TPI,   RG,   CS1,   CS2,   CST,  Associates */
RngScores reference_montecarlo_means =  {TRUE,  1.998, 0.242, 0.000, 8.99, 26.06, 22.39, 48.44, 
			{0.010,	0.020,	0.030,	0.040,	0.050,	0.060,	0.070,	0.080,	0.090,	0.100,	0.090,	0.080,	0.070,	0.060,	0.050,	0.040,	0.030,	0.020,	0.010, }
};

/*                                             R,     RNG,    TPI,   RG,   CS1,  CS2,  CST, Associates */
RngScores reference_montecarlo_sd    =  {TRUE, 0.940, 0.026, 0.010, 0.331, 9.289, 8.337, 11.621,
			{0.010, 0.014,	0.016,	0.019,	0.021,	0.023,	0.025,	0.027,	0.029,	0.030,	0.028,	0.027,	0.026,	0.023,	0.021,	0.019,	0.016,	0.014,	0.010, }
};





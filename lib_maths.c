/*******************************************************************************

    FILE: lib_maths.c
    AUTHOR: R. Cooper (translated from C++ written by SVW)
    CREATION DATE: 
    CONTENTS: 

*******************************************************************************/

#include <math.h>
#include <stdio.h>
#include "lib_maths.h"

/******************************************************************************/

static double squash(double x)
{
   double y = exp(x);
   return((y - 1.0) / (y + 1.0));
}

/*............................................................................*/

static double bounding_function(MathsType mathsSystem, double x)
{
    double r = (ACT_REST - ((ACT_MAX+ACT_MIN) / 2.0)) * (2.0 / (ACT_MAX - ACT_MIN));
    double fx, squashed, a;

    a = log ((1.0 + r) / (1.0 - r));

    switch (mathsSystem)  {
	case MT_SIGMOID:
	    fx = x + a;
	    break;

	case MT_TANH:
	    fx = (2.0 * x) + a;
	    break;

	case MT_HALFX:
	    fx = (x / 2.0) + a;
	    break;

	default:
	    fprintf(stderr, "Invalid MathsType in bounding_function\n");
	    return 0.0;
	    break;
    }

    squashed = (exp(fx) - 1.0) / (exp(fx) + 1.0);

    return((squashed * (ACT_MAX - ACT_MIN) / 2.0) + ((ACT_MAX + ACT_MIN) / 2.0));
}

/*............................................................................*/

static double inverse_bounding_function(MathsType mathsSystem, double x)
{
  if (x >= ACT_MAX) {
    return(500);               // to prevent NaN rounding errors - was 999
  }
  else if (x <= ACT_MIN) {
    return(-500);
  }
  else {

    double r = (ACT_REST - ((ACT_MAX + ACT_MIN) / 2.0)) * (2.0 / (ACT_MAX - ACT_MIN));
    double t = (x -       ((ACT_MAX + ACT_MIN) / 2.0)) * (2.0 / (ACT_MAX - ACT_MIN));
    double a = log ((1.0 + r) / (1.0 - r));
    double b = log ((1.0 + t) / (1.0 - t));
    double c = b - a;
    double fx = 0.0;

    switch (mathsSystem) {
	case MT_SIGMOID:
	    fx = c;
	    break;

	case MT_TANH:
	    fx = c / 2.0;
	    break;

	case MT_HALFX:
	    fx = c * 2.0;
	    break;

	default:
	    fprintf(stderr, "Invalid MathsType in inverse_bounding_function\n");
	    break;
    }

    return(fx);
  }
}

/*............................................................................*/

static double epsilon_function(double previous, double persistence, double input, double x)
{
    double epsilon = 0.0;

    if ((input > 0.0) && (previous < ACT_MAX)) {
	epsilon = x * (ACT_MAX - previous);
    }
    else if ((input < 0.0) && (previous > ACT_MIN)) {
	epsilon = x * (previous - ACT_MIN);
    }

    return((persistence * previous) + ((1 - persistence) * ACT_REST) + epsilon);
}

/*............................................................................*/

double apply_equations(double previous, double persistence, double input, MathsType mathsSystem)
{
    double x;
    double fx = 0.0;

    switch (mathsSystem) {

    case MT_SIGMOID:
	x = inverse_bounding_function(MT_SIGMOID,previous)*persistence+input;
	fx = bounding_function(MT_SIGMOID, x);
	break;

    case MT_TANH:
	x = inverse_bounding_function(MT_TANH,previous)*persistence+input;
	fx = bounding_function(MT_TANH, x);
	break;

    case MT_HALFX:
	x = inverse_bounding_function(MT_HALFX,previous)*persistence+input;
	fx = bounding_function(MT_HALFX, x);
	break;

    case MT_M_R:
	x = input;
	fx = epsilon_function(previous, persistence, input, x);
	break;

    case MT_HOUGHTON:
	x = squash(input);
	fx = epsilon_function(previous, persistence, input, x);
	break;

    case MT_NORMALISED:
	fx = (previous * persistence) + input;
	break;

    default:
	fprintf(stderr, "Invalid MathsType (%d) in apply_equations\n", (int) mathsSystem);
	break;
    }

    return(fx);
}

/******************************************************************************/

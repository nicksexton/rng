#ifndef _LIB_MATHS_H_

#define _LIB_MATHS_H_

typedef enum mt {
    MT_SIGMOID, MT_TANH, MT_HALFX, MT_M_R, MT_HOUGHTON, MT_NORMALISED
} MathsType;

extern double apply_equations(double previous, double persistence, double input, MathsType mathsSystem);

#define ACT_REST 0.1
#define ACT_MAX 1.0
#define ACT_MIN 0.0

#endif

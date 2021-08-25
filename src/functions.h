#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

/* declaration of functions */
/* fuction to take the derivative */
double diff_eco(double x, double delta, double r);
/* function for calculating the ecologic map */
double ecologic_map(double x, double y, double r);
/* function for calculation the lyapunov exponent via simple method */
double lyapunov_exponent_simple(double x0, double x1, int n, double r);
/* function for calculation of the lyapunov exponent via first derivative */
double lyapunov_exponent_advanced(double x0, int n, double r);
/* function to calculate the derivative of the ecologic_mao */
double eco_analytic_diff(double x, double r);
double eco_numeric_diff(double x, double delta, double r);

#endif
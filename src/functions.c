#include "functions.h"


/* definition of functions */
double ecologic_map(double x, double y, double r)
{
	return r * x * exp(1 - x * y);
}

double eco_numeric_diff(double x, double delta, double r)
{   double x_left = x - delta;
    double x_right = x + delta;
	double f_left = ecologic_map(x_left, x_left, r);
	double f_right = ecologic_map(x_right, x_right, r);
	return (f_right - f_left) / (2 * delta);
}

double eco_analytic_diff(double x, double r)
{   return r*(-1. * exp(1.-x*x))*(2.*x*x-1.);
}

double lyapunov_exponent_simple(double x0, double x1, int n, double r)
{
    double delta_x = x0 - x1;
    for (int i = 0; i < n; i++)
    {
        x0 = ecologic_map(x0, x0, r);
        x1 = ecologic_map(x1, x1, r);
    }
    return log(fabs((x0 - x1)/delta_x)) / n;
}

double lyapunov_exponent_advanced(double x0, int n, double r)
{

    double tmp_sum =0.0;
    for (int i = 0; i < n; i++ )
    {
        tmp_sum += log(fabs(eco_analytic_diff(x0, r)));
        x0 = ecologic_map(x0, x0, r);

    }
    return tmp_sum / n;

}

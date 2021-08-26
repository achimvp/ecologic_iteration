#include "functions.h"

/*  definition of ecologic map function */
double ecologic_map(double x, double y, double r)
{
	return r * x * exp(1 - x * y);
}

/*  analytic derivative of the ecologic map */
double eco_analytic_diff(double x, double r)
{   return r*(-1. * exp(1.-x*x))*(2.*x*x-1.);
}

/*  simple estimation of the lyapunov exponent based on the 
    differences of two trajectories over time 
*/
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

/*  advanced estimation of the lyapunov exponent based on the
    derivative of one trajectorie over time
*/
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

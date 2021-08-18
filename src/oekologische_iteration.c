#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

/* declaration of functions */
/* function for calculating the ecologic map */
double ecologic_map(double x, double y, double r);
/* function for calculation the lyapunov exponent via simple method */
double lyapunov_exponent_simple();
/* function for calculation of the lyapunov exponent via first derivative */
double lyapunov_exponent_advanced();
void excercise1();

/* main function */
int main(void)
{
	excercise1();
	return EXIT_SUCCESS;
}


/* definition of functions */
double ecologic_map(double x, double y, double r)
{
	return r * x * exp(1 - x * y);
}
void excercise1()
{
	double x0 = 1.0; // starting value for x
	double x1 = 1.0; // starting value for y
	double r = 0.5;  // value for bifurcation parameter
	int N = 200;    // number of iteration steps

	FILE* iterations = fopen("iteration_values.csv", "w");

	/* write file header and initial values */
	fprintf(iterations, "n,x\n0,%g", x1);
	/* iteration loop */
	for (int i = 0; i < N; i++)
	{
		double tmp = ecologic_map(x0, x1, r);
		x0 = x1;
		x1 = tmp;
		fprintf(iterations, "\n%d,%g", i, x1);
	};
	fclose(iterations);
}
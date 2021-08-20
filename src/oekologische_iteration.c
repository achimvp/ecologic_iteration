#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

/* declaration of functions */
/* function for calculating the ecologic map */
double ecologic_map(double x, double y, double r);
/* function for calculation the lyapunov exponent via simple method */
double lyapunov_exponent_simple(double x0, double x1, int n, double r);
/* function for calculation of the lyapunov exponent via first derivative */
double lyapunov_exponent_advanced();
void exercise1();
void bifurcation_diagram();
void exercise3();

/* main function */
int main(void)
{
	exercise1();
    bifurcation_diagram();
    exercise3();
	return EXIT_SUCCESS;
}


/* definition of functions */
double ecologic_map(double x, double y, double r)
{
	return r * x * exp(1 - x * y);
}
void exercise1()
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

void bifurcation_diagram()
{   
    int rs = 100000;  // number of rs to simulate dynamics for
    double r[rs];  // array for the values of r
    double step = 10. / rs;  // step size for equal spacing of r

    /* fill the r array with equally spaced values between 0 and 100*/
    for (int i = 0; i < rs; i++)
    {
        r[i] = i * step;
    };
    

    FILE* fp = fopen("ecologic_map_fine.csv", "w");

    /* simulate the dynamics for every r */
    for (int j = 0; j < rs; j++)
    {   
        double x0 = 0.5;
        double x1 = 0.5;
        fprintf(fp, "%g", r[j]);
        for (int i = 0; i < 1000; i++)
        {
            double tmp = ecologic_map(x0, x1, r[j]);
            x0 = x1;
            x1 = tmp;
            if (i >= 950)
            {
                fprintf(fp, ",%g", x1);
            }
            
        }
        fprintf(fp, "\n");
    };

}

double lyapunov_exponent_simple(double x0, double x1, int n, double r)
{
    double delta_x = x0 - x1;
    for (int i = 0; i < n; i++)
    {
        x0 = ecologic_map(x0, x0, r);
        x1 = ecologic_map(x1, x1, r);
    }
    return log(fabs(delta_x / (x0 - x1))) / n;
}

void exercise3()
{
    double r = 0.0;
    int rs = 10000;
    int n = 100;
    double x0 = 0.5;
    double x1 = x0 + 1e-6;
    double step = 5. / rs;

    FILE *fp = fopen("lyapunov_exponent_simple.csv", "w");

    /* write file header */
    fprintf(fp, "r,lypunov_exponent");
    
    for (int i = 0; i < rs; i++)
    {
        double le = lyapunov_exponent_simple(x0, x1, n, r);
        fprintf(fp, "\n%g,%g", r, le);
        r += step;
    }
    fclose(fp);
}
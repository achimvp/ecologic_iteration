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
/* simulate the map for fixed set of parameters */
void exercise1();
/* bifurcation diagram as function of r for two step iteration*/
void exercise2();
/* bifurcation diagram for single step iteration */
void exercise3();
/* compute lyapunov exponent for single step iteration */
void exercise4();

/* main function */
int main(void)
{
	exercise1();
    exercise2();
    exercise3();
    exercise4();
	return EXIT_SUCCESS;
}


/* definition of functions */
double ecologic_map(double x, double y, double r)
{
	return r * x * exp(1 - x * y);
}

double diff_eco(double x, double delta, double r)
{   double x_left = x - delta;
    double x_right = x + delta;
	double f_left = ecologic_map(x_left, x_left, r);
	double f_right = ecologic_map(x_right, x_right, r);
	return (f_right - f_left) / (2 * delta);
}

void exercise1()
{
	double x0[] = {.5, .5, .5, .5}; // starting value for x
	double x1[] = {.5, .5, .5, .5}; // starting value for y
	double rs[] = {0.1, 0.5, 0.9, 2.};  // value for bifurcation parameter
	int N = 200;    // number of iteration steps

	FILE* iterations = fopen("iteration_values.csv", "w");

	/* write file header and initial values */
	fprintf(iterations, "n,%g,%g,%g,%g\n", rs[0], rs[1], rs[2], rs[3]);
	fprintf(iterations, "0,%g,%g,%g,%g", x1[0], x1[1], x1[2], x1[3]);
	/* iteration loop */
	for (int i = 1; i <= N; i++)
	{
        fprintf(iterations, "\n%d", i);
        for (int i = 0; i < 4; i++)
        {
            double tmp = ecologic_map(x0[i], x1[i], rs[i]);
            x0[i] = x1[i];
            x1[i] = tmp;
            fprintf(iterations, ",%g", x1[i]);
        }
	};
	fclose(iterations);
}

void exercise2()
{   
    int rs = 10000;  // number of rs to simulate dynamics for
    double r[rs];  // array for the values of r
    double step = 3. / rs;  // step size for equal spacing of r

    /* fill the r array with equally spaced values between 0 and 100*/
    for (int i = 0; i < rs; i++)
    {
        r[i] = i * step;
    };
    

    FILE* fp = fopen("ecologic_map_twostep.csv", "w");

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

void exercise3()
{   
    int rs = 10000;  // number of rs to simulate dynamics for
    double r[rs];  // array for the values of r
    double step = 3. / rs;  // step size for equal spacing of r

    /* fill the r array with equally spaced values between 0 and 100*/
    for (int i = 0; i < rs; i++)
    {
        r[i] = i * step;
    };
    

    FILE* fp = fopen("ecologic_map_onestep.csv", "w");

    /* simulate the dynamics for every r */
    for (int j = 0; j < rs; j++)
    {   
        double x0 = 0.5;
        fprintf(fp, "%g", r[j]);
        for (int i = 0; i < 1000; i++)
        {
            x0 = ecologic_map(x0, x0, r[j]);
            if (i >= 950)
            {
                fprintf(fp, ",%g", x0);
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
    return log(fabs((x0 - x1)/delta_x)) / n;
}

double lyapunov_exponent_advanced(double x0, int n, double r)
{

    double tmp_sum =0.0;
    for (int i = 0; i < n; i++ )
    {
        tmp_sum += log(fabs(diff_eco(x0, 0.01, r)));
        x0 = ecologic_map(x0, x0, r);

    }
    return tmp_sum / n;

}

void exercise4()
{
    double r = 0.0;
    int rs = 10000;
    int n = 50;
    double x0 = 0.5;
    double x1 = x0 + 1e-6;
    double step = 5. / rs;

    FILE *fp = fopen("lyapunov_exponent_simple.csv", "w");
    FILE *fp2 = fopen("lyapunov_exponent_advances.csv", "w");
    

    /* write file header */
    fprintf(fp, "r,lypunov_exponent");
    fprintf(fp2, "r,lypunov_exponent");
    
    for (int i = 0; i < rs; i++)
    {
        double le = lyapunov_exponent_simple(x0, x1, n, r);
        fprintf(fp, "\n%g,%g", r, le);

        double le2 = lyapunov_exponent_advanced(x0, n, r);
        fprintf(fp2, "\n%g,%g", r, le2);
        r += step;
    }
    fclose(fp);
    fclose(fp2);
    
}
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
/* simulate the map for fixed set of parameters */
void exercise1();
/* bifurcation diagram as function of r for two step iteration*/
void exercise2();
/* bifurcation diagram for single step iteration */
void exercise3();
/* compute lyapunov exponent for single step iteration */
void exercise4();

void exercise5();

/* main function */
int main(void)
{
	exercise1();
    exercise2();
    exercise3();
    exercise4();
    exercise5();
	return EXIT_SUCCESS;
}


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

void exercise1()
{
	double x0[] = {.5, .5, .5, .5}; // starting value for x
	double x1[] = {.5, .5, .5, .5}; // starting value for y
	double rs[] = {0.367, 0.369, 1.5, 1.6};  // value for bifurcation parameter
	int N = 200;    // number of iteration steps

	FILE* iterations = fopen("data/iteration_values.csv", "w");

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
    

    FILE* fp = fopen("data/ecologic_map_twostep.csv", "w");

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
    

    FILE* fp = fopen("data/ecologic_map_onestep.csv", "w");

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
        tmp_sum += log(fabs(eco_analytic_diff(x0, r)));
        x0 = ecologic_map(x0, x0, r);

    }
    return tmp_sum / n;

}

void exercise4()
{
    double r = 0.0;
    int rs = 10000;
    //int n = 1000;
    int ns[] = {10,20,50,1000};
    double x0 = 0.5;
    double x1 = x0 + 1e-3;
    double step = 5. / rs;

    double le_simple = 0;
    double le_advanced = 0;

    FILE *fp = fopen("data/lyapunov_exponent_simple.csv", "w");
    FILE *fp2 = fopen("data/lyapunov_exponent_advanced.csv", "w");
    

    /* write file header */
    fprintf(fp, "r,%d,%d,%d,%d", ns[0],ns[1],ns[2],ns[3]);
    fprintf(fp2,"r,%d,%d,%d,%d", ns[0],ns[1],ns[2],ns[3]);
    
    for (int i = 0; i < rs; i++)
    {   
        fprintf(fp,"\n%g",r);
        for(int i = 0; i<4; i++){
            le_simple = lyapunov_exponent_simple(x0, x1, ns[i], r);
            fprintf(fp, ",%g", le_simple);

        }

        fprintf(fp2,"\n%g",r);
        for(int i = 0; i<4; i++){
            le_advanced = lyapunov_exponent_advanced(x0, ns[i], r);
            fprintf(fp2, ",%g", le_advanced);

        }
        

        //double le2 = lyapunov_exponent_advanced(x0, n, r);
        //fprintf(fp2, "\n%g,%g", r, le2);
        r += step;
    }
    fclose(fp);
    fclose(fp2);
    
}

void exercise5()
{
    FILE* fp = fopen("data/differences.csv", "w");
    int n = 100;
    double x_start = 0.5;
    double delta = 0.01;
    double x_i0[] = {x_start, x_start, x_start}; // starting value for x
	double x_i1[] = {x_start + delta, x_start+delta, x_start +delta}; // starting value for y
	double rs_i[] = {0.5, 1.2, 1.5};  // value for bifurcation parameter

    fprintf(fp,"%g,%g,%g,%g,%g", x_start, delta,  rs_i[0],  rs_i[1], rs_i[2]);

    //fprintf(fp,"n, %g,%g,%g", rs_i[0], rs_i[1], rs_i[2]);
    for(int i = 0; i < n; i++){
        fprintf(fp, "\n%d", i);
        for (int i = 0; i < 3; i++)
        {
            x_i0[i] = ecologic_map(x_i0[i], x_i0[i], rs_i[i]);
            x_i1[i] = ecologic_map(x_i1[i], x_i1[i], rs_i[i]);

            fprintf(fp,",%g,%g,%g", x_i0[i], x_i1[i], x_i0[i] - x_i1[i]);
        }


    }



}

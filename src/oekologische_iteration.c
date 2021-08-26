#include "functions.h"

/* bifurcation diagram as function of r for two step iteration*/
void exercise1();
/* bifurcation diagram for single step iteration */
void exercise3();
/* compute lyapunov exponent for single step iteration */
void exercise4();

/* main function */
int main(void)
{
	exercise1();
    exercise3();
    exercise4();
	return EXIT_SUCCESS;
}

void exercise1()
{   /*generation of the data for the bifurcation diagram for the two step rekursion*/

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
{   /*generation of the data for the bifurcation diagram for the onestep rekursion*/

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


void exercise4()
{   /*
    Calculation of the Lyapunov Exponent (LE) as a function
    of the bifurcation parameter with the simple and with
    the advanced method. 
    */
    int rs = 10000; // number of rs to simulate dynamics for
    double r = 0.0; // starting value for r
    int ns[] = {10,20,50,1000}; // ns for which the LE should be calculated
    double x0 = 0.5; //staring value for x
    double x1 = x0 + 1e-3; //the other close by starting value
    double step = 5. / rs; //step size for equal spacing of r

    double le_simple = 0; //Lyapunov Exponent with simple method
    double le_advanced = 0; // LE with advanced method

    FILE *fp = fopen("data/lyapunov_exponent_simple.csv", "w");
    FILE *fp2 = fopen("data/lyapunov_exponent_advanced.csv", "w");
    

    /* write file header */
    fprintf(fp, "r,%d,%d,%d,%d", ns[0],ns[1],ns[2],ns[3]);
    fprintf(fp2,"r,%d,%d,%d,%d", ns[0],ns[1],ns[2],ns[3]);
    
    // estimation of LE for every r and different n
    for (int i = 0; i < rs; i++)
    {   
        //simple
        fprintf(fp,"\n%g",r);
        for(int i = 0; i<4; i++){
            le_simple = lyapunov_exponent_simple(x0, x1, ns[i], r);
            fprintf(fp, ",%g", le_simple);

        }
        //advanced
        fprintf(fp2,"\n%g",r);
        for(int i = 0; i<4; i++){
            le_advanced = lyapunov_exponent_advanced(x0, ns[i], r);
            fprintf(fp2, ",%g", le_advanced);

        }
        
        r += step;
    }
    fclose(fp);
    fclose(fp2);

    /* 
    Tracking the differences between the trajektories for closeby starting values
    for some bifurkation parameters 
    this data is later used to better understand the differences between the 
    simple and advanced method for the calculation of the LE
     */
    FILE* fp3 = fopen("data/differences.csv", "w");
    int n = 100;
    double x_start = 0.5;//starting value
    double delta = 0.01;//difference between the starting values
    double x_i0[] = {x_start, x_start, x_start}; // starting value for x
	double x_i1[] = {x_start + delta, x_start+delta, x_start +delta}; // starting value for y
	double rs_i[] = {0.5, 1.2, 1.5};  // value for bifurcation parameter

    //writing meta information to file
    fprintf(fp,"%g,%g,%g,%g,%g", x_start, delta,  rs_i[0],  rs_i[1], rs_i[2]);

    //tracking trajectories and their difference over time
    for(int i = 0; i < n; i++)
    {
        fprintf(fp3, "\n%d", i);
        for (int i = 0; i < 3; i++)
        {
            x_i0[i] = ecologic_map(x_i0[i], x_i0[i], rs_i[i]);
            x_i1[i] = ecologic_map(x_i1[i], x_i1[i], rs_i[i]);

            fprintf(fp3,",%g,%g,%g", x_i0[i], x_i1[i], x_i0[i] - x_i1[i]);
        }
    }
    fclose(fp3);
}


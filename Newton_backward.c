#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 100

double newtonbackwardDifference(const double* x, const double* y, int n, double xi) {
    double backDiff[n][n];
    // Initialize the forward difference table
    for (int i = 0; i < n; i++) {
        backDiff[i][0] = y[i];
    }
    // Calculate the forward difference table
    for(int j = 1; j < n; j++){
        for(int i = n - 1; i >= j; i--){
            backDiff[i][j] = backDiff[i][j - 1]-backDiff[i - 1][j - 1];
        }
    }
    

    double factorial = 1.0; 
    double result = y[n-1];      
    double h = x[1] - x[0];     
    double v = (xi - x[n-1]) / h;
    double term = 1.0;
    for (int i = 1; i < n; i++) {
        term *= (v + (i - 1)) / i;
        result += term * backDiff[n-1][i];
    }

    return result;
}

int main() {
    FILE *fp;
    char filename[100];
    int n;
    double x[MAX_POINTS], y[MAX_POINTS];

    printf("Enter the data file name (e.g., DATA001.dat): ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(fp, "%d", &n);
    n++;
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%lf %lf", &x[i], &y[i]);
    }
    fclose(fp);

    printf("\n%-15s %-15s %-15s\n", "x", "y", "Interpolated ya");
    for (int i = 0; i < n; i++) {
        double ya = newtonbackwardDifference(x, y, n, x[i]);
        printf("%-15.10lf %-15.10lf %-15.10lf\n", x[i], y[i], ya);
    }

    return 0;
}

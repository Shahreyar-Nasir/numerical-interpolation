#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 100

// Function to perform Lagrange interpolation
double lagrange_interpolate(double x[], double y[], int n, double xp) {
    double yp = 0.0;

    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                term *= (xp - x[j]) / (x[i] - x[j]);
            }
        }
        yp += term;
    }

    return yp;
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
    double xi;
    printf("Enter the value to interpolate at: ");
    if (scanf("%lf", &xi) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    double result = lagrange_interpolate(x, y, n, xi);
    printf("Interpolated value at x = %lf is: %lf\n", xi, result);
    
    printf("\n");

    printf("\n%-15s %-15s %-15s\n", "x", "y", "Interpolated ya");
    for (int i = 0; i < n; i++) {
        double ya = lagrange_interpolate(x, y, n, x[i]);
        printf("%-15.10lf %-15.10lf %-15.10lf\n", x[i], y[i], ya);
    };
    return 0;
}

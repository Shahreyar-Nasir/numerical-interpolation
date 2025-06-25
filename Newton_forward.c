#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 100

double newtonForwardDifference(const double* x, const double* y, int n, double xi) {
    double result = y[0];
    double h = x[1] - x[0]; // Assuming equally spaced points
    double u = (xi - x[0]) / h;
    double factorial = 1.0;
    double term = 1.0;
    double forwardDiff[n][n];

    // Initialize the forward difference table
    for (int i = 0; i < n; i++) {
        forwardDiff[i][0] = y[i];
    }

    // Calculate the forward difference table
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            forwardDiff[i][j] = forwardDiff[i + 1][j - 1] - forwardDiff[i][j - 1];
        }
    }

    // Apply Newton's Forward Difference formula
    for (int i = 1; i < n; i++) {
        term *= (u - (i - 1)) / i;
        result += term * forwardDiff[0][i];
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
        double ya = newtonForwardDifference(x, y, n, x[i]);
        printf("%-15.10lf %-15.10lf %-15.10lf\n", x[i], y[i], ya);
    }

    return 0;
}
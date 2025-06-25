#include <stdio.h>
#include <stdlib.h>

// Function to compute backward divided difference table
void backwardDividedDifferenceTable(double x[], double y[], double diffTable[][100], int n) {
    for (int i = 0; i < n; i++) {
        diffTable[i][0] = y[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            diffTable[i][j] = (diffTable[i][j - 1] - diffTable[i - 1][j - 1]) / (x[i] - x[i - j]);
        }
    }
}

// Function to compute interpolation at a value using backward method
double newtonBackwardInterpolation(double x[], double diffTable[][100], int n, double value) {
    double result = diffTable[n - 1][0];
    double term = 1.0;

    for (int i = 1; i < n; i++) {
        term *= (value - x[n - 1 - i]);
        result += term * diffTable[n - 1][i];
    }

    return result;
}

int main() {
    char filename[100];
    printf("Enter the .dat filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);
    n++;
    double x[100], y[100];
    for (int i = 0; i < n; i++) {
        fscanf(file, "%lf %lf", &x[i], &y[i]);
    }
    fclose(file);

    double diffTable[100][100];
    backwardDividedDifferenceTable(x, y, diffTable, n);

    printf("\nResults (x, y, ya):\n");
    for (int i = 0; i < n; i++) {
        double ya = newtonBackwardInterpolation(x, diffTable, n, x[i]);
        printf("%lf\t%lf\t%lf\n", x[i], y[i], ya);
    }

    return 0;
}

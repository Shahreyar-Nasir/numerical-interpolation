#include <stdio.h>
#include <stdlib.h>

// Function to compute divided differences
void dividedDifferenceTable(double x[], double y[], double diffTable[][100], int n) {
    for (int i = 0; i < n; i++) {
        diffTable[i][0] = y[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            diffTable[i][j] = (diffTable[i + 1][j - 1] - diffTable[i][j - 1]) / (x[i + j] - x[i]);
        }
    }
}

// Function to calculate the interpolated value at a given x using forward difference
double newtonForwardInterpolation(double x[], double diffTable[][100], int n, double value) {
    double result = diffTable[0][0];
    double term = 1.0;

    for (int i = 1; i < n; i++) {
        term *= (value - x[i - 1]);
        result += term * diffTable[0][i];
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
    dividedDifferenceTable(x, y, diffTable, n);

    printf("\nResults (x, y, ya):\n");
    for (int i = 0; i < n; i++) {
        double ya = newtonForwardInterpolation(x, diffTable, n, x[i]);
        printf("%lf\t%lf\t%lf\n", x[i], y[i], ya);
    }

    return 0;
}

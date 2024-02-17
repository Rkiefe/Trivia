// R Kiefe, 17 Feb 2024
// Reads an n by m array from a .txt file, with double precision
// and without knowing the array dimensions à priori
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numRows;
    int numCols;
} ArrayDimensions;

double** read(char fileName[], ArrayDimensions *dimensions) {
    FILE *file;
    char line[100];

    double **arr = NULL;
    int numRows = 0;
    int maxRows = 10;

    file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening the file");
        exit(1);
    }
    printf("File opened successfully.\n");

    arr = (double **)malloc(maxRows * sizeof(double *));
    if (arr == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    // Determine the number of columns based on the first line
    fgets(line, sizeof(line), file);
    char *token = strtok(line, ",");
    int numCols = 0;
    while (token != NULL) {
        numCols++;
        token = strtok(NULL, ",");
    }

    rewind(file); // Reset file pointer to the beginning

    while (fgets(line, sizeof(line), file) != NULL) {
        if (numRows >= maxRows) {
            maxRows *= 2;
            arr = (double **)realloc(arr, maxRows * sizeof(double *));
            if (arr == NULL) {
                perror("Memory reallocation failed");
                exit(1);
            }
        }

        arr[numRows] = (double *)malloc(numCols * sizeof(double));
        if (arr[numRows] == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }

        token = strtok(line, ",");
        int col = 0;
        while (token != NULL) {
            arr[numRows][col] = atof(token);
            col++;
            token = strtok(NULL, ",");
        }

        numRows++;
    }

    dimensions->numRows = numRows;
    dimensions->numCols = numCols;

    fclose(file);

    return arr;
}

int main() {
    char fileName[] = "file.txt";
    ArrayDimensions dimensions;

    double **arr = read(fileName, &dimensions);

    int rows = dimensions.numRows;
    int cols = dimensions.numCols;

    printf("Number of rows: %d\n", rows);
    printf("Number of columns: %d\n", cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%lf ", arr[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

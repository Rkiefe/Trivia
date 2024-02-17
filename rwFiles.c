// R Kiefe, 17 Feb 2024
// Read a .txt file and get a n by 2 array of doubles

#include <stdio.h>  // Needed for input output
#include <stdlib.h> // Needed for memory allocation

typedef struct {
    int numRows;
    int numCols;
} ArrayDimensions;

double** read(char fileName[], ArrayDimensions *dimensions) {
    FILE *file;
    char line[100];

    double **arr = NULL; // Pointer to store dynamic 2D array
    int numRows = 0; // Count of rows
    int numCols = 2; // Assuming each line contains 2 numbers
    int maxRows = 10; // Initial capacity of rows
    int i, j;

    // Open the file in read mode
    file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening the file");
        exit(1);
    }

    // Allocate memory for the array of pointers (rows)
    arr = (double **)malloc(maxRows * sizeof(double *));
    if (arr == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    // Read numbers from the file
    while (fgets(line, sizeof(line), file) != NULL) {
        // Allocate memory for each row
        arr[numRows] = (double *)malloc(numCols * sizeof(double));
        if (arr[numRows] == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }

        // Use sscanf to extract the numbers from the line
        sscanf(line, "%lf,%lf", &arr[numRows][0], &arr[numRows][1]);
        numRows++; // Increment the row count

        // Resize the array if needed
        if (numRows >= maxRows) {
            maxRows *= 2; // Double the capacity
            arr = (double **)realloc(arr, maxRows * sizeof(double *));
            if (arr == NULL) {
                perror("Memory reallocation failed");
                exit(1);
            }
        }
    }

    // Set the dimensions
    dimensions->numRows = numRows;
    dimensions->numCols = numCols;

    // Close the file
    fclose(file);

    return arr;
}

void main() {
    char fileName[] = "file.txt";
    ArrayDimensions dimensions;

    double **arr = read(fileName, &dimensions);
    int rows = dimensions.numRows;
    int cols = dimensions.numCols;

    printf("Number of rows: %d\n", rows);
    printf("Number of columns: %d\n", cols);

    // Print the array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%lf ", arr[i][j]);
        }
        printf("\n");
    }

    // Free dynamically allocated memory
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);

}

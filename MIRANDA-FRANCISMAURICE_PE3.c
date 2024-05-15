/*
Francis Maurice B. Miranda || BSCS 1B
Programming Exercise 3
    A program that asks the user to input the dimension of the matrix, followed by values to serve as the elements for the matrix. The program then gets
    the transpose of the inputted matrix and outputs it. The sum of each row and column of the original and transposed matrix, respectively, is then 
    calculated and outputted in table form. Afterwards, the overall sum of the matrix is then calculated and outputted in the table.
*/

#include <stdio.h>
#include <math.h>

//function for getting the sum of all the values in the matrix
int totalSum(int columns, int sumColumns[]){
    int totalsum; //variable for the total sum
    for(int i = 0; i < columns; i++){ //for-loop that goes through the sum of each column
        totalsum += sumColumns[i]; //adds each value of the sum of each column to the total sum
    }
    printf("| %3d", totalsum); //outputs the total sum
}

//function for getting the sum of each row and column of the original matrix
int sumRow_Column(int rows, int columns, int matrix[][columns], int sumRows[], int sumColumns[]){
    printf("\nSum of each row and column of the original matrix:\n");
    printf("\t\t");
    for(int i = 0; i < columns; i++){ //for-loop for formatting
        printf("    ");
    }
    //getting the sum of each row
    printf("Sum-of-Row\n");
    for(int i = 0; i < rows; i++){ //nested for-loop that goes through each row and column
        printf("\t\t");
        sumRows[i] = 0; //sets sumRows[i] to 0
        for(int j = 0; j < columns; j++){
            printf("%3d ", matrix[i][j]); //outputs the table of the original matrix
            sumRows[i] += matrix[i][j]; //adds up the values for each row
        }
        printf("| %3d\n", sumRows[i]); //outputs the sum of each row
    }
    //getting the sum of each column
    printf("\t\t");
    for(int i = 0; i < columns; i++){ //for-loop for table formatting
        printf("-----");
    }
    printf("\nSum-of-Column   ");
    for(int i = 0; i < columns; i++){ //nested for-loop that goes through each column and row
        sumColumns[i] = 0; //set sumColumns[i] to 0
        for(int j = 0; j < rows; j++){
            sumColumns[i] += matrix[j][i]; //adds up the values for each column
        }
        printf("%3d ", sumColumns[i]); //outputs the sum of each column
    }
    
}

//function for transposing the matrix
int transpose(int rows, int columns, int matrix[][columns]){
    printf("\nTranspose of the matrix: \n");
    for(int i = 0; i < columns; i++){ //nested for-loop that goes through each column and row
        for(int j = 0; j < rows; j++){
            printf("%3d ", matrix[j][i]); //outputs the each element of the original matrix to its transposed arrangement
        }
        printf("\n");
    }
}

//function for getting the sum of each row and column of the transposed matrix
int transpose_sumRow_Column(int rows, int columns, int matrix[][columns], int sumRows[], int sumColumns[]){
    printf("\nSum of each row and column of the transpose matrix:\n"); 
    printf("\t\t");
    //getting the sum of each row
    for(int i = 0; i < rows; i++){ //for-loop for formatting
        printf("    ");
    }
    printf("Sum-of-Row\n");
    
    for(int i = 0; i < columns; i++){ //nested for-loop that goes through each column and row
        printf("\t\t");
        for(int j = 0; j < rows; j++){
            printf("%3d ", matrix[j][i]); //outputs the table for the transposed matrix
        }
        printf("| %3d\n", sumColumns[i]); //outputs the sum of each row (by outputting the corresponding value in sumColumns[i])
    }
    //getting the sum of each column
    printf("\t\t");
    for(int i = 0; i < columns; i++){ //for-loop for formatting
        printf("----");
    }
    printf("\nSum-of-Column   ");
    for(int i = 0; i < rows; i++){
        printf("%3d ", sumRows[i]); //outputs the sum of each column (by outputting the corresponding value in sumRow[i])
    }
}

//main function
int main(){
    int rows, columns; //variables for rows and columns
    printf("Input the dimension of the matrix(row column): "); //prompt for the dimension of the matrix
    scanf("%d%d", &rows, &columns);
    int matrix[rows][columns], sumRows[rows], sumColumns[columns]; //declares the matrix and arrays for the sums of rows and columns
    printf("Please enter the elements of the %dx%d matrix: \n", rows, columns); //prompt for the elements of the matrix
    for(int i = 0; i < rows; i++){ //nested for-loop to take the inputs
        for(int j = 0; j < columns; j++){
            scanf("%d", &matrix[i][j]);
        }
    }

    //function calls
    transpose(rows, columns, matrix); //function calls transpose function
    sumRow_Column(rows, columns, matrix, sumRows, sumColumns); //function calls sumRow_Column function (outputs sum each of row and column of the original matrix)
    totalSum(columns, sumColumns); //function calls totalSum function
    printf("\n\n");
    transpose_sumRow_Column(rows, columns, matrix, sumRows, sumColumns); //function calls transpose_sumRow_Column function (outputs sum each of row and column of the transposed matrix)
    totalSum(columns, sumColumns); //function calls totalSum function
    
   return 0;
}

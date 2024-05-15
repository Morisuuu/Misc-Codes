/*
Francis Maurice B. Miranda || BSCS 1B
Programming Exercise 5
    A program that outputs the variable name, type, address and value of each preset variable and its corresponding value in table form. A function 
    will then get the inputs for the new value of the preset variables. The program will then output the same table with the new inputted values.
*/
#include <stdio.h>  

//function that gets the new values
void new_value(float *fPtr, int *iPtr, char *cPtr){
    //prompts for the input of the new values
    printf("Input a new value for desimal: ");
    scanf("%f", fPtr); //replaces the value for float
    printf("Input a new value for numero: ");
    scanf("%d", iPtr); //replaces the value for int
    printf("Input a new value for letra: ");
    scanf(" %c", cPtr); //replaces the value for char
} 

//main function
int main() {
    //declaring and initializing the set variables (with custom variable names and values)
    float desimal = 69.96;
    int numero = 56;
    char letra = 'B';
    //declaring and initializing the pointers
    float *fPtr = &desimal; //assigns the address of the float
    int *iPtr = &numero; //assigns the address of the int
    char *cPtr = &letra; //assigns the address of the char

    //outputs the variable name, type, address and value of each declared variable in table form
    printf("Variable_name   Type       Address                Value\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("desimal         float      %p       %.2f\n", fPtr, desimal);
    printf("numero          int        %p       %d\n", iPtr, numero);
    printf("letra           char       %p       %c\n", cPtr, letra);
    printf("fPtr            float*     %p       %p\n", &fPtr, fPtr);
    printf("iPtr            int*       %p       %p\n", &iPtr, iPtr);
    printf("cPtr            char*      %p       %p\n", &cPtr, cPtr);

    printf("\n\n");
    new_value(fPtr, iPtr, cPtr); //function calls new_value
    printf("\n");

    //outputs the table with the new set of inputted values
    printf("Variable_name   Type       Address                New_Value\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("desimal         float      %p       %.2f\n", fPtr, desimal);
    printf("numero          int        %p       %d\n", iPtr, numero);
    printf("letra           char       %p       %c\n", cPtr, letra);
    printf("fPtr            float*     %p       %p\n", &fPtr, fPtr);
    printf("iPtr            int*       %p       %p\n", &iPtr, iPtr);
    printf("cPtr            char*      %p       %p\n", &cPtr, cPtr);

    return 0;
}



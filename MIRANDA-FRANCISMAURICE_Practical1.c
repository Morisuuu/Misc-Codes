
/*Francis Maurice B. Miranda || BSCS 1B*/

#include <stdio.h>
#include <math.h>
int main() { 

    int a,b,c,d,e; //variables for the inputted integers
    int a2,b2,c2,d2,e2, sum_sq;

    printf("\n\"CS102 Practical Exam 1\"\n"); //prints the message with ""
    printf("\nInput the five integers seperated by a space: \n");
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e); //takes the input for each integer

//squaring the inputted integers
    a2 = a*a; b2 = b*b; c2 = c*c; d2 = d*d; e2 = e*e;
    printf("\nSquares of the numbers: %d, %d, %d, %d, %d\n", a2, b2, c2, d2, e2); //outputs the squared integers

//adds up the sum of the squared integers
    sum_sq = a2+b2+c2+d2+e2;
    printf("Sum of the squares: %d\n", sum_sq); //outputs the sum of the squared integers

//gets the average of the sum
    printf("Average of the squares: %.2f\n", sum_sq/5.00); //outputs the average of the sum

//gets the square root of the sum
    printf("Square root of the squares' sum: %.4f\n", sqrt(sum_sq)); //outputs the square root of the sum

    return 0;
    
}
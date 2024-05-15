/*
Francis Maurice B. Miranda || BSCS 1B
Practical Exam 2
*/

#include <stdio.h>
#include <math.h>

//function that gets the sum of the numbers between X and Y
int f1(int X, int Y){
    int sum = 0, count;
    if (X<Y){ 
        count = X;
        while (count <= Y){ //pretest loop
            sum = sum + count; //adds up the numbers
            count++;//increments count
        }
        return sum;
    }
    else{ 
        count = Y;
        do
        {
            sum = sum + count; //adds up the numbers
            count++; //increments count
        } while (count <= X); //post-test loop
        return sum;  
    }
}

//function that gets the sum of the digits using recursion
int f2(int num){
    if(num >= 10){
        return (num % 10 + f2(num/10)); //adds up the remainder of the number and moves on to the next digit
    }
    else if (num < 10){
        return num; //returns the number itself when number is less than 10
    }
}

//main function
int main() { 
    unsigned int X,Y;
    char choice;
    //gets the input of the two positive integers
    printf("Input two positive integers: ");
    scanf("%d %d", &X, &Y);

    printf("\nWhat would you like to do?\n");
    printf(" [A/a] Get sum of all integers between %d and %d.\n", X, Y);
    printf(" [B/b] Find sum of the digits of %d and %d.\n", X, Y);

    //gets input of choice
    printf("Enter the letter of choice: ");
    scanf(" %c", &choice);

    //switch case for choice
    switch (choice){
        case 'A': case 'a':
            printf("\nThe sum of the integers from %d up to %d is %d.\n", X, Y, f1(X,Y)); //outputs sum of integers between X and Y
            break;
        case 'B': case 'b':
            printf("\nThe sum of the digits of %d and %d is %d.\n", X, Y, f2(X) + f2(Y)); //outputs sum of digits of X and Y and adds them
            break;
        default:
            printf("\nNot a valid letter of choice!\n"); //prints if other character than a/A or b/B is inputted
            break;
    }

    return 0;
}

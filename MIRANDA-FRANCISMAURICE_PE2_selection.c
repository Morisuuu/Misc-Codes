/*
Francis Maurice B. Miranda || BSCS 1B
Programming Exercise 2 - Selection Sort MODIFIED
    A modified version of the selection sort program given in Lecture 1.a but instead it sorts the array in descending order. The program will ask the user to
    input the size of the array which would then be followed by the elements of the array (separated with spaces). The program will then use the selection sort
    algorithm to sort the elements of the array from the highest number to the lowest. This sorted list is then outputted.
*/

#include <stdio.h>
#include <math.h>
int main() { 
    int a[100], n, i, j, position, swap;

    printf("Enter the size of array: "); //prompt for array size
    scanf("%d", &n);
    printf("Enter the array elements: ", n); //prompt for the elements

    //for loop to take the inputs
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    //selection sort algorithm
    for(i = 0; i < n-1; i++){
        position=i; //sets the index of the element to be checked

        //loop that finds the smallest number
        for(j = i+1; j < n; j++){
            if(a[position] < a[j])
                position=j;
        }
        //if condition that swaps places with a[i] if a smaller value is found
        if(position != i) {
            swap=a[i];
            a[i]=a[position];
            a[position]=swap;
        }
    }
    //outputs the sorted list
    printf("Array after sorting: ");
    for(i = 0; i < n; i++)
        printf("%d ", a[i]);

  return 0;
}

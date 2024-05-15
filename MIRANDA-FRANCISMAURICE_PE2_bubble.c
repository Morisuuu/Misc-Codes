/*
Francis Maurice B. Miranda || BSCS 1B
Programming Exercise 2 - Bubble Sort MODIFIED
    A modified version of the bubble sort program given in Lecture 1.a but instead it sorts the array in descending order. The program will ask the user to
    input the size of the array which would then be followed by the elements of the array (separated with spaces). The program will then use the bubble sort
    algorithm to sort the elements of the array from the highest number to the lowest. This sorted list is then outputted.
*/

#include <stdio.h>
#include <math.h>
int main() { 
    int a[50],n,i,j,temp;
    printf("Enter the size of array: "); //prompt for array size
    scanf("%d",&n);
    printf("Enter the array elements: "); //prompt for the elements

    //for loop that takes the inputs
    for(i = 0; i < n; i++)
        scanf("%d",&a[i]);

    //bubble sort algorithm
    for(i = 1; i < n; i++){
        for(j = 0; j < (n-i); j++){
            if(a[j]<a[j+1]){ //compares the adjacent elements (if first element is less than the next)
                temp=a[j];
                a[j]=a[j+1]; //swaps the elements if so
                a[j+1]=temp;
            }
        }
    }

    //outputs the sorted list
    printf("\nArray after sorting: ");
    for(i=0;i<n;++i)
        printf("%d ",a[i]);

  return 0;
}

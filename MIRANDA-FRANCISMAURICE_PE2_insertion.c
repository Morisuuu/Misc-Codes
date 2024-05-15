/*
Francis Maurice B. Miranda || BSCS 1B
Programming Exercise 2 - Insertion Sort MODIFIED
    A modified version of the insertion sort program given in Lecture 1.a but instead it sorts the array in descending order. The program will ask the user to
    input the size of the array which would then be followed by the elements of the array (separated with spaces). The program will then use the insertion sort
    algorithm to sort the elements of the array from the highest number to the lowest. This sorted list is then outputted.
*/

#include <stdio.h>
#include <math.h>
int main() { 
    int arr[100], n, i, j, key;

    printf("Enter the size of array: "); //prompt for array size
    scanf("%d", &n);
    printf("Enter the array elements: ", n); //prompt for the elements

    //for loop that takes the inputs
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    //insertion sort algorithm
    for (i = 1; i < n; i++){
        key = arr[i]; //sets the element to be swapped
        j = i - 1;

        //loop that compares each element on the array until an element greater than the key value is found
        while (j >= 0 && arr[j] < key){ //checks if the checked value is less than the key value
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key; //sets the key value on the index after the element greater than it
    }

    //outputs the sorted list
    printf("Array after sorting: ");
    for(i = 0; i < n; i++)
        printf("%d ", arr[i]);

  return 0;
}

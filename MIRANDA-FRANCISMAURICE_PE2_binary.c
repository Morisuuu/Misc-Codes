/*
Francis Maurice B. Miranda || BSCS 1B
Programming Exercise 2 - Binary Search MODIFIED
    A modified version of the binary search program given in Lecture 1.a but instead it searches the array in descending order. The program will ask 
    the user to input the size of the array which would then be followed by the elements of the array in descending order (separated with spaces). 
    The program then asks the user to input the KEY element to be searched. The program will then use the binary search algorithm to find the given 
    KEY element but in descending order. The position of the KEY is then outputted when found.
*/

#include <stdio.h>
#include <math.h>

int main() { 
    int arr[50], i, n, key, flag=0, first, last, mid;

    printf("Enter size of array: "); //prompt for array size
    scanf("%d", &n);
    printf("\nEnter array element(descending order): \n"); //prompt for the elements

    for(i = 0; i < n; i++){ //for loop for the input of the elements
        scanf("%d",&arr[i]);
    }

    printf("\nEnter the element to search: "); //prompt for the element to be searched
    scanf("%d",&key);

    //set index values for the first and last element of the array
    first=0;
    last=n-1;

    //while loop that will find the key value
    while(first <= last){
        mid=(first+last)/2; //gets the middle index of the array
        printf("%d", mid);
        if(key == arr[mid]){ //checks if the key value and the middle element of the array are the same
            flag=1; //sets flag to 1 when found
            break;
        }
        else
            if(key > arr[mid]) //checks if the key value is in the right or left half
                last=mid-1; //moves to the left
            else
                first=mid+1; //move to the right

        //loop repeats until key value is found or no more elements are left to be checked
        }

    if(flag == 1) //checks the value of flag
        printf("\nElement found at position %d.",mid+1); //outputs the position of the key value when found
    else
        printf("\nElement not found."); //outputs if key value is not found

  return 0;
}

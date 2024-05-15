/*
Francis Maurice B. Miranda || BSCS 1B
Programming Exercise 1
    The program asks the user to input 10 integer values using spaces and will store them in an array called LIST. A KEY value is then asked which the program will then
    output all numbers in the list that are LESS THAN and GREATER THAN the key value inputted. The program then checks if the key value is present in the list. If so,
    the INDEX of the value is outputted, otherwise, it outputs that it is not found.
*/

#include <stdio.h>
#include <math.h>

//function for getting the values greater than the key value
int greaterList(int list[], int key){
    for(int i = 0; i < 10; i++){ //loop that goes through the indexes of the array
        if(key<list[i]){ //checks if the element in the given index is greater than the key value
            printf("%d ", list[i]); //outputs the element
        }
    }
}

//function for getting the values less than the key value
int lessList(int list[], int key){
    for(int i = 0; i < 10; i++){ //loop that goes through the indexes of the array
        if(key>list[i]){ //checks if the element in the given index is less than the key value
            printf("%d ", list[i]); //outputs the element
        }
    }
}

//function for finding the position of the key value in the array(if applicable)
int findPos(int list[], int key){
    for(int i = 0; i < 10; i++){ //loop that goes through the indexes of the array
        if(key==list[i]){ //checks if the element in the given index is the same as the key value
            return i; //returns the index if found
        }
    }
    return -1; //returns -1 if not found (-1 because the starting index of an array is 0)
}
int main() { 
    int list[10], key;

    printf("Input the 10 integers each separated by a space: \n\t"); //prompt user to input 10 integers

    //for loop to take the inputs
    for(int i = 0; i < 10; i++) {
        scanf("%d", &list[i]);
    }

    printf("Please enter the key value: "); //prompt user for key value
    scanf("%d", &key);

    //shows values less than the key value
    printf("\nValues in the array that are less than %d: \n\t", key);
    lessList(list, key);//function calls lessList

    //shows values greater than the key value
    printf("\nValues in the array that are greater than %d: \n\t", key);
    greaterList(list, key); //function calls greaterList

    //finds the position of the key value in the array
    if(findPos(list, key) == -1){ //if condition that function calls findPos and checks the returned value
        printf("\nThe key=%d was not found in the array.", key); //outputs if key value is not found in the array
    }
    else
        printf("\nThe key=%d was found at index %d.", key, findPos(list, key)); //outputs the index of the key value if present

  return 0;
}

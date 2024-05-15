/*
Francis Maurice B. Miranda || BSCS 1B
Programming Exercise 6
    A program that will ask the user to input 10 strings (only letters) in succession. The inputted strings will then be formatted to lowercase
    and then assigns each of its address to an array pointer. A function will then get this pointer as parameter and sort the inputted strings
    in lexicographic order. If there are strings with the same length, they are alphabetically arranged. After this, the string name, address of
    each inputted string and its length are then outputted in table form.
*/

#include <stdio.h>  
#include <string.h>
#define MAX 100

//function for sorting the inputted strings in lexicographic order
void sortStrings(char *stringsPtr[]){
    int position;
	char *swap = NULL;
	
    //selection sort
	for(int i=0; i<10; i++){ //for-loop that goes through each element of the pointer string array
		position=i; //sets position to i
		for(int j=i+1; j<10; j++){
			if(strlen(*(stringsPtr+position)) > strlen(*(stringsPtr+j))){ //finds the string with the longest length
                position=j; //sets the position with the longest length
            } 
			else if(strlen(*(stringsPtr+position)) == strlen(*(stringsPtr+j))){ //checks if the strings have equal lengths
				if (strcmp(*(stringsPtr+position), *(stringsPtr+j)) > 0){ //checks which goes first alphabetically
                    position=j; //sets the position of the string that goes first alphabetically
                } 
			}
		}
        //swapping the positions
		if(position!=i){ //checks if position is not equal to i
			swap = *(stringsPtr+i);
			*(stringsPtr+i) = *(stringsPtr+position); //swaps the position of the strings
			*(stringsPtr+position) = swap;
		}
	}
}

//function for formatting the string to lowercase
void lowercase(char strings[]){
    for(int i = 0; i < strlen(strings); i++){ //for-loop that goes through the characters of the string
        if(*(strings + i) >= 'A' && *(strings + i) <= 'Z'){ //checks if the characters are in uppercase
            *(strings+i) += 32; //changes them to lowercase by changing the ASCII value
        }
    }
}

//main function
int main() {
    char strings[10][MAX]; //declaration of array of strings
    char *stringsPtr[10]; //pointer array for strings
    for(int i = 0;  i < 10; i++){ //for-loop that takes the inputs
        printf("Input string%d: ", i+1); //prompt for input
        scanf("%s", *(strings+i));
        lowercase(*(strings+i)); //function calls lowercase
        *(stringsPtr+i) = *(strings+i); //assigns each value of the strings to pointer stringsPtr
    }

    sortStrings(stringsPtr); //function calls sortStrings with the string array pointer as argument

    printf("\n\nLEXICOGRAPHIC ORDERING:\n\n"); //text for the ordering
	printf("STRING\t\tADDRESS\t\t\tLENGTH\n\n"); //table headers
	
	for(int i = 0; i < 10; i++){ //for-loop for the output (in formatted form)
		printf("%-15s\t%p\t%d\n",*(stringsPtr+i), *(stringsPtr+i), strlen(*(stringsPtr+i))); //outputs the string name, address, and string length in lexicographic order
	}

    return 0;
}




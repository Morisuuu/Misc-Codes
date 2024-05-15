/*
Francis Maurice B. Miranda || BSCS 1B
Practical Examination
    A program that will take a string as input and assign a pointer to it. A 3x26 matrix is also initalized with the ASCII values of the alphabet,
    upper and lower case, assigned to the first two rows respectively and a third row initialized to zero. A funtion will then take the pointer
    of the inputted string and the initialized matrix as parameter to get the frequency of each letter in the given string. The corresponding 
    frequency of each letter are assigned in the third row of the matrix. Afterwards, the length of the string is outputted which is then 
    followed by the frequency of the letters in the string, outputted in alphabetical order in table form.
*/
#include <stdio.h>  
#include <string.h>
#define MAX 200

//function to get the frequency of each letter in the inputted string
void get_Frequency(int freq[][26], char *sPtr){
    int length = strlen(sPtr); //gets the length of the string
    int position = 0;
    for(int i = 0; i < length; i++){ //for-loop that goes through the characters of the string
        if(*(sPtr+i) >= 'a' && *(sPtr+i) <= 'z'){ //checks if the character is within the range of lowercase letters
            position = *(sPtr+i)-'a'; //gets the corresponding position of that letter (if present)
            freq[2][position]+=1; //adds one to the count in the corresponding position in the third row
        }
        else if(*(sPtr+i) >= 'A' && *(sPtr+i) <= 'Z'){ //checks if the character is within the range of uppercase letters
            position = *(sPtr+i)-'A'; //gets the corresponding position of that letter (if present)
            freq[2][position]+=1; //adds one to the count in the corresponding position in the third row
        }
    }
}

//main function
int main() {
    char string[MAX]; //variable for the inputted string
    char *sPtr; //pointer for the string
    int freq[3][26] = {{65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81,82, 83, 84, 85, 86, 87, 88, 89, 90},
			           {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122},
	                    {0}	}; //initialized matrix with ASCII values

    printf("Please input a string(at most 200 characters):\n"); //prompt for the input
    printf("\t");
    scanf("%s", string);
    
    sPtr = &string; //assigns the address of the string to the pointer

    get_Frequency(freq, sPtr); //function calls get_Frequency

    printf("\nString length:%d\n", strlen(string)); //outputs the length of the string

    printf("\nFrequency of letters in the string:\n");
    for(int i = 0; i < 26; i++){ //for-loop that goes through the matrix
		if(freq[2][i] > 0){ //checks the third row of the matrix for the present letters in the string
            printf("      %c/%c     %d\n", freq[0][i], freq[1][i], freq[2][i]); //outputs the frequency of the letters
        }
	}
    return 0;
}





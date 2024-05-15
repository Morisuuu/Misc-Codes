/*
Francis Maurice B. Miranda || BSCS 1B
Programming Exercise 4
    A program that continuously asks the user to input a singular noun until EOF. The program would then get the plural form of the inputted noun using 
    these rules:
        - If noun ends in -s, -sh, -ch, -x, or -z, add “es”.
        - If noun ends in -y and the letter before the ”y” is a consonant, remove the “y” and add “ies”.
        - If noun ends in -y and the letter before the ”y” is a vowel, simply add an “s” to make it plural.
        - In all other cases, just add “s”.
    This would be implemented using a function with string as parameter. The plural form of the inputted noun is then outputted through the main function. 
    The program will end when EOF (CTRL-Z or CTRL-D) is inputted.
*/

#include <stdio.h>  
#include <string.h>
#define maxlength 100 //macrodefinition for maxlength

//function to get the plural form of the inputted noun
void plural(char noun[]){
    int length = strlen(noun); //gets the length of the noun and assigns it to a variable

    //nested if condition that checks the last or second to the last letter of the noun
    if(noun[length-1] == 's' || noun[length-2] == 'c' && noun[length-1] == 'h'|| 
    noun[length-2] == 's' && noun[length-1] == 'h'|| noun[length-1] == 'x' || noun[length-1] == 'z'){ //checks if the noun ends in -s, -sh, -ch, -x, or -z
        strcat(noun, "es"); //adds "es" if any of the conditions are met
    }
    else if(noun[length-1] == 'y'){ //checks if last letter is 'y'
        if(noun[length-2] == 'a' || noun[length-2] == 'e' || noun[length-2] == 'i' ||
        noun[length-2] == 'o' || noun[length-2] == 'u'){ //checks if the letter before 'y' is a vowel
            strcat(noun, "s"); //adds "s" if any of the conditions are met
        }
        else{ //case that 'y' is followed by a consonant
            noun[length-1] = '\0'; //deletes the last letter
            strcat(noun, "ies"); //replaces it with "ies"
        }
    }
    else{
        strcat(noun, "s"); //adds "s" if no other conditions are met
    }
}

//main function
int main() {
    char noun[maxlength]; //variable to store the inputted noun
    printf("Input a singular noun: "); //prompt for the input for the singular noun
    while(scanf("%s", noun) != EOF){ //loop that continuously gets the input until EOF is inputted
        plural(noun); //function calls plural
        printf("Plural form: %s", noun); //outputs the plural form of the inputted noun
        printf("\n\nInput a singular noun: "); //repeats the prompt for the next input
    }
    printf("End of program."); //outputs when EOF is inputted

    return 0;
}
/*
Francis Maurice B. Miranda || BSCS 1B
Programming Exercise 8
    A program that will open and read a file named "student.txt". The first line is then read which contains the integer value N for 
    the total number of students. An array of structs will then store the data of each student. This includes the name, student number,
    age and gender. The program will then group these students according to their gender and sort them alphabetically. This is then
    outputted in table form, listing the name, the student number and the age of each student, seperated by gender and is listed
    alphabetically. The outputted data and table is then written on the output file, "sorted.txt".
*/

#include <stdio.h> 
#include <string.h>
#define MAX 200 //macrodefinition for MAX

//creating a structure for the student records
struct studentrecords{
    char name[MAX];
    int student_number;
    int age;
    char gender;
}records[MAX], male[MAX], female[MAX]; //declaration of struct arrays

//function for grouping and sorting the records of the students
void group_sort(FILE *input, FILE *output, struct studentrecords records[], int N){
    int x = 0, y = 0; //stores the total number of elements in the male and female arrays respectively (also works as a counter variables)
    for(int i = 0; i < N; i++){ //for-loop to read the lines of the file
        fscanf(input, "%s %d %d %c", records[i].name, &records[i].student_number, &records[i].age, &records[i].gender); //stores the lines in the files in respective struct members
        if(records[i].gender == 'M'){ //checks if the gender is 'M' or male
            strcpy(male[x].name, records[i].name);  //stores the data in the respective member of male
            male[x].student_number = records[i].student_number; //stores the data in the respective member of male
            male[x].age = records[i].age; //stores the data in the respective member of male
            male[x].gender = records[i].gender; //stores the data in the respective member of male
            x++; //adds one to x (control variable for male array)
        }
        else if(records[i].gender == 'F'){ //checks if the gender is 'F' or female
            strcpy(female[y].name, records[i].name); //stores the data in the respective member of female
            female[y].student_number = records[i].student_number; //stores the data in the respective member of female
            female[y].age = records[i].age; //stores the data in the respective member of female
            female[y].gender = records[i].gender; //stores the data in the respective member of female
            y++; //adds one to y (control variable for female array)
        }
    }
    fclose(input); //closes the input file ("students.txt")

    struct studentrecords temp; //creates a temp struct variable for swapping

    //bubble sort algorithm for sorting the names of the male array alphabetically
    for(int i = 0; i < x; i++){
        for(int j = i + 1; j < x; j++){
            if(strcmp(male[i].name, male[j].name) > 0){ //compares the name in the current position and in the next
                temp = male[i];
                male[i] = male[j]; //swaps them
                male[j] = temp;
            }
        }
    }

    //bubble sort algorithm for sorting the names of the female array alphabetically
    for(int i = 0; i < y; i++){
        for(int j = i + 1; j < y; j++){
            if(strcmp(female[i].name, female[j].name) > 0){ //compares the name in the current position and in the next
                temp = female[i];
                female[i] = female[j]; //swaps them
                female[j] = temp;
            }
        }
    }

    //outputs the table
    printf("NAME\t\t#\tAGE\n");
    printf("----------------------------\n");
    printf("MALE:\n");
    for(int i = 0; i < x; i++){ //for-loop to output the male data
        printf("%-8s\t%.2d\t%.2d\n", male[i].name, male[i].student_number, male[i].age); //outputs the name, student number and age of the male students alphabetically
    }
    printf("\nFEMALE:\n");
    for(int i = 0; i < y; i++){ //for-loop to output the female data
        printf("%-8s\t%.2d\t%.2d\n", female[i].name, female[i].student_number, female[i].age); //outputs the name, student number and age of the female students alphabetically
    }

    //writes on sorted.txt the outputted table and data
    fprintf(output,"NAME\t\t#\tAGE\n");
    fprintf(output, "----------------------------\n");
    fprintf(output, "MALE:\n");
    for(int i = 0; i < x; i++){
        fprintf(output, "%-8s\t%.2d\t%.2d\n", male[i].name, male[i].student_number, male[i].age);
    }
    fprintf(output, "\nFEMALE:\n");
    for(int i = 0; i < y; i++){
        fprintf(output, "%-8s\t%.2d\t%.2d\n", female[i].name, female[i].student_number, female[i].age);
    }

    fclose(output); //closes the output file ("sorted.txt")
}

//main function
int main(){
    FILE *input = NULL; //declares a file handler for students.txt
    FILE *output = NULL; //declares a file handler for sorted.txt
    int N = 0; //variable to store the number of students
    input = fopen("students.txt", "r"); //opens students.txt as read
    output = fopen("sorted.txt", "w"); //opens sorted.txt as write

    if(input == NULL){ //checks if students.txt exists
        printf("File \"students.txt\" does not exist."); //outputs if students.txt doesn't exist
    }
    else{ //runs if the file exists
        char total[MAX]; //stores the first line of the file
        fgets(total, 100, input); //reads the first line of the file and stores it in total

        for(int i = 0; i < strlen(total)-1; i++){ //for-loop that converts total(string) to an int
            N = N * 10 + (total[i] - 48); //converts total to int (by changing the ASCII value) and assigns it to N
        }
        group_sort(input, output, records, N); //function calls group_sort
    }
    return 0;   
}
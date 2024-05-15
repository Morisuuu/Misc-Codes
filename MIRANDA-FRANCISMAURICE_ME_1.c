/*
    Submitted by: Francis Maurice B. Miranda || BSCS-2B

    CS104 DSA - MACHINE EXERCISE 1

        A Linked List Sandbox in which the users can freely play around with linked lists using a set of options. Values can be
        appended from the beginning and end of the list. Some of the features include reversing the order of the linked list, sorting
        the list in ascending order and removing duplicate values.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//initializing the linked list node using struct
struct node{
    int data;
    struct node *next;
};

struct node *head; //declaring the head of the linked list

//function declarations
void insert_start();
void insert_last();
void print_list();
void reverse();
void ascending();
void remove_duplicate();

//main function
void main(){
    int opt = 0; //variable to take inputs
    system("cls");
    printf("\t Welcome to the Linked List Sandbox!\n");
    printf("\n\n\t Press enter to proceed...");
    getch();
    //the main menu of the program (utilizes "goto" to redirect the program to the main menu)
    menu:
        //outputs the options/menu
        system("cls");
        printf("\t***********************\n");
        printf("\t* Linked List Sandbox *\n");
        printf("\t***********************\n\n");
        printf("\t 1. Add value at the start\n");
        printf("\t 2. Add value at the end\n");
        printf("\t 3. Reverse the order of the list\n");
        printf("\t 4. Sort in ascending order\n");
        printf("\t 5. Remove duplicate values\n");
        printf("\t 6. Print linked list\n");
        printf("\t 7. Exit\n\n");

        printf("\t Please enter the number of your corresponding choice: ");
        scanf("%d", &opt);

        //function calls specific functions based on the corresponding option the user inputted
        switch(opt){
            case 1: system("cls"); insert_start(); goto menu;
            case 2: system("cls"); insert_last(); goto menu;
            case 3: system("cls"); reverse(); goto menu;
            case 4: system("cls"); ascending(); goto menu;
            case 5: system("cls"); remove_duplicate(); goto menu;
            case 6: system("cls"); print_list(); goto menu;
            case 7: printf("\t Thank you for using!"); break; //exits the program
            default: system("cls"); printf("\n\tInvalid choice.\n"); printf("\n\tPress enter to continue."); getch(); goto menu;
        }
}

//function for inserting values from the start of the list
void insert_start(){
    struct node *ptr = (struct node*)malloc(sizeof(struct node)); //creates a node
    int item;
	
    //checks for errors
    if(ptr == NULL){  
        printf("\n\tError.\n");  
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{  //if there are no errors proceed here
        printf("\n\tInput value: "); 
        scanf("%d", &item); //gets for user input
        ptr->data = item;  //assigns input to the created node
        ptr->next = head;  
        head = ptr;  //appoints node to the start of the list
        printf("\n\tNode successfully inserted.\n");
        printf("\n\tPress enter to continue.");
        getch();
    }     
}

//function for inserting values at the end of the list
void insert_last(){
    struct node *ptr = (struct node*)malloc(sizeof(struct node)); //creates a node
    struct node *temp;
    int item;
    
    //checks for errors
	if(ptr == NULL){  
        printf("\n\tError.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{ //proceed here otherwise
        printf("\n\tInput value: ");  
        scanf("%d", &item);  //gets user input
        ptr->data = item;  //assigns input to the data of the node

        if(head == NULL){ 
            ptr->next = NULL;
            head = ptr; //insert only node to the list
        }
        else{
            temp = head;  //assigns head to temp
            
            while(temp->next != NULL){ //loop traverses through the list until it reaches the last node
                temp = temp->next;  
            }  
            temp->next = ptr;  //assigns input to the node at the end of the list
            ptr->next = NULL;
            
        }
        printf("\n\tNode successfully inserted.\n");  
        printf("\n\tPress enter to continue.");
        getch();
    }
        
     
}

//function for reversing the order of the linked list
void reverse(){
    struct node *current = head, *prev = NULL, *next = NULL; //assign value of head to current
    if(current == NULL){ //checks if list is empty
        printf("\n\tList is still empty.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{
        while(current != NULL){ //loop that traverses and reverses the list
            next = current->next;
            current->next = prev; //reverses the places of the values
            prev = current; 
            current = next;
        }
        head = prev;
        printf("\n\tList has been reversed.\n");
        printf("\n\tPress enter to continue.");
        getch();
    }
    
}

//function that sorts the linked list to ascending order
void ascending(){
    struct node *ptr = head, *temp = NULL; //assigns head to ptr
    int item;
    //checks if list is empty
    if(ptr == NULL){
        printf("\n\tList is still empty\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{
        //bubble sort implementation to make the list in ascending order
        while(ptr != NULL){
            temp = ptr->next; //assigns the next node to ptr to temp
            while(temp != NULL){ //second loop that traverses the elements of the list
                if(ptr->data > temp->data){ //compares the data of the two consecutive nodes
                    item = ptr->data;
                    ptr->data = temp->data; //swaps the places of the values
                    temp->data = item;
                }
                temp = temp->next; //goes to the next node
            }
            ptr = ptr->next; //goes to the next node
        }
        printf("\n\tList has been sorted.\n");
        printf("\n\tPress enter to continue.");
        getch();
    }
    
}

//function to remove the duplicate values in the linked list
void remove_duplicate(){
    struct node *current = head, *ptr = NULL, *temp = NULL; //assigns head to current
    //checks if list is empty
    if(current == NULL){
        printf("\n\tList is still empty.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{
        //utilizes the two loop method for removing duplicates
        while(current != NULL){ //first loop that traverses through each element of the list
            ptr = current;
            while(ptr->next != NULL){ //second loop that compares the current element to rest of the elements
                if(current->data == ptr->next->data){ //checks if the elements have the same value
                    temp = ptr->next;
                    ptr->next = ptr->next->next;
                    free(temp); //deletes the duplicate data
                }
                else{
                    ptr = ptr->next; //goes to the next node
                }
            }
            current = current->next; //goes to the next node to be checked
        }
        printf("\n\tDuplicates have been removed.\n");
        printf("\n\tPress enter to continue.");
        getch();
    }
    
}

//function that outputs the contents of the list
void print_list(){
    struct node *ptr = head; //assigns head to ptr
    if(ptr == NULL){ //checks if list is empty
        printf("\n\tThere are no items yet...\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{
        printf("\tCurrent Linked List: \n\n\t");
        while(ptr != NULL){ //loop that goes through the elements of the list
            printf("%d ",ptr->data); //outputs the data of each node visited
            ptr = ptr->next; //goes to the next node
        }
    }
    printf("\n\n\tPress enter to continue.");
    getch();

}
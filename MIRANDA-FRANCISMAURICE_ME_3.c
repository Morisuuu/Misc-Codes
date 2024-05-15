/*
    Submitted by: Francis Maurice B. Miranda || BSCS-2B

    CS104 DSA - MACHINE EXERCISE 3

        An implementation of STACK in linked list including the standard operations: push and pop. In addition to this,
        peek() and change() functions are implemented that will return the top value and change the value at a specified
        position in the stack, respectively.
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
  
struct node *top = NULL; //initializing the top

//function declarations
void push();
void pop();
void peek();
void change();
void display();

//main function
void main(){
    int opt = 0; //variable to take inputs
    //the main menu of the program (utilizes "goto" to redirect the program to the main menu)
    menu:
        //outputs the options/menu
        system("cls");
        printf("\t***********************\n");
        printf("\t*        STACK        *\n");
        printf("\t***********************\n\n");
        printf("\t 1. Insert value\n");
        printf("\t 2. Delete Value\n");
        printf("\t 3. Peek\n");
        printf("\t 4. Change value\n");
        printf("\t 5. Print Stack\n");
        printf("\t 6. Exit\n\n");

        printf("\t Please enter the number of your corresponding choice: ");
        scanf("%d", &opt);

        //function calls specific functions based on the corresponding option the user inputted
        switch(opt){
            case 1: system("cls"); push(); goto menu;
            case 2: system("cls"); pop(); goto menu;
            case 3: system("cls"); peek(); goto menu;
            case 4: system("cls"); change(); goto menu;
            case 5: system("cls"); display(); goto menu;
            case 6: printf("\t Thank you for using!"); break; //exits the program
            default: system("cls"); printf("\n\tInvalid choice.\n"); printf("\n\tPress enter to continue."); getch(); goto menu;
        }
}

//function that adds values to the stack
void push(){
    int item;  
    struct node *ptr = (struct node*)malloc(sizeof(struct node));   
    
	if(ptr == NULL){ //checks if stack is full
        printf("\n\tStack is full.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return; 
    }else{  
        printf("\n\tPlease enter the value to be inserted: ");  
        scanf("%d", &item);  
        
		if(top == NULL){  //checks if there are no items in the stack yet
            //inserts value as the first element
            ptr->data = item;  
            ptr->next = NULL;  
            top = ptr;  
        }else{  
            //inserts value at the top of the stack
            ptr->data = item;  
            ptr->next = top;  
            top = ptr;       
        }  
        printf("\n\tValue has been inserted.\n");
        printf("\n\tPress enter to continue.");
        getch(); 
    }  
}

//function that deletes values from the stack
void pop(){
    int item;  
    struct node *ptr;  
    
	if(top == NULL){  //checks if stack is empty
        printf("\n\tStack is empty.\n"); 
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }else{
        //removes value from the top
        item = top->data;
        ptr = top;
        top = top->next;  
        free(ptr);  
        printf("\n\tValue has been deleted.\n");
        printf("\n\tPress enter to continue.");
        getch();
    }
}

//function that returns the top value
void peek(){
    struct node *ptr = top;
    if(ptr == NULL){ //checks if stack is empty
        printf("\n\tStack is empty.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{
        printf("\tTop of Stack: %d\n\n\t", ptr->data); //outputs the top value
        printf("\n\n\tPress enter to continue.");
        getch();
    }
}

//function that changes the value from a specified position
void change(){
    struct node *ptr = top, *temp = ptr; //temp is for counting the size of the stack
    int item, pos, size = 0; //size is for the size of the stack
    if(top == NULL){ //checks if stack is empty
        printf("\n\tStack is empty.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{
        printf("\n\tEnter position in which the value will be changed: ");
        scanf("%d", &pos);
        while(temp != NULL){ //while loop that gets the current size of the stack
                temp = temp->next;
                size++;
        }
        if(pos <= 0 || pos > size){ //checks if pos is out of bounds or more than the size of the stack
            printf("\n\tPosition is out of bounds.\n");
            printf("\n\tPress enter to continue.");
            getch();
            return;
        }
        else if(pos == 1){ //checks if the value to be changed is the first position
            printf("\n\tEnter new value: ");
            scanf("%d", &item);
            ptr->data = item; //just changes the top value
            printf("\n\tValue has been changed.\n");
            printf("\n\tPress enter to continue.");
            getch();
        }
        else{
            for(int i = 0; i < pos-1; i++){ //for loop for traversing the stack to the specified position
                ptr = ptr->next; 
            }
            printf("\n\tEnter new value: ");
            scanf("%d", &item);
            ptr->data = item; //changes the value of the position specifed
            printf("\n\tValue has been changed.\n");
            printf("\n\tPress enter to continue.");
            getch();
        }
            
                
    }
            
}


//function that outputs the contents of the stack
void display(){ 
    struct node *ptr = top;
    if(ptr == NULL){ //checks if stack is empty
        printf("\n\tStack is empty.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{
        printf("\tCurrent Stack: \n\n\t");
        while(ptr != NULL){ //loop that goes through the stack
            printf("%d ",ptr->data); //outputs the value of the current node
            ptr = ptr->next; //goes to the next node
        }
    }
    printf("\n\n\tPress enter to continue.");
    getch();

}
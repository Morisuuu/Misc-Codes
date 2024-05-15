/*
    Submitted by: Francis Maurice B. Miranda || BSCS-2B

    CS104 DSA - MACHINE EXERCISE 2

        An implementation of QUEUE in linked list including the standard operations: enqueue and dequeue. In addition to this,
        peek() and change() functions are implemented that will return the front value and change the value at a specified
        position in the queue, respectively.
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
  
struct node *front = NULL, *rear = NULL; //initializing the front and rear

//function declarations
void enqueue();
void dequeue();
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
        printf("\t*        QUEUE        *\n");
        printf("\t***********************\n\n");
        printf("\t 1. Insert value\n");
        printf("\t 2. Delete Value\n");
        printf("\t 3. Peek\n");
        printf("\t 4. Change value\n");
        printf("\t 5. Print Queue\n");
        printf("\t 6. Exit\n\n");

        printf("\t Please enter the number of your corresponding choice: ");
        scanf("%d", &opt);

        //function calls specific functions based on the corresponding option the user inputted
        switch(opt){
            case 1: system("cls"); enqueue(); goto menu;
            case 2: system("cls"); dequeue(); goto menu;
            case 3: system("cls"); peek(); goto menu;
            case 4: system("cls"); change(); goto menu;
            case 5: system("cls"); display(); goto menu;
            case 6: printf("\t Thank you for using!"); break; //exits the program
            default: system("cls"); printf("\n\tInvalid choice.\n"); printf("\n\tPress enter to continue."); getch(); goto menu;
        }
}

//function that adds values to the queue
void enqueue(){
    struct node *ptr;
    int item;
    ptr = (struct node*)malloc(sizeof(struct node));

    if(ptr == NULL){ //checks if queue is full
        printf("\n\tQueue is full.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{
        printf("\n\tPlease enter the value to be inserted: ");
        scanf("%d", &item); //user input on the value to be inserted
        ptr->data = item;
        if(front == NULL){ //checks if there are no items in the queue yet
            //inserts the value at the front
            front = ptr;
            rear = ptr;
            rear->next = NULL;
            printf("\n\tValue has been inserted.\n");
            printf("\n\tPress enter to continue.");
            getch();
        }
        else{
            //adds the value to the rear of the queue
            rear->next = ptr;
            rear = ptr;
            rear->next = NULL;
            printf("\n\tValue has been inserted.");
            printf("\n\tPress enter to continue.");
            getch();

        }
    }
}

//function that deletes values from the queue
void dequeue(){
    struct node *ptr;
    int item;
    if(front == NULL){ //checks if queue is empty
        printf("\n\tQueue is empty.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{
        //removes value from the front
        ptr = front;
        item = ptr->data;
        front = front->next; //moves on to the next element as the front
        free(ptr);
        printf("\n\tValue has been deleted.\n");
        printf("\n\tPress enter to continue.");
        getch();
    }
}

//function that returns the front value
void peek(){
    struct node *ptr = front;
    if(ptr == NULL){ //checks if queue is empty
        printf("\n\tQueue is empty.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{ 
        printf("\tFront of Queue: %d\n\n\t", ptr->data); //outputs the front value
        printf("\n\n\tPress enter to continue.");
        getch();
    }
}

//function that changes the value from a specified position
void change(){
    struct node *ptr = front, *temp = ptr; //temp is for counting the size of the queue
    int item, pos, size = 0; //size is for the size of the queue
    if(front == NULL){ //checks if queue is empty
        printf("\n\tQueue is empty.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{
        printf("\n\tEnter position in which the value will be changed: ");
        scanf("%d", &pos);
        while(temp != NULL){ //while loop that gets the current size of the queue
                temp = temp->next;
                size++;
        }
        if(pos <= 0 || pos > size){ //checks if pos is out of bounds or more than the size of the queue
            printf("\n\tPosition is out of bounds.\n");
            printf("\n\tPress enter to continue.");
            getch();
            return;
        }
        else if(pos == 1){ //checks if the value to be changed is the first position
            printf("\n\tEnter new value: ");
            scanf("%d", &item);
            ptr->data = item; //just changes the front value
            printf("\n\tValue has been changed.\n");
            printf("\n\tPress enter to continue.");
            getch();
        }
        else{
            for(int i = 0; i < pos-1; i++){ //for loop for traversing the queue to the specified position
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


//function that outputs the contents of the queue
void display(){ 
    struct node *ptr = front;
    if(ptr == NULL){ //checks if queue is empty
        printf("\n\tQueue is empty.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{
        printf("\tCurrent Queue: \n\n\t");
        while(ptr != NULL){ //loop that goes through the queue
            printf("%d ",ptr->data); //outputs the value of the current node
            ptr = ptr->next; //goes to the next node
        }
    }
    printf("\n\n\tPress enter to continue.");
    getch();

}
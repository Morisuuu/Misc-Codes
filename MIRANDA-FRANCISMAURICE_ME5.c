/*
    Submitted by: Francis Maurice B. Miranda || BSCS-2B

    CS104 DSA - MACHINE EXERCISE 5

        An implementation of MergeSort in Linked List. The program will ask users to input numbers in the list, may it be 
        at the start or at the end. They can sort the given list using mergesort with the indicated option on the menu.
        This will sort the given list in ascending order and show the steps in doing so. To output the list, a print list
        option is indicated on the menu.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

struct node{  
    int data;  
    struct node *next;   
};
  
struct node *head;

void insert_start();
void insert_last();
void printList();
void delete();
struct node *mergesort(struct node *head);
struct node *getMid(struct node *head);
struct node *sortedMerge(struct node *left, struct node *right);


void main(){
    int choice = 0;
    menu:
        system("cls");
        printf("\n\t*************************\n");
        printf("\t*   MergeSort Sandbox   *\n");
        printf("\t*************************\n\n");
        printf("\t<1> Add at Start\n");
        printf("\t<2> Add at Last\n");
        printf("\t<3> Remove Item from start\n");
        printf("\t<4> Merge Sort\n");
        printf("\t<5> Print List\n");
        printf("\t<6> Exit\n\n");

        printf("\tEnter option: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: system("cls"); insert_start(); goto menu;
            case 2: system("cls"); insert_last(); goto menu;
            case 3: system("cls"); delete(); goto menu;
            case 4: system("cls"); head = mergesort(head); printList(); goto menu;
            case 5: system("cls"); printList(); goto menu;
            case 6: printf("\n\tThank you for using!"); return;
            default: system("cls"); printf("\n\tInvalid input."); getch(); goto menu;
        }
}

struct node *mergesort(struct node *head){ //O(nlogn)
    if(head == NULL || head->next == NULL){
        return head; //O(1)
    }

    struct node *mid = getMid(head); //O(n)
    struct node *left = head; //O(1)
    struct node *right = mid->next; //O(1)
    mid->next = NULL; //O(1)
    printList(); //not counting
    struct node *source = sortedMerge(mergesort(left), mergesort(right)); //T(n/2) + T(n/2) + n

    return source; //O(1)

}

struct node *getMid(struct node *head){ //O(n)
    struct node *ptr = head; // O(1)
    struct node *tail = head->next; // O(1)
    while(tail != NULL){
        tail = tail->next; //O(n)
        if(tail != NULL){
            ptr = ptr->next; //O(1)
            tail = tail->next; //O(1)
        }
    }
    return ptr; //O(1)
}

struct node *sortedMerge(struct node *left, struct node *right){ //O(n)
    struct node *ptr = NULL; //O(1)
    
    if(left == NULL){ 
        return right; //O(1)
    }
    else if(right == NULL){
        return left; //O(1)
    }
    else{
        if(left->data <= right->data){ 
            ptr = left; //O(1)
            ptr->next = sortedMerge(left->next, right); //T(n-1)
        }
        else{
            ptr = right; //O(1)
            ptr->next = sortedMerge(left, right->next); //T(n-1)
        }
        return ptr; //O(1)
        
    }
    
}

void delete(){
    int item;
    struct node *ptr;
    if(head == NULL){
        printf("\n\tList is empty.\n"); 
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{
        item = head->data;
        ptr = head;
        head = head->next;  
        free(ptr); 
        printList(); 
        printf("\n\tValue has been deleted.\n");
        printf("\n\tPress enter to continue.");
        getch();
    }
}

void printList(){
    struct node *ptr = head;
    if(ptr == NULL){
        printf("\n\tList is empty.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return; 
    }
    else{
        printf("\n\tCurrent Linked List: \n\t");
        while(ptr != NULL){
            printf("%d ", ptr->data);
            ptr = ptr->next;
        }

        printf("\n\n\tPress enter to continue.\n");
        getch();
    }
    
}

void insert_start(){
    int num = 0;
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    if(ptr == NULL){
        printf("\n\tError.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return; 
    }
    else{
        printf("\n\tEnter number: ");
        scanf("%d", &num);
        ptr->data = num; 
        ptr->next = head;  
        head = ptr;
        printList();
        printf("\n\tNode successfully inserted.\n");
        printf("\n\tPress enter to continue.");
        getch();
    }
}

void insert_last(){
    int num = 0;
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    struct node *temp;

    if(ptr == NULL){  
        printf("\n\tError.\n");
        printf("\n\tPress enter to continue.");
        getch();
        return;
    }
    else{
        printf("\n\tInput value: ");  
        scanf("%d", &num); 
        ptr->data = num; 

        if(head == NULL){ 
            ptr->next = NULL;
            head = ptr;
        }
        else{
            temp = head;
            
            while(temp->next != NULL){
                temp = temp->next;  
            }  
            temp->next = ptr;
            ptr->next = NULL;
            
        }
        printList();
        printf("\n\tNode successfully inserted.\n");  
        printf("\n\tPress enter to continue.");
        getch();
    }
}
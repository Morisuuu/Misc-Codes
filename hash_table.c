#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define MAX 10

struct node{
    int data;
    struct node *next;
};

struct node *head[MAX]={NULL}, *ptr;


void insert();
void display();
void search();
void delete();
int hash(int key);

void main(){
    int choice;
    menu:
        system("cls");
        printf("\n\t*************************\n");
        printf("\t*   Hash Table Sandbox  *\n");
        printf("\t*************************\n\n");
        printf("\t<1> Insert Item\n");
        printf("\t<2> Delete Item\n");
        printf("\t<3> Print Table\n");
        printf("\t<4> Search Table\n");
        printf("\t<5> Exit\n\n");

        printf("\tEnter option: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: system("cls"); insert(); goto menu;
            case 2: system("cls"); delete(); goto menu;
            case 3: system("cls"); display(); goto menu;
            case 4: system("cls"); search(); goto menu;
            case 5: printf("\n\tThank you for using!"); return;
            default: system("cls"); printf("\n\tInvalid input."); getch(); goto menu;
        }
}

int hash(int key){
    return key % MAX;
}

void insert(){
    int key, index;
    struct node * insert=(struct node *)malloc(sizeof(struct node));
    printf("\n\tEnter number: ");
    scanf("%d", &key);

    insert->data = key;
    insert->next = NULL;
    index = hash(key);

    if(head[index] == NULL){
        head[index] = insert;
        printf("\n\tItem successfully inserted.\n");
        display();
    }
    else{
        ptr = head[index];
        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        ptr->next = insert;
        printf("\n\tItem successfully inserted.\n");
        display();
    }

}

void display(){
    for(int i = 0; i < MAX; i++){
        if(head[i] == NULL){
            printf("\t%i\t---\n", i);
        }
        else{
            printf("\t%i\t", i);
            for(ptr = head[i]; ptr != NULL; ptr=ptr->next){
                printf("%d->", ptr->data);
            }
            printf("\n");
        }
    }

    printf("\n\tPress enter to continue.");
    getch();
}

void search(){
    int index, num;
    int count = 0;
    printf("\n\tEnter number to search: ");
    scanf("%d", &num);
    index = hash(num);
    if(head[index] == NULL){
        printf("\n\tItem does not exist.\n");
        printf("\n\tPress enter to continue.");
        getch();
    }
    else{
        for(int i = 0; i < MAX; i++){
            if(i == index){
                for(ptr = head[index]; ptr != NULL; ptr=ptr->next){
                    if(ptr->data == num){
                        printf("\n\tItem found at index: %d, position: %d.\n", i, count);
                        printf("\n\tPress enter to continue.");
                        getch();
                        break;
                    }
                    count++;
            
                }
                if(ptr == NULL){
                    printf("\n\tItem does not exist.\n");
                    printf("\n\tPress enter to continue.");
                    getch();
                }
            }
        }
    }
}

void delete(){
   int index, del, found = 0, count = 0;
   struct node *curr, *prev;

    printf("\n\tEnter number to delete: ");
    scanf("%d", &del);
    index = hash(del);

    if(head[index] == NULL){
        printf("\n\tItem does not exist.\n");
        printf("\n\tPress enter to continue.");
        getch();
    }
    else{
        if(head[index]->data == del && head[index]->next == NULL){
            curr = head[index];
            head[index] = NULL;
            free(curr);
            printf("\n\tItem deleted.\n");
            printf("\n\tPress enter to continue.");
            getch();
        }
        else if(head[index]->data == del && head[index]->next != NULL){
            curr = head[index];
            head[index] = head[index]->next;
            free(curr);
            printf("\n\tItem deleted.\n");
            printf("\n\tPress enter to continue.");
            getch();
        }
        else{
            for(ptr = head[index]; ptr != NULL; ptr=ptr->next){
                if(ptr->data == del){
                    found = 1;
                    break;
                }
            }

            if(found == 1){
                for(curr = head[index]; curr->data != del; curr=curr->next){
                    prev = curr;
                }
                prev->next = curr->next;
                free(curr);
                printf("\n\tItem deleted.\n");
                printf("\n\tPress enter to continue.");
                getch();
            }
            else{
                printf("\n\tItem does not exist.\n");
                printf("\n\tPress enter to continue.");
                getch();
            }
            }

    }
}

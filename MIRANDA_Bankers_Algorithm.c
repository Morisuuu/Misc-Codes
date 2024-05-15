/*

    OPERATING SYSTEMS - PROGRAMMING ACTIVITY
    C IMPLEMENTATION OF BANKER'S ALGORITHM

    Submitted by: Francis Maurice B. Miranda || BSCS 3A

    A simple C program implementation of the Banker's Algorithm for deadlock avoidance.

*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

//universal variables
int process, resource;

int max[MAX][MAX];
int alloc[MAX][MAX];
int need[MAX][MAX];
int avail[MAX][MAX];

int total_res[MAX];
int total_alloc[MAX];
int total_avail[MAX];
int sequence[MAX];

//function prototypes
void input();
void bankers();

void main(){
    int choice;
    //mini interface system for program
    menu:
        printf("\t\tBanker's Algorithm C Implementation\n\n");
        printf("\t1. Run\n");
        printf("\t2. Exit\n\n");

        printf("\tEnter option: ");
        scanf("%d", &choice);

        switch (choice){
        case 1: system("cls"); input(); bankers(); goto menu; break; //redirects user
        case 2: printf("\n\tBye! :>"); exit(1); break;
        default: printf("\nInvalid input! Try again.\n"); goto menu; break;
        }
}

//function that takes the user input and initializes the needed matrices
void input(){
    char c = 'A';
    printf("\tEnter the number of process: ");
    scanf("%d", &process);
    printf("\tEnter the number of resource: ");
    scanf("%d", &resource);
    system("cls");

    for(int i = 0; i < resource; i++){
        printf("\tEnter the total resource for resource %c: ", c++);
        scanf("%d", &total_res[i]);
    }   
    system("cls");

    //MAX Need Matrix
    printf("\tEnter the [MAX Need matrix]: \n");
    for(int i = 0; i < process; i++){
        printf("\tProcess %d: ", i);
        for(int j = 0; j < resource; j++){
            scanf("%d", &max[i][j]);
        }
    }

    system("cls");

    //ALLOCATION Matrix
    printf("\tEnter the [ALLOCATION matrix]: \n");
    for(int i = 0; i < process; i++){
        printf("\tProcess %d: ", i);
        for(int j = 0; j < resource; j++){
            scanf("%d", &alloc[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    system("cls");

    //NEED Matrix
    printf("\t[NEED Matrix]: \n");
    for(int i = 0; i < process; i++){
        printf("\tProcess %d: ", i);
        for(int j = 0; j < resource; j++){
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    //Total Allocation
    printf("\n\n\t[Total Allocation]: ");
    for(int j = 0; j < resource; j++){
        for(int i = 0; i < process; i++){
            total_alloc[j] += alloc[i][j];
        }
        printf("%d ", total_alloc[j]);
    }

    //Total Available
    printf("\n\t[Total Available Resources]: ");
    for(int i = 0; i < resource; i++){
        total_avail[i] = total_res[i] - total_alloc[i];
        avail[0][i] = total_avail[i];
        printf("%d ", total_avail[i]);
    }

    printf("\n");
    system("pause");
    system("cls");
}

//implements the safety checking and output of the banker's algorithm
void bankers(){
    int temp[resource];
    int finish[process];
    int num = 0;
    int check = 0; //1 - can execute, 0 - can't execute
    int state = 0; //0 - safe, 1 - deadlock
    int proc = 0; 
    int point = 0;

    //loop initializes the array that records the executed process to 0 - not yet executed
    for(int i = 0; i < process; i++){
        finish[i] = 0;
    }

    //primary loop - loops until there is deadlock or everything is executed
    while(num < process && state == 0){
        
        if(proc >= process){ //resets value of proc every time it surpasses the number of processes 
            proc = 0;
        }
        
        point = proc;
        check = 1;
        
        do{ //secondary loop - loops to check the process execution/assigning the available matrix
            if(finish[proc] == 0){ 
                check = 1;
                for(int j = 0; j < resource; j++){
                    if(need[proc][j] > avail[num][j]){
                        check = 0;
                        break;
                    }
                }
                if(check == 1){ //outputs when process is executed successfully
                    finish[proc] = 1;
                    printf("\tProcess %d has successfully executed!\n", proc);
                    printf("\tCurrently Available Resources: ");
                    for(int k = 0; k < resource; k++){
                        avail[num+1][k] = avail[num][k] + alloc[proc][k];
                        printf("%d ", avail[num+1][k]);   
                    }
                    printf("\n");
                    sequence[num] = proc;
                    proc++;
                    num++;
                    system("pause");
                    system("cls");
                    break;
                }
                else{ //when a process is skipped
                    printf("\n\tNot enough resources, skip Process %d. \n", proc);
                    proc++;
                    system("pause");
                    system("cls");
                }
            }
            else{
                proc++;
            }
            if(proc >= process){
                proc = 0;
            }
        }while(proc != point);

        if(proc == point){
            printf("\tDEADLOCK!\n");
            state = 1;
            system("pause");
            system("cls");
        }
    }
    //safe when all the process have been executed
    if(state == 0){
        printf("\tSAFE!\n");
        printf("\tSequence of Execution: \n\t");
        for(int i = 0; i < process; i++){
            printf("P%d ", sequence[i]);
        }
        printf("\n");
        system("pause");
        system("cls");
    }
    
}

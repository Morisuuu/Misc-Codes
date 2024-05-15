/*
MIRANDA - CPU SCHEDULING IMPLEMENTATION IN C

    This project is a simple C implementation of the following CPU Scheduling Algorithms: FSCS, SJF(NP), Priority (NP)
    and Round Robin. The project requires the user to input the number of processes (n), their corresponding burst times
    and priorities. The program then outputs the Completion Time, Turnaround Time and Waiting Time in Table Format. The 
    Average Turnaround Time and Average Waiting Time is then computed and outputted.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define MAX 10

struct process{ //struct that contains all info needed for process
    int pid, bt, ct, wt, tat, prio, rt;
};

//global variables
struct process p[MAX], temp;
struct process p2[MAX];
int n = 0;

//function prototype
void FCFS();
void SJF();
void Prio();
void RR(int quantum);
void AVG();

//main function (menu iterface)
void main(){
    int quantum = 0;
    
    menu:
        system("cls");
        printf("\n\t*******************************\n");
        printf("\t*    CPU SCHEDULING SANDBOX   *\n");
        printf("\t*******************************\n\n");
        printf("\tEnter number of processes: ");
        scanf("%d", &n);

        //gets input from user (number of processes, burst time, priority)
        for(int i = 0; i < n; i++){
            p[i].pid = i + 1;
            printf("\n\tProcess #%d:\n", p[i].pid);
            p2[i].pid = p[i].pid;
            printf("\tEnter burst time: ");
            scanf("%d", &p[i].bt);
            p2[i].bt = p[i].bt;
            printf("\tEnter priority (lowest = priority): ");
            scanf("%d", &p[i].prio);
            p2[i].prio = p[i].prio;
            p[i].rt = p[i].bt;
            p2[i].rt = p[i].bt;
        }

        //prompt for quantum time
        printf("\tEnter Time Quantum: ");
        scanf("%d", &quantum);


        //function calls for the CPU Scheduling Algorithms
        FCFS();
        SJF();
        Prio();
        RR(quantum);

}

//function that calculates the Average Turnaround Time and Average Waiting Time
void AVG(){
    int total_tat = 0, total_wt = 0;
    for(int i = 0; i < n; i++) {
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    printf("\n\tAverage Turnaround Time: %.2f\n", (float)total_tat/n);
    printf("\tAverage Waiting Time: %.2f\n", (float)total_wt/n);
}

//function that implements the First Come First Serve Scheduling Algorithm
void FCFS(){
    int ct = 0;
    system("cls");
    printf("\tFirst Come First Serve: \n");
    printf("\tProcessID\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++){
        ct += p[i].bt;
        p[i].ct = p[i].tat = ct;
        p[i].wt = p[i].tat - p[i].bt;
        printf("\tP%d\t\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].bt,p[i].ct,p[i].tat,p[i].wt); //outputs the process info in table form
    }
    AVG(); 

    getch();
}

//function that implements the Shortest Job First (Non-Preemptive)
void SJF(){
    int ct = 0;
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j< n-i-1; j++){
            if(p[j].bt > p[j+1].bt){ //sorts process in terms of lowest burst time to highest (bubble sort)
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    system("cls");
    printf("\tShortest Job First (NP): \n");
    printf("\tProcessID\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++){
        ct += p[i].bt;
        p[i].ct = p[i].tat = ct;
        p[i].wt = p[i].tat - p[i].bt;
        printf("\tP%d\t\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].bt,p[i].ct,p[i].tat,p[i].wt); //outputs the process info in table form
    }
    AVG();

    getch();
}

//function that implements the Priority (Non-Preemptive) Scheduling
void Prio(){
    int ct = 0;
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j< n-i-1; j++){
            if(p[j].prio > p[j+1].prio){ //sorts process in terms of highest priority (smallest number) to lowest priority (largest number)
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    system("cls");
    printf("\tPriority (NP) Scheduling: \n");
    printf("\tProcessID\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++){
        ct += p[i].bt;
        p[i].ct = p[i].tat = ct;
        p[i].wt = p[i].tat - p[i].bt;
        printf("\tP%d\t\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].bt,p[i].ct,p[i].tat,p[i].wt); //outputs the process info in table form
    }
    AVG();

    getch();
}

//function that implements the Round Robin Scheduling Algorithm
void RR(int quantum){
    int ct = 0, check = 0;
    for(int i = 0; i < n; i++){ //copies content of original unsorted input to original struct
        p[i].pid = p2[i].pid;
        p[i].bt = p2[i].bt;
        p[i].prio = p2[i].prio;
    }
    system("cls");
    printf("\tRound Robin Scheduling: \n");
    for (int i = 0 ; i < n ; i++)
		p[i].rt = p[i].bt;

    while(!check){ //loop that checks if all process has been run through
        check = 1;
        for(int i = 0; i < n; i++){
            if(p[i].rt > 0){ //checks if there is remaining time in the process' burst time
                check = 0;
                if(p[i].rt > quantum){
                    ct += quantum;
                    p[i].rt -= quantum;
                }
                else{ //adds up to turnaround time and waiting time otherwise
                    ct += p[i].rt;
                    p[i].wt = ct - p[i].bt;
                    p[i].rt = 0;
                    p[i].tat = p[i].bt + p[i].wt;
                }
            }
        } 
    }
    printf("\tProcessID\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++){
        printf("\tP%d\t\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].bt,p[i].tat,p[i].tat,p[i].wt); //outputs the process info in table form
    }
    AVG();

    getch();
}
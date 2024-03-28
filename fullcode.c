#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct {
    char name[50];
    int age;
    int wt;
    int priority;
} Patient;

typedef struct {
    Patient items[MAX_SIZE];
    int rear;
} PriorityQueue;

void insert(PriorityQueue* pq, Patient p);
Patient dequeue(PriorityQueue* pq);
void displayPatient(Patient p);
void displayQueue(PriorityQueue* pq);
void insert(PriorityQueue* pq, Patient p);
int isEmpty(PriorityQueue* pq);
void initQueue(PriorityQueue* pq);

// ANSI escape codes for colors
#define COLOR_RESET "\033[0m"
#define COLOR_BOLD "\033[1m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"

typedef struct {
    Patient items[MAX_SIZE];
    int count;
} PatientList;

void addToPatientList(PatientList* list, Patient p);

int main() {
    PriorityQueue pq;
    initQueue(&pq);

    PatientList addedPatients;
    addedPatients.count = 0;

    int choice;
    do {
        printf(COLOR_BOLD "\n\t\t\tHospital Management System\n" COLOR_RESET);
        printf(COLOR_YELLOW "1. Add patient\n");
        printf("2. Serve patient\n");
        printf("3. Display non served patients list\n");
        printf("4. Display all patients details\n");
        printf("5. Exit\n" COLOR_RESET);
        printf(COLOR_BLUE "Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                Patient p;
                printf("Enter patient name: ");
                scanf(" %[^\n]", p.name);
                printf("Enter patient age: ");
                scanf("%d", &p.age);
                printf("Enter weight:");
                scanf("%d", &p.wt);
                printf(COLOR_GREEN "Please refer to this table for your disease:\n");
                // Print the table
                printf("1. Emergency (accidents, cardiac arrest..)\n");
                printf("2. Chronic disease\n");
                printf("3. Illness\n");
                printf("4. General checkup\n" COLOR_RESET);
                printf(COLOR_BLUE "Enter patient priority: ");
                scanf("%d", &p.priority);
                insert(&pq, p);
                addToPatientList(&addedPatients, p); // Add patient to the separate list
                break;
            }
            case 2: {
                Patient p = dequeue(&pq);
                if (p.priority != 0) {
                    printf(COLOR_GREEN "Serving patient according to their priority:\n");
                    displayPatient(p);
                }
                break;
            }
            case 3: {
                displayQueue(&pq);
                break;
            }
            case 4: {
                printf(COLOR_BLUE "Added patients list:\n" COLOR_RESET);
                displayQueuer(&addedPatients); // Display the separate list of added patients
                break;
            }
            case 5: {
                printf(COLOR_RED "Exiting the program.\n" COLOR_RESET);
                break;
            }
            default: {
                printf(COLOR_RED "Invalid choice. Please try again.\n" COLOR_RESET);
                break;
            }
        }
    } while (choice != 5);

    return 0;
}

// ...

void addToPatientList(PatientList* list, Patient p) {
    if (list->count >= MAX_SIZE) {
        printf("Added patients list is full. Cannot add more patients.\n");
        return;
    }
    list->items[list->count] = p;
    list->count++;
}
void initQueue(PriorityQueue* pq) 
{
    pq->rear = -1;
}

//to check patients list(PriorityQueue)is empty or not
int isEmpty(PriorityQueue* pq) 
{
    return pq->rear == -1;//it returns true if rear=-1
}

//to check if the patients list(PriorityQueue) is full or not
int isFull(PriorityQueue* pq)
{
    return pq->rear == MAX_SIZE - 1; // it returns true if rear= max-1
}

void insert(PriorityQueue* pq, Patient p)
{
    if (isFull(pq))
    {
        printf("Priority queue is full. Cannot insert more patients.\n");
        return;
    }

    int i;
    // Find the correct position to insert the patient based on priority
    for (i = pq->rear; i >= 0; i--) 
    {
        if (pq->items[i].priority > p.priority)
            pq->items[i + 1] = pq->items[i];
        else
            break;
    }
    pq->items[i + 1] = p;
    pq->rear++;
}
Patient dequeue(PriorityQueue* pq) 
{
    if (isEmpty(pq))
    {
        printf("Priority queue is empty. No patients to dequeue.\n");
        Patient emptyPatient = { "", 0, 0 };//emptyPatient is avariable of Patient
        return emptyPatient;               //and intialising to NULL
    }
    Patient front = pq->items[0];
    for (int i = 0; i < pq->rear; i++) 
    {
        pq->items[i] = pq->items[i + 1];
    }
    pq->rear--;
    return front;
}
//to display served Patient details
void displayPatient(Patient p)
{
    printf("Name: %s\n", p.name);
    printf("Age: %d\n", p.age);
    printf("weight: %d\n",p.wt);
    printf("Priority: %d\n", p.priority);
    printf("------------------------\n");
}
//to display all patients priority
void displayQueue(PriorityQueue* pq)
{
    if (isEmpty(pq)) 
    {
        printf("Priority queue is empty. No patients to display.\n");
        return;
    }

    printf("Patients in the priority queue:\n");
    for (int i = 0; i <= pq->rear; i++) 
    {
        displayPatient(pq->items[i]);
    }
}
void displayQueuer(PriorityQueue* pq)
{
    if (isEmpty(pq)) 
    {
        printf("Priority queue is empty. No patients to display.\n");
        return;
    }

    printf("Patients in the priority queue:\n");
    for (int i = 0; i <= (pq->rear)-1; i++) 
    {
        displayPatient(pq->items[i]);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_APPOINTMENTS 100

// Structure for Appointment
struct Appointment {
    int id;
    char patientName[50];
    char gender[10];           // New field
    char doctorName[50];
    char date[15];
    char time[10];
};

// Function declarations
void addAppointment(struct Appointment *appointments, int *count);
void viewAppointments(struct Appointment *appointments, int count);
void saveToFile(struct Appointment *appointments, int count);
void loadFromFile(struct Appointment *appointments, int *count);
void searchAppointment(struct Appointment *appointments, int count);
void deleteAppointment(struct Appointment *appointments, int *count);
void menu();


int main() {
    struct Appointment appointments[MAX_APPOINTMENTS];
    int count = 0;

    // Load appointments from file at start
    loadFromFile(appointments, &count);

    int choice;
    do {
        menu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

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
        
        switch (choice) {
            case 1: addAppointment(appointments, &count); break;
            case 2: viewAppointments(appointments, count); break;
            case 3: searchAppointment(appointments, count); break;
            case 4: deleteAppointment(appointments, &count); break;
            case 5: saveToFile(appointments, count);
                    printf("Appointments saved. Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Menu
void menu() {
    printf("\n--- Clinic Appointment Management ---\n");
    printf("1. Add Appointment\n");
    printf("2. View All Appointments\n");
    printf("3. Search Appointment by ID\n");
    printf("4. Delete Appointment by ID\n");
    printf("5. Exit & Save\n");
}


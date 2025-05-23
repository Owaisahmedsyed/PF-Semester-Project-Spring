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

// Function to add appointment
void addAppointment(struct Appointment *appointments, int *count) {
    if (*count >= MAX_APPOINTMENTS) {
        printf("Cannot add more appointments.\n");
        return;
    }

    struct Appointment *a = &appointments[*count];
    a->id = *count + 1;

    printf("Enter patient name: ");
    fgets(a->patientName, sizeof(a->patientName), stdin);
    a->patientName[strcspn(a->patientName, "\n")] = '\0';

    printf("Enter gender (Male/Female/Other): ");
    fgets(a->gender, sizeof(a->gender), stdin);
    a->gender[strcspn(a->gender, "\n")] = '\0';

    printf("Enter doctor name: ");
    fgets(a->doctorName, sizeof(a->doctorName), stdin);
    a->doctorName[strcspn(a->doctorName, "\n")] = '\0';

    printf("Enter date (dd/mm/yyyy): ");
    fgets(a->date, sizeof(a->date), stdin);
    a->date[strcspn(a->date, "\n")] = '\0';

    printf("Enter time (hh:mm): ");
    fgets(a->time, sizeof(a->time), stdin);
    a->time[strcspn(a->time, "\n")] = '\0';

    (*count)++;

    printf("Appointment added successfully.\n");
}

// Function to view appointments
void viewAppointments(struct Appointment *appointments, int count) {
    if (count == 0) {
        printf("No appointments to show.\n");
        return;
    }

    printf("\n%-5s %-20s %-10s %-20s %-12s %-10s\n", "ID", "Patient Name", "Gender", "Doctor Name", "Date", "Time");
    printf("--------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-10s %-20s %-12s %-10s\n",
               appointments[i].id,
               appointments[i].patientName,
               appointments[i].gender,
               appointments[i].doctorName,
               appointments[i].date,
               appointments[i].time);
    }
}
// Save to file
void saveToFile(struct Appointment *appointments, int count) {
    FILE *file = fopen("appointments.txt", "w");
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%s\n",
                appointments[i].id,
                appointments[i].patientName,
                appointments[i].gender,
                appointments[i].doctorName,
                appointments[i].date,
                appointments[i].time);
    }

    fclose(file);
}

// Load from file
void loadFromFile(struct Appointment *appointments, int *count) {
    FILE *file = fopen("appointments.txt", "r");
    if (!file) return;

    while (fscanf(file, "%d,%49[^,],%9[^,],%49[^,],%14[^,],%9[^\n]\n",
                  &appointments[*count].id,
                  appointments[*count].patientName,
                  appointments[*count].gender,
                  appointments[*count].doctorName,
                  appointments[*count].date,
                  appointments[*count].time) == 6) {
        (*count)++;
    }

    fclose(file);
}

// Search appointment by ID
void searchAppointment(struct Appointment *appointments, int count) {
    int id;
    printf("Enter appointment ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (appointments[i].id == id) {
            printf("\nAppointment Found:\n");
            printf("Patient: %s\nGender: %s\nDoctor: %s\nDate: %s\nTime: %s\n",
                   appointments[i].patientName,
                   appointments[i].gender,
                   appointments[i].doctorName,
                   appointments[i].date,
                   appointments[i].time);
            return;
        }
    }

    printf("Appointment with ID %d not found.\n", id);
}

// Delete appointment
void deleteAppointment(struct Appointment *appointments, int *count) {
    int id, found = 0;
    printf("Enter appointment ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *count; i++) {
        if (appointments[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                appointments[j] = appointments[j + 1];
                appointments[j].id = j + 1;
            }
            (*count)--;
            found = 1;
            printf("Appointment deleted.\n");
            break;
        }
    }

    if (!found)
        printf("Appointment with ID %d not found.\n", id);
}



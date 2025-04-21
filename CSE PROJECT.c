// NSU Hospital Management System
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 10

struct Patient {
    char name[50];
    int age;
    char gender[10];
    char contact[20];
    char username[20];
    char password[20];
    int hasOverduePayment;
};

struct Doctor {
    char name[50];
    char specialization[50];
    int available;
    float consultationFee;
};


struct Patient patients[MAX_PATIENTS];
int patientCount = 0;

struct Doctor doctors[MAX_DOCTORS] = {
    {"Dr. Ahmed", "Cardiologist", 1, 1000.0},
    {"Dr. Farhana", "Dermatologist", 1, 800.0},
    {"Dr. Rahman", "Neurologist", 0, 1200.0},
    {"Dr. Zaman", "Pediatrician", 1, 900.0}
};
int doctorCount = 4;

// Function declarations
void mainMenu();
void registerPatient();
int loginPatient();
void showDoctors();
void bookAppointment(int patientIndex);
void clearInputBuffer();

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice, loggedInIndex;
    while (1) {
        printf("\n--- NSU Hospital Management System ---\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                registerPatient();
                break;
            case 2:
                loggedInIndex = loginPatient();
                if (loggedInIndex != -1) {
                    bookAppointment(loggedInIndex);
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void registerPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Patient limit reached.\n");
        return;
    }

    printf("\n--- Patient Registration ---\n");
    struct Patient newPatient;

    printf("Name: ");
    fgets(newPatient.name, 50, stdin);
    newPatient.name[strcspn(newPatient.name, "\n")] = 0;

    printf("Age: ");
    scanf("%d", &newPatient.age);
    clearInputBuffer();

    printf("Gender: ");
    fgets(newPatient.gender, 10, stdin);
    newPatient.gender[strcspn(newPatient.gender, "\n")] = 0;

    printf("Contact: ");
    fgets(newPatient.contact, 20, stdin);
    newPatient.contact[strcspn(newPatient.contact, "\n")] = 0;

    printf("Username: ");
    fgets(newPatient.username, 20, stdin);
    newPatient.username[strcspn(newPatient.username, "\n")] = 0;

    printf("Password: ");
    fgets(newPatient.password, 20, stdin);
    newPatient.password[strcspn(newPatient.password, "\n")] = 0;

    newPatient.hasOverduePayment = 0;

    patients[patientCount++] = newPatient;
    printf("Registration successful!\n");
}

int loginPatient() {
    char username[20], password[20];
    printf("\n--- Patient Login ---\n");
    printf("Username: ");
    fgets(username, 20, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Password: ");
    fgets(password, 20, stdin);
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].username, username) == 0 && strcmp(patients[i].password, password) == 0) {
            printf("Login successful.\n");
            return i;
        }
    }
    printf("Invalid credentials.\n");
    return -1;
}

void showDoctors() {
    printf("\n--- Available Doctors ---\n");
    for (int i = 0; i < doctorCount; i++) {
        printf("%d. %s (%s) - Fee: %.2f - %s\n", i + 1, doctors[i].name, doctors[i].specialization,
               doctors[i].consultationFee, doctors[i].available ? "Available" : "Not Available");
    }
}

void bookAppointment(int patientIndex) {
    if (patients[patientIndex].hasOverduePayment) {
        printf("You have overdue payments. Clear them before booking.");
        return;
    }

    showDoctors();
    int choice;
    printf("\nEnter the doctor number to book: ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice < 1 || choice > doctorCount || !doctors[choice - 1].available) {
        printf("Invalid choice or doctor not available.\n");
        return;
    }

    printf("Pay %.2f to confirm appointment: ", doctors[choice - 1].consultationFee);
    float payment;
    scanf("%f", &payment);
    clearInputBuffer();

    if (payment >= doctors[choice - 1].consultationFee) {
        printf("Appointment confirmed with %s.\n", doctors[choice - 1].name);
    } else {
        printf("Insufficient payment. Appointment marked as overdue.\n");
        patients[patientIndex].hasOverduePayment = 1;
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

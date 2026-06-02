#include <stdio.h>
#include <string.h>

#define MAX_MEMBERS 100
#define MAX_CLASSES 100

struct Member {
    int member_id;
    char member_name[50];
    int member_age;
    char membership_type[20]; // Monthly, Quarterly, Annual
};

struct ClassRegistration {
    int member_id;
    int class_id;
    char class_type[10]; // Cardio/Strength
};

struct gymdetails {
    int member_id;
    int weekly_target;
    float time_spent;
};

struct Member members[MAX_MEMBERS];
struct ClassRegistration classes[MAX_CLASSES];
struct gymdetails gymStatus[MAX_MEMBERS];

int member_count = 0;
int class_count = 0;
int gymStatus_count = 0; // To keep track of the number of gym status entries

// Function prototypes
void addMember();
void deleteMember();
void registerForClass();
void cancelClassRegistration();
void printMemberClasses();
void gymstatusupdate();
void displaygymstatus();

int main() {
    int choice;
    while (1) {
        printf("\nGym Membership Management System\n");
        printf("1. Add a new member\n");
        printf("2. Delete a member record\n");
        printf("3. Register for a class or facility\n");
        printf("4. Cancel a class registration\n");
        printf("5. Print classes registered by a member\n");
        printf("6. Update gym status\n");
        printf("7. Display gym status\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addMember(); break;
            case 2: deleteMember(); break;
            case 3: registerForClass(); break;
            case 4: cancelClassRegistration(); break;
            case 5: printMemberClasses(); break;
            case 6: gymstatusupdate(); break;
            case 7: displaygymstatus(); break;
            case 8: return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}

void addMember() {
    if (member_count >= MAX_MEMBERS) {
        printf("Member limit reached!\n");
        return;
    }
    printf("Enter Member ID: ");
    scanf("%d", &members[member_count].member_id);
    printf("Enter Member Name: ");
    scanf(" %[^\n]s", members[member_count].member_name);
    printf("Enter age:");
    scanf("%d", &members[member_count].member_age);
    if (members[member_count].member_age <= 15) {
        printf("You are not eligible!\n");
    }
    printf("Enter Membership Type (Monthly/Quarterly/Annual): ");
    scanf(" %[^\n]s", members[member_count].membership_type);
    member_count++;
    printf("Member added successfully!\n");
}

void deleteMember() {
    int id, i, found = 0;
    printf("Enter Member ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < member_count; i++) {
        if (members[i].member_id == id) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Member not found!\n");
        return;
    }

    for (; i < member_count - 1; i++) {
        members[i] = members[i + 1];
    }
    member_count--;
    printf("Member deleted successfully!\n");
}

void registerForClass() {
    if (class_count >= MAX_CLASSES) {
        printf("Class limit reached!\n");
        return;
    }

    int member_id, cardio_count = 0, strength_count = 0;
    printf("Enter Member ID: ");
    scanf("%d", &member_id);

    for (int i = 0; i < class_count; i++) {
        if (classes[i].member_id == member_id) {
            if (strcmp(classes[i].class_type, "Cardio") == 0)
                cardio_count++;
            else if (strcmp(classes[i].class_type, "Strength") == 0)
                strength_count++;
        }
    }

    if (cardio_count > 3) {
        printf("You have reached the maximum number of Cardio classes!\n");
        return;
    }
    if (strength_count > 2) {
        printf("You have reached the maximum number of Strength classes!\n");
        return;
    }

    printf("Enter Class ID: ");
    scanf("%d", &classes[class_count].class_id);
    printf("Enter Class Type (Cardio/Strength): ");
    scanf(" %[^\n]s", classes[class_count].class_type);

    if (strcmp(classes[class_count].class_type, "Cardio") == 0 && cardio_count >= 3) {
        printf("Cannot register for more than 3 Cardio classes!\n");
        return;
    }
    if (strcmp(classes[class_count].class_type, "Strength") == 0 && strength_count >= 2) {
        printf("Cannot register for more than 2 Strength classes!\n");
        return;
    }

    classes[class_count].member_id = member_id;
    class_count++;
    printf("Class registered successfully!\n");
}

void cancelClassRegistration() {
    int member_id, class_id, i, found = 0;
    printf("Enter Member ID: ");
    scanf("%d", &member_id);
    printf("Enter Class ID to cancel: ");
    scanf("%d", &class_id);

    for (i = 0; i < class_count; i++) {
        if (classes[i].member_id == member_id && classes[i].class_id == class_id) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Class registration not found!\n");
        return;
    }

    for (; i < class_count - 1; i++) {
        classes[i] = classes[i + 1];
    }
    class_count--;
    printf("Class registration cancelled successfully!\n");
}

void printMemberClasses() {
    int member_id, found = 0;
    printf("Enter Member ID: ");
    scanf("%d", &member_id);

    printf("Classes registered by Member ID %d:\n", member_id);
    for (int i = 0; i < class_count; i++) {
        if (classes[i].member_id == member_id) {
            printf("Class ID: %d, Class Type: %s\n", classes[i].class_id, classes[i].class_type);
            found = 1;
        }
    }

    if (!found) {
        printf("No classes found for this member.\n");
    }
}

void gymstatusupdate() {
    if (gymStatus_count >= MAX_MEMBERS) {
        printf("Gym status limit reached!\n");
        return;
    }

    int member_id;
    printf("Enter Member ID: ");
    scanf("%d", &member_id);

    int i, found = 0;
    for (i = 0; i < gymStatus_count; i++) {
        if (gymStatus[i].member_id == member_id) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Enter new weekly target for Member ID %d: ", member_id);
        scanf("%d", &gymStatus[i].weekly_target);
        printf("Enter time spent in gym (in hours): ");
        scanf("%f", &gymStatus[i].time_spent);
    } else {
        gymStatus[gymStatus_count].member_id = member_id;
        printf("Enter weekly target for Member ID %d: ", member_id);
        scanf("%d", &gymStatus[gymStatus_count].weekly_target);
        printf("Enter time spent in gym (in hours): ");
        scanf("%f", &gymStatus[gymStatus_count].time_spent);
        gymStatus_count++;
    }
    printf("Gym status updated successfully!\n");
}

void displaygymstatus() {
    if (gymStatus_count == 0) {
        printf("No gym status available!\n");
        return;
    }

    // Sort gymStatus array by time spent in descending order
    for (int i = 0; i < gymStatus_count - 1; i++) {
        for (int j = i + 1; j < gymStatus_count; j++) {
            if (gymStatus[i].time_spent < gymStatus[j].time_spent) {
                struct gymdetails temp = gymStatus[i];
                gymStatus[i] = gymStatus[j];
                gymStatus[j] = temp;
            }
        }
    }

    // Display gym status
    printf("\nGym Status:\n");
    for (int i = 0; i < gymStatus_count; i++) {
        printf("Member ID: %d, Weekly Target: %d, Time Spent: %.2f hours\n", 
               gymStatus[i].member_id, gymStatus[i].weekly_target, gymStatus[i].time_spent);
    }

    printf("\nMember with the highest time spent in the gym: Member ID %d, Time Spent: %.2f hours\n", 
           gymStatus[0].member_id, gymStatus[0].time_spent);
}
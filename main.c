#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<float.h>

// Function prototypes
void TeamRoaster();
void PlayerStats();
void coachesRoster();
void EquipmentInventory();
void financialRecords();

// Main Menu Function
void mainMenu() {
    int choice, preference;

    printf("\n*WELCOME TO SLAM-DUNK BASKETBALL CLUB!*\n\n"); 
    printf("MAIN MENU:\n"); 
    printf("1. View Records\n2. Add and Create new Records\n3. Delete Existing Records\n4. Search Records\n\n");
    printf("Enter the number of the operation you would like to perform: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid Input - Please enter a valid number.\n");
        return;
    }

    if(choice >= 1 && choice <= 4) {
        switch(choice) {
            case 1:
                printf("\nWhich records would you like to view?\n");
                break;
            case 2:
                printf("\nWhich records would you like to add or create?\n");
                break;
            case 3:
                printf("\nWhich records would you like to delete?\n");
                break;
            case 4:
                printf("\nWhich records would you like to search?\n");
                break;
        }

        printf("1. Team Roster\n2. Player Stats\n3. Coaches Roster\n4. Equipment Inventory\n5. Financial Records\n\n");
        printf("Enter the number of your preference: ");
        if (scanf("%d", &preference) != 1 || preference < 1 || preference > 5) {
            printf("Invalid Input - Please enter a valid number.\n");
            return;
        }

        switch(preference) {
            case 1: TeamRoaster(); break;
            case 2: PlayerStats(); break;
            case 3: coachesRoster(); break;
            case 4: EquipmentInventory(); break;
            case 5: financialRecords(); break;
        }
    } else {
        printf("Invalid Input - Please enter a valid operation number.\n");
    }
}

// Placeholder functions
void TeamRoaster() {
    printf("Team Roster function called.\n");
}

void PlayerStats() {
    printf("Player Stats function called.\n");
}

void coachesRoster() {
    printf("Coaches Roster function called.\n");
}

void EquipmentInventory() {
    printf("Equipment Inventory function called.\n");
}

void financialRecords() {
    printf("Financial Records function called.\n");
}

// Main function
int main() {
    mainMenu();
    return 0;
}
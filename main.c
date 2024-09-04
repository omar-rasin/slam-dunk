#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *teamRosterFilename = "team_roster.txt";
const char *statsFilename = "player_stats.txt";
const char *coachesRosterFilename = "coaches_roster.txt";
const char *equipmentInventoryFilename = "equipment_inventory.txt";  // File for Equipment Inventory

// Function prototypes
void mainMenu();
void TeamRoster();
void viewTeamRoster();
void addPlayer();
void deletePlayer();
void searchPlayer();
void PlayerStats();
void viewPlayerStats();
void addPlayerStats();
void deletePlayerStats();
void updatePlayerStats();  // Function prototype for updating player stats
void CoachesRoster();
void viewCoachesRoster();
void addCoach();
void deleteCoach();
void EquipmentInventory();  // Function prototype for Equipment Inventory
void viewEquipmentInventory();
void addEquipment();
void deleteEquipment();
void searchEquipment();
void ensureFileExists(const char *filename);
int getNextPlayerNumber();
int getNextPlayerStatNumber();
int getNextCoachNumber();
int getNextEquipmentNumber();  // Function prototype for getting the next equipment number

// Main Menu Function
void mainMenu() {
    int choice;

    printf("\n*** WELCOME TO SLAM-DUNK BASKETBALL CLUB! ***\n\n"); 
    printf("MAIN MENU:\n"); 
    printf("1. Team Roster\n2. Player Stats\n3. Coaches Roster\n4. Equipment Inventory\n\n");
    printf("Enter the number of your preference: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid Input - Please enter a valid number.\n");
        return;
    }

    switch(choice) {
        case 1: TeamRoster(); break;
        case 2: PlayerStats(); break;
        case 3: CoachesRoster(); break;
        case 4: EquipmentInventory(); break;
        default: printf("Invalid Input - Please enter a valid operation number.\n");
    }
}

// Function to manage Team Roster
void TeamRoster() {
    int choice;

    printf("\nTeam Roster:\n");
    printf("1. View Team Roster\n2. Add Player\n3. Delete Player\n4. Search Player\n");
    printf("Enter the number of your preference: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid Input - Please enter a valid number.\n");
        return;
    }

    switch(choice) {
        case 1: viewTeamRoster(); break;
        case 2: addPlayer(); break;
        case 3: deletePlayer(); break;
        case 4: searchPlayer(); break;
        default: printf("Invalid Input - Please enter a valid operation number.\n");
    }
}

// Function to view Team Roster
void viewTeamRoster() {
    ensureFileExists(teamRosterFilename);

    FILE *file = fopen(teamRosterFilename, "r");
    if (file == NULL) {
        perror("Error opening team roster file for reading");
        return;
    }

    char line[256];
    printf("\n%-5s %-10s %-3s\n", "No.", "Name", "Pos");
    printf("------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    printf("------------------------\n");
    printf("End of Team Roster.\n");
}

// Function to add a player to the roster
void addPlayer() {
    ensureFileExists(teamRosterFilename);

    FILE *file = fopen(teamRosterFilename, "a");
    if (file == NULL) {
        perror("Error opening team roster file for writing");
        return;
    }

    char name[50], position[3];
    printf("Enter player name: ");
    scanf("%s", name);
    printf("Enter player position (e.g., PG, SG, SF, PF, C): ");
    scanf("%s", position);

    fprintf(file, "%d) %s - %s\n", getNextPlayerNumber(), name, position);

    fclose(file);
    printf("Player added successfully.\n");
}

// Function to delete a player from the roster
void deletePlayer() {
    ensureFileExists(teamRosterFilename);

    FILE *file = fopen(teamRosterFilename, "r");
    if (file == NULL) {
        perror("Error opening team roster file for reading");
        return;
    }

    FILE *tempFile = fopen("temp_roster.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temporary file for writing");
        fclose(file);
        return;
    }

    char line[256];
    int playerNumber;
    printf("Enter the number of the player to delete: ");
    if (scanf("%d", &playerNumber) != 1) {
        printf("Invalid Input.\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        int currentNumber;
        sscanf(line, "%d)", &currentNumber);
        if (currentNumber != playerNumber) {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(teamRosterFilename);
    rename("temp_roster.txt", teamRosterFilename);
    printf("Player deleted successfully.\n");
}

// Function to search players by position
void searchPlayer() {
    ensureFileExists(teamRosterFilename);

    FILE *file = fopen(teamRosterFilename, "r");
    if (file == NULL) {
        perror("Error opening team roster file for reading");
        return;
    }

    char position[3];
    printf("Enter the position to search for (e.g., PG, SG, SF, PF, C): ");
    scanf("%s", position);

    char line[256];
    int found = 0;
    printf("\nPlayers with position %s:\n", position);
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, position) != NULL) {
            printf("%s", line);
            found = 1;
        }
    }

    if (!found) {
        printf("No players found with position %s.\n", position);
    }

    fclose(file);
}

// Function to handle Player Stats menu
void PlayerStats() {
    int choice;

    printf("\nPlayer Stats:\n");
    printf("1. View Player Stats\n2. Add Player Stats\n3. Delete Player Stats\n4. Update Player Stats\n");
    printf("Enter the number of your preference: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid Input - Please enter a valid number.\n");
        return;
    }

    switch(choice) {
        case 1: viewPlayerStats(); break;
        case 2: addPlayerStats(); break;
        case 3: deletePlayerStats(); break;
        case 4: updatePlayerStats(); break;  // Call the Update Player Stats function
        default: printf("Invalid Input - Please enter a valid operation number.\n");
    }
}

// Function to view Player Stats
void viewPlayerStats() {
    FILE *file = fopen(statsFilename, "r");
    if (file == NULL) {
        printf("Error opening player stats file.\n");
        return;
    }

    printf("\nNo.\tName\tPos\tPTS\tREB\tAST\tBLK\tTO\n");
    printf("--------------------------------------------------------------\n");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);

    printf("\nEnd of Player Stats.\n");
    
    getchar();  // Wait for the user to press a key before returning to the main menu
}

// Function to add Player Stats
void addPlayerStats() {
    ensureFileExists(statsFilename);

    FILE *file = fopen(statsFilename, "a");
    if (file == NULL) {
        perror("Error opening player stats file for writing");
        return;
    }

    char name[50], position[3];
    int points, rebounds, assists, blocks, turnovers;

    printf("Enter player name: ");
    scanf("%s", name);
    printf("Enter player position (e.g., PG, SG, SF, PF, C): ");
    scanf("%s", position);
    printf("Enter average points per game: ");
    scanf("%d", &points);
    printf("Enter average rebounds per game: ");
    scanf("%d", &rebounds);
    printf("Enter average assists per game: ");
    scanf("%d", &assists);
    printf("Enter average blocks per game: ");
    scanf("%d", &blocks);
    printf("Enter average turnovers per game: ");
    scanf("%d", &turnovers);

    fprintf(file, "%d) %s - %s - PTS: %d, REB: %d, AST: %d, BLK: %d, TO: %d\n",
            getNextPlayerStatNumber(), name, position, points, rebounds, assists, blocks, turnovers);

    fclose(file);
    printf("Player stats added successfully.\n");
}

// Function to delete Player Stats
void deletePlayerStats() {
    ensureFileExists(statsFilename);

    FILE *file = fopen(statsFilename, "r");
    if (file == NULL) {
        perror("Error opening player stats file for reading");
        return;
    }

    FILE *tempFile = fopen("temp_stats.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temporary file for writing");
        fclose(file);
        return;
    }

    int playerNumber;
    char line[256];
    printf("Enter the number of the player stats to delete: ");
    if (scanf("%d", &playerNumber) != 1) {
        printf("Invalid Input.\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        int currentNumber;
        sscanf(line, "%d)", &currentNumber);
        if (currentNumber != playerNumber) {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(statsFilename);
    rename("temp_stats.txt", statsFilename);
    printf("Player stats deleted successfully.\n");
}

// Function to update Player Stats
void updatePlayerStats() {
    ensureFileExists(statsFilename);

    FILE *file = fopen(statsFilename, "r");
    if (file == NULL) {
        perror("Error opening player stats file for reading");
        return;
    }

    FILE *tempFile = fopen("temp_stats.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temporary file for writing");
        fclose(file);
        return;
    }

    int playerNumber;
    printf("Enter the number of the player stats to update: ");
    if (scanf("%d", &playerNumber) != 1) {
        printf("Invalid Input.\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    char name[50], position[3];
    int points, rebounds, assists, blocks, turnovers;
    int found = 0;
    char line[256];  // Declare 'line' variable here

    while (fgets(line, sizeof(line), file)) {
        int currentNumber;
        sscanf(line, "%d)", &currentNumber);
        if (currentNumber == playerNumber) {
            printf("Updating stats for player number %d:\n", playerNumber);
            printf("Enter player name: ");
            scanf("%s", name);
            printf("Enter player position (e.g., PG, SG, SF, PF, C): ");
            scanf("%s", position);
            printf("Enter average points per game: ");
            scanf("%d", &points);
            printf("Enter average rebounds per game: ");
            scanf("%d", &rebounds);
            printf("Enter average assists per game: ");
            scanf("%d", &assists);
            printf("Enter average blocks per game: ");
            scanf("%d", &blocks);
            printf("Enter average turnovers per game: ");
            scanf("%d", &turnovers);

            fprintf(tempFile, "%d) %s - %s - PTS: %d, REB: %d, AST: %d, BLK: %d, TO: %d\n",
                    playerNumber, name, position, points, rebounds, assists, blocks, turnovers);

            found = 1;
        } else {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(statsFilename);
    rename("temp_stats.txt", statsFilename);

    if (found) {
        printf("Player stats updated successfully.\n");
    } else {
        printf("Player number %d not found.\n", playerNumber);
    }
}

// Function to manage Coaches Roster
void CoachesRoster() {
    int choice;

    printf("\nCoaches Roster:\n");
    printf("1. View Coaches Roster\n2. Add Coach\n3. Delete Coach\n");
    printf("Enter the number of your preference: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid Input - Please enter a valid number.\n");
        return;
    }

    switch(choice) {
        case 1: viewCoachesRoster(); break;
        case 2: addCoach(); break;
        case 3: deleteCoach(); break;
        default: printf("Invalid Input - Please enter a valid operation number.\n");
    }
}

// Function to view Coaches Roster
void viewCoachesRoster() {
    ensureFileExists(coachesRosterFilename);

    FILE *file = fopen(coachesRosterFilename, "r");
    if (file == NULL) {
        perror("Error opening coaches roster file for reading");
        return;
    }

    printf("\nNo.\tName\tField\tExperience (Years)\n");
    printf("--------------------------------------------------------------\n");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    printf("--------------------------------------------------------------\n");
    printf("End of Coaches Roster.\n");
}

// Function to add a coach to the roster
void addCoach() {
    ensureFileExists(coachesRosterFilename);

    FILE *file = fopen(coachesRosterFilename, "a");
    if (file == NULL) {
        perror("Error opening coaches roster file for writing");
        return;
    }

    char name[50], field[50];
    int experience;

    printf("Enter coach name: ");
    scanf("%s", name);
    printf("Enter coach field (e.g., Offense, Defense, Special Teams): ");
    scanf("%s", field);
    printf("Enter years of experience: ");
    scanf("%d", &experience);

    fprintf(file, "%d) %s - %s - %d years\n", getNextCoachNumber(), name, field, experience);

    fclose(file);
    printf("Coach added successfully.\n");
}

// Function to delete a coach from the roster
void deleteCoach() {
    ensureFileExists(coachesRosterFilename);

    FILE *file = fopen(coachesRosterFilename, "r");
    if (file == NULL) {
        perror("Error opening coaches roster file for reading");
        return;
    }

    FILE *tempFile = fopen("temp_coaches.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temporary file for writing");
        fclose(file);
        return;
    }

    int coachNumber;
    printf("Enter the number of the coach to delete: ");
    if (scanf("%d", &coachNumber) != 1) {
        printf("Invalid Input.\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int currentNumber;
        sscanf(line, "%d)", &currentNumber);
        if (currentNumber != coachNumber) {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(coachesRosterFilename);
    rename("temp_coaches.txt", coachesRosterFilename);
    printf("Coach deleted successfully.\n");
}

// Function to handle Equipment Inventory
void EquipmentInventory() {
    int choice;

    printf("\nEquipment Inventory:\n");
    printf("1. View Equipment Inventory\n2. Add Equipment\n3. Delete Equipment\n4. Search Equipment\n");
    printf("Enter the number of your preference: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid Input - Please enter a valid number.\n");
        return;
    }

    switch(choice) {
        case 1: viewEquipmentInventory(); break;
        case 2: addEquipment(); break;
        case 3: deleteEquipment(); break;
        case 4: searchEquipment(); break;
        default: printf("Invalid Input - Please enter a valid operation number.\n");
    }
}

// Function to view Equipment Inventory
void viewEquipmentInventory() {
    ensureFileExists(equipmentInventoryFilename);

    FILE *file = fopen(equipmentInventoryFilename, "r");
    if (file == NULL) {
        perror("Error opening equipment inventory file for reading");
        return;
    }

    printf("\nNo.\tItem\tStock\n");
    printf("--------------------------------------------------------------\n");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    printf("--------------------------------------------------------------\n");
    printf("End of Equipment Inventory.\n");
}

// Function to add Equipment to the inventory
void addEquipment() {
    ensureFileExists(equipmentInventoryFilename);

    FILE *file = fopen(equipmentInventoryFilename, "a");
    if (file == NULL) {
        perror("Error opening equipment inventory file for writing");
        return;
    }

    char item[50];
    int stock;

    printf("Enter equipment item: ");
    scanf("%s", item);
    printf("Enter stock quantity: ");
    scanf("%d", &stock);

    fprintf(file, "%d) %s - %d in stock\n", getNextEquipmentNumber(), item, stock);

    fclose(file);
    printf("Equipment added successfully.\n");
}

// Function to delete Equipment from the inventory
void deleteEquipment() {
    ensureFileExists(equipmentInventoryFilename);

    FILE *file = fopen(equipmentInventoryFilename, "r");
    if (file == NULL) {
        perror("Error opening equipment inventory file for reading");
        return;
    }

    FILE *tempFile = fopen("temp_inventory.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temporary file for writing");
        fclose(file);
        return;
    }

    int itemNumber;
    printf("Enter the number of the equipment to delete: ");
    if (scanf("%d", &itemNumber) != 1) {
        printf("Invalid Input.\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int currentNumber;
        sscanf(line, "%d)", &currentNumber);
        if (currentNumber != itemNumber) {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(equipmentInventoryFilename);
    rename("temp_inventory.txt", equipmentInventoryFilename);
    printf("Equipment deleted successfully.\n");
}

// Function to search for equipment by name
void searchEquipment() {
    ensureFileExists(equipmentInventoryFilename);

    FILE *file = fopen(equipmentInventoryFilename, "r");
    if (file == NULL) {
        perror("Error opening equipment inventory file for reading");
        return;
    }

    char item[50];
    printf("Enter the item name to search for: ");
    scanf("%s", item);

    char line[256];
    int found = 0;
    printf("\nEquipment matching '%s':\n", item);
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, item) != NULL) {
            printf("%s", line);
            found = 1;
        }
    }

    if (!found) {
        printf("No equipment found with the name '%s'.\n", item);
    }

    fclose(file);
}

// Function to ensure a file exists; creates it if it does not
void ensureFileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        file = fopen(filename, "w");
        if (file != NULL) {
            fclose(file);
        }
    } else {
        fclose(file);
    }
}

// Function to get the next player number for roster
int getNextPlayerNumber() {
    FILE *file = fopen(teamRosterFilename, "r");
    if (file == NULL) {
        return 1;
    }

    int number = 1;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int currentNumber;
        sscanf(line, "%d)", &currentNumber);
        if (currentNumber >= number) {
            number = currentNumber + 1;
        }
    }

    fclose(file);
    return number;
}

// Function to get the next player stat number
int getNextPlayerStatNumber() {
    FILE *file = fopen(statsFilename, "r");
    if (file == NULL) {
        return 1;
    }

    int number = 1;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int currentNumber;
        sscanf(line, "%d)", &currentNumber);
        if (currentNumber >= number) {
            number = currentNumber + 1;
        }
    }

    fclose(file);
    return number;
}

// Function to get the next coach number
int getNextCoachNumber() {
    FILE *file = fopen(coachesRosterFilename, "r");
    if (file == NULL) {
        return 1;
    }

    int number = 1;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int currentNumber;
        sscanf(line, "%d)", &currentNumber);
        if (currentNumber >= number) {
            number = currentNumber + 1;
        }
    }

    fclose(file);
    return number;
}

// Function to get the next equipment number
int getNextEquipmentNumber() {
    FILE *file = fopen(equipmentInventoryFilename, "r");
    if (file == NULL) {
        return 1;
    }

    int number = 1;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int currentNumber;
        sscanf(line, "%d)", &currentNumber);
        if (currentNumber >= number) {
            number = currentNumber + 1;
        }
    }

    fclose(file);
    return number;
}

// Main function
int main() {
    while (1) {
        mainMenu();
    }
    return 0;
}

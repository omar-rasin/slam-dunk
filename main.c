#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *teamRosterFilename = "team_roster.txt";
const char *statsFilename = "player_stats.txt";

// Function prototypes
void mainMenu();
void TeamRoster();
void viewTeamRoster();
void addPlayer();
void deletePlayer();
void PlayerStats();
void viewPlayerStats();
void addPlayerStats();
void deletePlayerStats();
void ensureFileExists(const char *filename);
int getNextPlayerNumber();
int getNextPlayerStatNumber();

// Main Menu Function
void mainMenu() {
    int choice;

    printf("\n*WELCOME TO SLAM-DUNK BASKETBALL CLUB!*\n\n"); 
    printf("MAIN MENU:\n"); 
    printf("1. Team Roster\n2. Player Stats\n3. Coaches Roster\n4. Equipment Inventory\n5. Financial Records\n\n");
    printf("Enter the number of your preference: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid Input - Please enter a valid number.\n");
        return;
    }

    switch(choice) {
        case 1: TeamRoster(); break;
        case 2: PlayerStats(); break;
        case 3: /* Function to handle Coaches Roster */ break;
        case 4: /* Function to handle Equipment Inventory */ break;
        case 5: /* Function to handle Financial Records */ break;
        default: printf("Invalid Input - Please enter a valid operation number.\n");
    }
}

// Function to manage Team Roster
void TeamRoster() {
    int choice;

    printf("\nTeam Roster:\n");
    printf("1. View Team Roster\n2. Add Player\n3. Delete Player\n");
    printf("Enter the number of your preference: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid Input - Please enter a valid number.\n");
        return;
    }

    switch(choice) {
        case 1: viewTeamRoster(); break;
        case 2: addPlayer(); break;
        case 3: deletePlayer(); break;
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

// Get the next player number based on the file contents
int getNextPlayerNumber() {
    FILE *file = fopen(teamRosterFilename, "r");
    if (file == NULL) {
        return 1; // Start from 1 if file does not exist
    }

    int maxNumber = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int number;
        sscanf(line, "%d)", &number);
        if (number > maxNumber) {
            maxNumber = number;
        }
    }

    fclose(file);
    return maxNumber + 1;
}

// Function to manage Player Stats
void PlayerStats() {
    int choice;

    printf("\nPlayer Stats:\n");
    printf("1. View Player Stats\n2. Add Player Stats\n3. Delete Player Stats\n");
    printf("Enter the number of your preference: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid Input - Please enter a valid number.\n");
        return;
    }

    switch(choice) {
        case 1: viewPlayerStats(); break;
        case 2: addPlayerStats(); break;
        case 3: deletePlayerStats(); break;
        default: printf("Invalid Input - Please enter a valid operation number.\n");
    }
}

// Function to view player stats in an organized manner
void viewPlayerStats() {
    ensureFileExists(statsFilename); // Ensure file exists before opening it
    
    FILE *file = fopen(statsFilename, "r");
    if (file == NULL) {
        perror("Error opening player stats file for reading");
        return;
    }

    char line[256];
    printf("\n%-5s %-10s %-3s %-28s %-28s %-28s %-28s %-28s\n", 
           "No.", "Name", "Pos", "Avg Points/Game", "Avg Rebounds/Game", 
           "Avg Assists/Game", "Avg Blocks/Game", "Avg Turnovers/Game");
    printf("--------------------------------------------------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        char name[50], position[3];
        int playerNumber;
        float avgPoints, avgRebounds, avgAssists, avgBlocks, avgTurnovers;

        // Parse the line for player details
        sscanf(line, "%d) %s - %s - Average points per game : %f , Average rebounds per game : %f , Average assists per game : %f , Average blocks per game : %f , Average turnovers per game : %f",
               &playerNumber, name, position, &avgPoints, &avgRebounds, &avgAssists, &avgBlocks, &avgTurnovers);

        // Print each player’s stats in an organized way
        printf("%-5d %-10s %-3s %-28.2f %-28.2f %-28.2f %-28.2f %-28.2f\n",
               playerNumber, name, position, avgPoints, avgRebounds, 
               avgAssists, avgBlocks, avgTurnovers);
    }

    fclose(file);
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    printf("End of Player Stats.\n");
}

// Function to add player stats
void addPlayerStats() {
    ensureFileExists(statsFilename);

    FILE *file = fopen(statsFilename, "a");
    if (file == NULL) {
        perror("Error opening player stats file for writing");
        return;
    }

    char name[50], position[3];
    float avgPoints, avgRebounds, avgAssists, avgBlocks, avgTurnovers;
    
    printf("Enter player name: ");
    scanf("%s", name);
    printf("Enter player position (e.g., PG, SG, SF, PF, C): ");
    scanf("%s", position);
    printf("Enter average points per game: ");
    scanf("%f", &avgPoints);
    printf("Enter average rebounds per game: ");
    scanf("%f", &avgRebounds);
    printf("Enter average assists per game: ");
    scanf("%f", &avgAssists);
    printf("Enter average blocks per game: ");
    scanf("%f", &avgBlocks);
    printf("Enter average turnovers per game: ");
    scanf("%f", &avgTurnovers);

    fprintf(file, "%d) %s - %s - Average points per game : %.2f , Average rebounds per game : %.2f , Average assists per game : %.2f , Average blocks per game : %.2f , Average turnovers per game : %.2f\n", 
            getNextPlayerStatNumber(), name, position, avgPoints, avgRebounds, avgAssists, avgBlocks, avgTurnovers);

    fclose(file);
    printf("Player stats added successfully.\n");
}

// Function to delete player stats
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

    char line[256];
    int playerNumber;
    printf("Enter the number of the player to delete stats: ");
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

// Get the next player stat number based on the file contents
int getNextPlayerStatNumber() {
    FILE *file = fopen(statsFilename, "r");
    if (file == NULL) {
        return 1; // Start from 1 if file does not exist
    }

    int maxNumber = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int number;
        sscanf(line, "%d)", &number);
        if (number > maxNumber) {
            maxNumber = number;
        }
    }

    fclose(file);
    return maxNumber + 1;
}

// Function to ensure a file exists, creating it if necessary
void ensureFileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        file = fopen(filename, "w"); // Create the file if it does not exist
    }
    if (file != NULL) {
        fclose(file);
    }
}

int main() {
    mainMenu();
    return 0;
}
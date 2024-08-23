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
void searchPlayer();
void PlayerStats();  // Function prototype for PlayerStats
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
        case 2: PlayerStats(); break;  // Call the PlayerStats function
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

// Get the next player number based on the file contents
int getNextPlayerNumber() {
    FILE *file = fopen(teamRosterFilename, "r");
    if (file == NULL) {
        return 1; // Start from 1 if file does not exist
    }

    int maxNumber = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int currentNumber;
        sscanf(line, "%d)", &currentNumber);
        if (currentNumber > maxNumber) {
            maxNumber = currentNumber;
        }
    }

    fclose(file);
    return maxNumber + 1;
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
        int currentNumber;
        sscanf(line, "%d)", &currentNumber);
        if (currentNumber > maxNumber) {
            maxNumber = currentNumber;
        }
    }

    fclose(file);
    return maxNumber + 1;
}

// Ensure that the file exists before trying to read or write
void ensureFileExists(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file != NULL) {
        fclose(file);
    }
}

int main() {
    while (1) {
        mainMenu();
    }
    return 0;
}
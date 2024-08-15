#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<float.h>

int main() {

    printf("\n");
    
    printf("WELCOME TO SLAM-DUNK BASKETBALL CLUB!\n\n"); 
    
    printf("MAIN MENU:\n");

    int choice;
    printf("1.Team Roster\n2.Player Information\n3.Player Stats\n4.Coaches Roster\n5.Equipment Inventory\n6.Financial Records\n\n");
    printf("Please Enter the number of your choice: ");
    scanf("%d", &choice);

    if(choice>=1 && choice<=6 ) {

        printf("\n");
        printf("What Operation would you like to perform?\n\n");
        printf("1.View Records\n2.Add and Create new Records\n3.Delete Existing Records\n4.Search records based off criteria\n\n");

        int preference;
        printf("Enter the number of your preference: ");
        scanf("%d", &preference);

    }else {
        
        printf("Invalid number of choice inputted - Please try again");
    }

    return 0;
}

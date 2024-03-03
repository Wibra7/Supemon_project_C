#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for Supémons
typedef struct {
    char name[20];
    int hp;
    int attack;
    int defense;
    int evasion;
    int accuracy;
    int speed;
    char moves[4][20];
} Supemon;

// Define a structure for the Player
typedef struct {
    char name[50];
    Supemon supemons[3]; // Assuming the player can have up to 3 Supémons for this example
    int supocoins;
    int items[10]; // Placeholder for item inventory
} Player;

// Function prototypes
void showWelcomeScreen();
void chooseStarterSupemon(Player *player);


void mainMenu(Player *player);
void goIntoTheWild(Player *player);
void visitShop(Player *player);
void visitSupemonCenter(Player *player);
void leaveGame(Player *player, int saveGame);



void mainMenu(Player *player) {
    int choice;

    while(1) {
        printf("\nWhat would you like to do?\n");
        printf("1 - Into the Wild\n");
        printf("2 - Shop\n");
        printf("3 - Supémon Center\n");
        printf("4 - Leave the Game\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character after scanf

        switch(choice) {
            case 1:
                goIntoTheWild(player);
                break;
            case 2:
                visitShop(player);
                break;
            case 3:
                visitSupemonCenter(player);
                break;
            case 4:
                printf("Do you want to save your game before leaving? (1 for Yes, 0 for No): ");
                scanf("%d", &choice);
                leaveGame(player, choice);
                return; // Exit the main menu loop and the game
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    }
}



// Main function
int main() {
    Player player = { "", {{0}}, 0, {0} }; // Initialize the player with empty data

    showWelcomeScreen();
    chooseStarterSupemon(&player);
    mainMenu(&player); // Call the main menu after the player chooses a starter Supémon

    return 0;
}

// Implement the Welcome Screen
void showWelcomeScreen() {
    printf("Hello! Welcome to Supémon World!\n");
    printf("Please enter your name: ");
}

// Modified function to greet the player with their name and let them choose their starter Supémon
void chooseStarterSupemon(Player *player) {
    int choice;
    char playerName[50];
    
    fgets(playerName, 50, stdin); // Reading player name with fgets to handle spaces
    playerName[strcspn(playerName, "\n")] = 0; // Remove trailing newline character
    strcpy(player->name, playerName); // Copy the input to the player's name

    // Personalized greeting using the player's name
    printf("Hello %s! Welcome to Supémon World!\n", player->name);

    printf("Choose your starter Supémon:\n");
    printf("1 - Supmander\n");
    printf("2 - Supasaur\n");
    printf("3 - Supirtle\n");
    printf("Enter 1, 2 or 3: ");
    scanf("%d", &choice);
    // Assuming there's additional code here to handle the choice
}

// More functions and game logic would follow...
void goIntoTheWild(Player *player) {
    printf("\nYou venture into the wild...\n");
    // Implement the logic for random encounters here
}

void visitShop(Player *player) {
    printf("\nYou enter the shop...\n");
    // Implement the logic for buying or selling items here
}

void visitSupemonCenter(Player *player) {
    printf("\nYou visit the Supémon Center. Your Supémons are healed!\n");
    // Implement the logic for healing Supémons here
}

void leaveGame(Player *player, int saveGame) {
    if (saveGame) {
        printf("\nSaving game...\n");
        // Implement the logic for saving the game here
    }
    printf("Goodbye!\n");
    exit(0); // Exit the program
}
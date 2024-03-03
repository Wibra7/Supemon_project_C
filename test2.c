// Define a structure for Moves
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Item IDs for easy reference
#define POTION 0
#define SUPER_POTION 1
#define RARE_CANDY 2

// Define the prices for the items
#define PRICE_POTION 100
#define PRICE_SUPER_POTION 300
#define PRICE_RARE_CANDY 700

typedef struct {
    char name[20];
    int damage;
    int statChange;
    char affectedStat[10];
} Move;


typedef struct {
    char name[20];
    int level;
    int experience;
    int hp;
    int maxHp;
    int attack;
    int baseAttack;
    int defense;
    int baseDefense;
    int evasion;
    int baseEvasion;
    int accuracy;
    int baseAccuracy;
    int speed;
    Move moves[2];
} Supemon;

// Define a structure for the Player
typedef struct {
    char name[50];
    Supemon supemons[3]; // Assuming the player can have up to 3 Supémons
    int supocoins;
    Supemon *selectedSupemon; // Pointer to the currently selected fighting Supémon
    // Assuming a simple list of items as an array of integers for their IDs
    int items[10]; // Placeholder for item inventory
} Player;


void printHeader(const char* header) {
    int len = strlen(header);
    printf("+"); // Starting border
    for (int i = 0; i < len + 2; i++) { // +2 for padding
        printf("-"); // Top border
    }
    printf("+\n"); // Ending border
    printf("| %s |\n", header); // Padded header text
    printf("+"); // Starting bottom border
    for (int i = 0; i < len + 2; i++) { // +2 for padding
        printf("-"); // Bottom border
    }
    printf("+\n"); // Ending bottom border
}



// Initialize Supémons with their respective stats and moves
void initializeSupemons(Supemon *supmander, Supemon *supasaur, Supemon *supirtle) {
    // Initialize Supmander
    strcpy(supmander->name, "Supmander");
    supmander->hp = supmander->maxHp = 10;
    supmander->attack = supmander->baseAttack = 1;
    supmander->defense = supmander->baseDefense = 1;
    supmander->evasion = supmander->baseEvasion = 1;
    supmander->accuracy = supmander->baseAccuracy = 2;
    supmander->speed = 1;
    strcpy(supmander->moves[0].name, "Scratch");
    supmander->moves[0].damage = 3;
    strcpy(supmander->moves[1].name, "Grawl");
    supmander->moves[1].statChange = 1;
    strcpy(supmander->moves[1].affectedStat, "Attack");

    strcpy(supasaur->name, "Supasaur");
    supasaur->hp = supasaur->maxHp = 9;
    supasaur->attack = supasaur->baseAttack = 1;
    supasaur->defense = supasaur->baseDefense = 2;
    supasaur->evasion = supasaur->baseEvasion = 2;
    supasaur->accuracy = supasaur->baseAccuracy = 1;
    supasaur->speed = 2;
    strcpy(supasaur->moves[0].name, "Pound");
    supasaur->moves[0].damage = 2;
    strcpy(supasaur->moves[1].name, "Foliage");
    supasaur->moves[1].statChange = 1;
    strcpy(supasaur->moves[1].affectedStat, "Evasion");

    strcpy(supirtle->name, "Supirtle");
    supirtle->hp = supirtle->maxHp = 11;
    supirtle->attack = supirtle->baseAttack = 2;
    supirtle->defense = supirtle->baseDefense = 2;
    supirtle->evasion = supirtle->baseEvasion = 2;
    supirtle->accuracy = supirtle->baseAccuracy = 1;
    supirtle->speed = 2;
    strcpy(supirtle->moves[0].name, "Pound");
    supirtle->moves[0].damage = 2;
    strcpy(supirtle->moves[1].name, "Shell");
    supirtle->moves[1].statChange = 1;
    strcpy(supirtle->moves[1].affectedStat, "Defense");
}

// Function prototypes//////////////////////////////////////////////////////////////////////////////////////
void showWelcomeScreen();
void initializeSupemons(Supemon *supmander, Supemon *supasaur, Supemon *supirtle);

void mainMenu(Player *player);
void goIntoTheWild(Player *player);
void visitShop(Player *player);
void visitSupemonCenter(Player *player);
void leaveGame(Player *player, int saveGame);

void initializeSupemons(Supemon *supmander, Supemon *supasaur, Supemon *supirtle);

// Main/////////////////////////////////////////////////

int main() {
    Player player = { "", {{0}}, 300, {0}, NULL }; // Initialize the player with empty data
    Supemon supmander, supasaur, supirtle;

    // Initialize the starter Supémons
    initializeSupemons(&supmander, &supasaur, &supirtle);

    showWelcomeScreen();
    chooseStarterSupemon(&player, &supmander, &supasaur, &supirtle);
    mainMenu(&player); // Call the main menu after the player chooses a starter Supémon

    return 0;
}

// More functions and game logic would follow...*************************************************************************

void showWelcomeScreen() {
    printf("Hello! Welcome to Supémon World!\n");
    printf("Please enter your name: ");
}


void goIntoTheWild(Player *player) {
    printf("\nYou venture into the wild...\n");
    // Implement the logic for random encounters here
}

// void visitShop(Player *player) {
//     printf("\nYou enter the shop...\n");
//     // Implement the logic for buying or selling items here
// }




void visitShop(Player *player) {
    
    int choice, quantity, itemToSell;
    printHeader("Welcome to the Supemon local shop!");
    printf("\tYou have %d Supocoins.\n", player->supocoins);
    

    while(1) {
        printf("\t1. Buy items\n");
        printf("\t2. Sell items\n");
        printf("\t3. Exit shop\n");
        printf("  Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Buying items
                printHeader("        Buying items       ");
                printf("You now have %d Supocoins.\n", player->supocoins);
                printf("   1. Potion: +5 HP (100 Supocoins)\n");
                printf("   2. Super Potion: +10 HP (300 Supocoins)\n");
                printf("   3. Rare Candy: Adds a level (700 Supocoins)\n");
                printf("Enter the item number you want to buy and the quantity (e.g., '1 3' to buy 3 potions): ");
                scanf("%d %d", &choice, &quantity);

                // Check for positive quantity
                if (quantity <= 0) {
                    printf("Invalid quantity. Please enter a positive number.\n");
                    break;
                }

                switch (choice) {
                    case 1: // Potion
                        if (player->supocoins >= PRICE_POTION * quantity) {
                            player->supocoins -= PRICE_POTION * quantity;
                            player->items[POTION] += quantity;
                            printf("You bought %d Potion(s).\n", quantity);
                        } else {
                            printf("Not enough Supocoins.\n");
                        }
                        break;
                    case 2: // Super Potion
                        if (player->supocoins >= PRICE_SUPER_POTION * quantity) {
                            player->supocoins -= PRICE_SUPER_POTION * quantity;
                            player->items[SUPER_POTION] += quantity;
                            printf("You bought %d Super Potion(s).\n", quantity);
                        } else {
                            printf("Not enough Supocoins.\n");
                        }
                        break;
                    case 3: // Rare Candy
                        if (player->supocoins >= PRICE_RARE_CANDY * quantity) {
                            player->supocoins -= PRICE_RARE_CANDY * quantity;
                            player->items[RARE_CANDY] += quantity;
                            printf("You bought %d Rare Candy(candies).\n", quantity);
                        } else {
                            printf("Not enough Supocoins.\n");
                        }
                        break;
                    default:
                        printf("Invalid item number.\n");
                }
                break;
            case 2: // Selling items
                printf("Enter the item number you want to sell (1:Potion 2:SuperPotion 3:RareCandy) and the quantity\n(e.g., '1 2' to sell 2 potions): ");
                scanf("%d %d", &itemToSell, &quantity);

                // Check for positive quantity
                if (quantity <= 0) {
                    printf("Invalid quantity. Please enter a positive number.\n");
                    break;
                }

                switch (itemToSell) {
                    case 1: // Potion
                        if (player->items[POTION] >= quantity) {
                            player->items[POTION] -= quantity;
                            player->supocoins += (PRICE_POTION / 2) * quantity;
                            printf("You sold %d Potion(s).\n", quantity);
                        } else {
                            printf("You do not have enough Potions to sell.\n");
                        }
                        break;
                    case 2: // Super Potion
                        if (player->items[SUPER_POTION] >= quantity) {
                            player->items[SUPER_POTION] -= quantity;
                            player->supocoins += (PRICE_SUPER_POTION / 2) * quantity;
                            printf("You sold %d Super Potion(s).\n", quantity);
                        } else {
                            printf("You do not have enough Super Potions to sell.\n");
                        }
                        break;
                    case 3: // Rare Candy
                        if (player->items[RARE_CANDY] >= quantity) {
                            player->items[RARE_CANDY] -= quantity;
                            player->supocoins += (PRICE_RARE_CANDY / 2) * quantity;
                            printf("You sold %d Rare Candy(candies).\n", quantity);
                        } else {
                            printf("You do not have enough Rare Candies to sell.\n");
                        }
                        break;
                    default:
                        printf("Invalid item number.\n");
                }
                break;
            case 3: // Exit shop
                printf("Thank you for visiting the shop!\n");
                return; // Exit the shop function
            default:
                printf("Invalid choice. Please enter a number between 1 and 3.\n");
                break;
        }

        // Display the player's updated Supocoins and inventory after each transaction
        printf("_____________________\n");
        printf("You now have %d Supocoins.\n", player->supocoins);
        printHeader("    Inventory    ");
        
        printf("Potions: %d\n", player->items[POTION]);
        printf("Super Potions: %d\n", player->items[SUPER_POTION]);
        printf("Rare Candies: %d\n", player->items[RARE_CANDY]);
        printf("_____________________\n");
        printHeader("Welcome to the Supemon shop local!");
    }
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


void chooseStarterSupemon(Player *player, Supemon *supmander, Supemon *supasaur, Supemon *supirtle) {
    int choice;
    char playerName[50];
    
    fgets(playerName, 50, stdin); // Reading player name with fgets to handle spaces
    playerName[strcspn(playerName, "\n")] = 0; // Remove trailing newline character
    strcpy(player->name, playerName); // Copy the input to the player's name

    printHeader("Choose your starter Supemon:");
    printf("\t1 - Supmander\n");
    printf("`\t2 - Supasaur\n");
    printf("\t3 - Supirtle\n");
    printf("Enter 1, 2 or 3: ");
    scanf("%d", &choice);

    // Assign the chosen Supémon to the player
    switch(choice) {
        case 1:
            player->supemons[0] = *supmander;
            break;
        case 2:
            player->supemons[0] = *supasaur;
            break;
        case 3:
            player->supemons[0] = *supirtle;
            break;
        default:
            printf("Invalid choice. Assigning default starter Supémon Supmander.\n");
            player->supemons[0] = *supmander;
            break;
    }
    player->selectedSupemon = &player->supemons[0]; // Set the selected Supémon to the first in the array
}

void mainMenu(Player *player) {
    int choice;

    while(1) {
        printHeader("Where do you want to go?");
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
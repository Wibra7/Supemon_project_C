#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

const char *moveNames[] = {"Scratch", "Grawl", "Pound", "Foliage", "Shell","Uppercut","Caillasse"};
const char *stats[] = {"Attack", "Defense", "Evasion", "Accuracy"};
const char *supemonPrefixes[] = {"Supa", "Hyper", "Mega", "Top"};
const char *supemonSuffixes[] = {"piaf", "coin-coin", "cabot", "minou", "clapiot","bourrin"};


// Define Item IDs for easy reference
#define POTION 0
#define SUPER_POTION 1
#define RARE_CANDY 2

// Define the prices for the items
#define PRICE_POTION 100
#define PRICE_SUPER_POTION 300
#define PRICE_RARE_CANDY 700

typedef enum {
    BATTLE_ONGOING,
    BATTLE_WON,
    BATTLE_LOST,
    BATTLE_RAN_AWAY
} BattleStatus;

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

typedef struct {
    char name[50];
    Supemon supemons[3];
    int supocoins;
    Supemon *selectedSupemon;
    int items[10];
} Player;

void printHeader(const char* header) {
    // Affiche *------------------------------------------*
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

// Initialize Supemons with their respective stats and moves


// Function prototypes//////////////////////////////////////////////////////////////////////////////////////
void showWelcomeScreen();
void initializeSupemons(Supemon *supmander, Supemon *supasaur, Supemon *supirtle);
bool tryToRunAway(Player *player, Supemon *enemySupemon);
void mainMenu(Player *player);
void goIntoTheWild(Player *player);
void visitShop(Player *player);
void visitSupemonCenter(Player *player);
void saveGame(Player *player);
void leaveGame(Player *player, int saveGame);
void chooseStarterSupemon(Player *player, Supemon *supmander, Supemon *supasaur, Supemon *supirtle);
void initializeSupemons(Supemon *supmander, Supemon *supasaur, Supemon *supirtle);
void generateEnemySupemon(Supemon *enemySupemon, Player *player);
void useItem(Player *player, Supemon *targetSupemon);
void changeSupemon(Player *player);
void executeMove(Supemon *attacker, Supemon *defender);
void printStatus(Supemon *playerSupemon, Supemon *enemySupemon,char *player_name);
bool tryToCapture(Player *player, Supemon *enemySupemon);
void usePotion(Player *player, Supemon *targetSupemon);
void useSuperPotion(Player *player, Supemon *targetSupemon);
void useRareCandy(Player *player, Supemon *targetSupemon);
void addSupemonToPlayer(Player *player, Supemon *capturedSupemon);
BattleStatus playerMove(Player *player, Supemon *enemySupemon);
void executeEnemyMove(Supemon *enemy, Supemon *playerSupemon);
void levelUp(Supemon *supemon);
void goIntoTheWild(Player *player);
int increaseStat(int stat);
void levelUp(Supemon *supemon);
void addExperience(Supemon *supemon, int exp);

// Main/////////////////////////////////////////////////

int main() {
    Player player = { "", {{0}}, 300, 0, {0} }; // Initialize the player with empty data
    Supemon supmander, supasaur, supirtle;

    // Initialize the starter Supemons
    initializeSupemons(&supmander, &supasaur, &supirtle);

    showWelcomeScreen();
    chooseStarterSupemon(&player, &supmander, &supasaur, &supirtle);
    mainMenu(&player); // Call the main menu after the player chooses a starter Supemon
    return 0;
}

// More functions and game logic will follow...*************************************************************************


void initializeSupemons(Supemon *supmander, Supemon *supasaur, Supemon *supirtle) {
    // Initialize Supmander
    strcpy(supmander->name, "Supmander");
    supmander->level = 1;
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
    supasaur->level = 1;
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
    supirtle->level = 1;
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

void showWelcomeScreen() {
    printHeader("**Hello! Welcome to Supemon World!**");
    printf("Please enter your name: ");
}

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
    int i, choice;

    // Welcome message
    printHeader("Welcome to the local Supemon Center");

    // List all Supemons and their current HP status
    printf("Which Supemon do you want to heal:\n");
    for (i = 0; i < 3; i++) {
        if (strlen(player->supemons[i].name) > 0) { // Check if the Supemon slot is used
            printf("%d - %s (HP: %d/%d)\n", i + 1, player->supemons[i].name, player->supemons[i].hp, player->supemons[i].maxHp);
        }
    }
    printf("4 - Heal all Supemons\n");
    printf("5 - Cancel\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice >= 1 && choice <= 3) {
        if (strlen(player->supemons[choice - 1].name) > 0) {
            player->supemons[choice - 1].hp = player->supemons[choice - 1].maxHp;
            printf("%s has been fully healed!\n", player->supemons[choice - 1].name);
        }
    } else if (choice == 4) {
        for (i = 0; i < 3; i++) {
            if (strlen(player->supemons[i].name) > 0) {
                player->supemons[i].hp = player->supemons[i].maxHp;
            }
        }
        printf("All your Supemons have been fully healed!\n");
    } else if (choice == 5) {
        printf("No Supemons were healed.\n");
    } else {
        printf("Invalid choice.\n");
    }

    printf("Goodbye!\n");
    printf("_____________________________________\n");

}

void saveGame(Player *player) {
    char fileName[64];

    // Create the file name based on the player's name
    snprintf(fileName, sizeof(fileName), "%s.txt", player->name);

    FILE *file = fopen(fileName, "w"); // Open the file in write mode
    if (file == NULL) {
        printf("Error opening save file!\n");
        return;
    }

    // Save player name and Supocoins
    fprintf(file, "Player Name: %s\n", player->name);
    fprintf(file, "Supocoins: %d\n", player->supocoins);

    // Save items
    fprintf(file, "Items:\n");
    fprintf(file, "Potion: %d\n", player->items[POTION]);
    fprintf(file, "Super Potion: %d\n", player->items[SUPER_POTION]);
    fprintf(file, "Rare Candy: %d\n", player->items[RARE_CANDY]);

    // Save Supemons
    fprintf(file, "Supemons:\n");
    for (int i = 0; i < 3; i++) {
        if (strlen(player->supemons[i].name) > 0) { // Check if the Supemon slot is used
            fprintf(file, "Name: %s, Level: %d, HP: %d/%d, Attack: %d, Defense: %d, Evasion: %d, Accuracy: %d, Speed: %d\n",
                    player->supemons[i].name,
                    player->supemons[i].level,
                    player->supemons[i].hp,
                    player->supemons[i].maxHp,
                    player->supemons[i].attack,
                    player->supemons[i].defense,
                    player->supemons[i].evasion,
                    player->supemons[i].accuracy,
                    player->supemons[i].speed);
        }
    }

    fclose(file); // Close the file
    printf("Game saved successfully to %s!\n", fileName);
}


void leaveGame(Player *player, int shouldSaveGame) {
    if (shouldSaveGame) {
        printf("\nSaving game...\n");
        saveGame(player); // Save the player's current game state
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

    // Assign the chosen Supemon to the player
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
            printf("Invalid choice. Assigning default starter Supemon Supmander.\n");
            player->supemons[0] = *supmander;
            break;
    }
    player->selectedSupemon = &player->supemons[0];
}

void mainMenu(Player *player) {
    int choice;

    while(1) {
        printHeader("Where do you want to go?");
        printf("1 - Into the Wild\n");
        printf("2 - Shop\n");
        printf("3 - Supemon Center\n");
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
                do {
                    printf("Do you want to save your game before leaving? (1 for Yes, 0 for No): ");
                    scanf("%d", &choice);
                    // Clear the input buffer to handle extra characters
                    while ((getchar()) != '\n');

                    if(choice != 1 && choice != 0) {
                        printf("Invalid choice. Please enter 1 for Yes or 0 for No.\n");
                    }
                } while(choice != 1 && choice != 0);

                leaveGame(player, choice);
                return; // Exit the main menu loop and the game
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    }
}

void randomMove(Move *move) {
    // Select a random move name from the pool
    strcpy(move->name, moveNames[rand() % (sizeof(moveNames) / sizeof(char*))]);
    // Random damage between 2 and 3
    move->damage = 2 + rand() % 2;
    // Random stat change between 1 and 2
    move->statChange = 1 + rand() % 2;
    // Select a random affected stat from the pool
    strcpy(move->affectedStat, stats[rand() % (sizeof(stats) / sizeof(char*))]);
}

void generateEnemySupemon(Supemon *enemySupemon, Player *player) {
    int base_level = player->selectedSupemon->level;

    // Select a random default Supemon name
    if (rand() % 2) {
        const char *defaultNames[] = {"Supmander", "Supasaur", "Supirtle"};
        strcpy(enemySupemon->name, defaultNames[rand() % 3]);
    } else {
        // Create a new Supemon name by combining a prefix and suffix
        strcpy(enemySupemon->name, supemonPrefixes[rand() % (sizeof(supemonPrefixes) / sizeof(char*))]);
        strcat(enemySupemon->name, supemonSuffixes[rand() % (sizeof(supemonSuffixes) / sizeof(char*))]);
    }

    enemySupemon->level = base_level;

    // Base stats for level 1
    int baseHp = 10;
    int baseAttack = 2;
    int baseDefense = 2;
    int baseEvasion = 1;
    int baseAccuracy = 1;
    int baseSpeed = 2;

    // Scale stats based on level
    for (int i = 1; i < base_level; ++i) {
        baseHp = increaseStat(baseHp);
        baseAttack = increaseStat(baseAttack);
        baseDefense = increaseStat(baseDefense);
        baseEvasion = increaseStat(baseEvasion);
        baseAccuracy = increaseStat(baseAccuracy);
        baseSpeed = increaseStat(baseSpeed);
    }

    // Assign the scaled stats
    enemySupemon->hp = enemySupemon->maxHp = baseHp;
    enemySupemon->attack = enemySupemon->baseAttack = baseAttack;
    enemySupemon->defense = enemySupemon->baseDefense = baseDefense;
    enemySupemon->evasion = enemySupemon->baseEvasion = baseEvasion;
    enemySupemon->accuracy = enemySupemon->baseAccuracy = baseAccuracy;
    enemySupemon->speed = baseSpeed;

    // Random moves
    randomMove(&enemySupemon->moves[0]);
    randomMove(&enemySupemon->moves[1]);
}


bool tryToRunAway(Player *player, Supemon *enemySupemon) {
    float playerSpeed = (float)player->selectedSupemon->speed;
    float enemySpeed = (float)enemySupemon->speed;
    float runAwayChance = playerSpeed / (playerSpeed + enemySpeed);

    // Generate a random number between 0 and 1
    float randomValue = (float)rand() / RAND_MAX;

    // Compare the random value to the run away chance
    if (randomValue < runAwayChance) {
        return true; // Successful escape
    } else {
        return false; // Failed escape
    }
}

bool tryToCapture(Player *player, Supemon *enemySupemon) {
    // Calculate the capture rate
    float captureRate = ((float)(enemySupemon->maxHp - enemySupemon->hp) / enemySupemon->maxHp) - 0.5f;

    // Ensure captureRate is not negative
    if (captureRate < 0) {
        captureRate = 0;
    }

    // Convert captureRate to a percentage chance, e.g., 0.2 -> 20%
    int chanceToCapture = (int)(captureRate * 100);

    // Generate a random number between 0 and 99
    int randomChance = rand() % 100;

    // Capture is successful if randomChance is less than or equal to chanceToCapture
    return randomChance <= chanceToCapture;
}

void printStatus(Supemon *playerSupemon, Supemon *enemySupemon,char *player_name) {
    printf("\n");
    printf("%s (Enemy)\n",enemySupemon->name);
    printf("HP: %d/%d  Lvl: %d  Atk: %d  Def: %d  Acc: %d  Eva: %d\n",
           enemySupemon->hp, enemySupemon->maxHp, enemySupemon->level, enemySupemon->attack,
           enemySupemon->defense, enemySupemon->accuracy, enemySupemon->evasion);
    printf("%s (%s)\n",playerSupemon->name,player_name);
    printf("HP: %d/%d  Lvl: %d  Atk: %d  Def: %d  Acc: %d  Eva: %d\n",
           playerSupemon->hp, playerSupemon->maxHp, playerSupemon->level, playerSupemon->attack,
           playerSupemon->defense, playerSupemon->accuracy, playerSupemon->evasion);
    printf("\n");
}

void executeMove(Supemon *attacker, Supemon *defender) {
    // Example implementation with just showing the moves and selecting them
    printf(" ->Choose a move\n");
    for (int i = 0; i < 2; i++) {
        printf(            "      %d - %s\n", i + 1, attacker->moves[i].name);
    }

    int moveChoice;
    scanf("%d", &moveChoice);
    getchar(); // consume the newline character

    // Assuming moveChoice is 1-indexed as per the prompt
    if (moveChoice < 1 || moveChoice > 2) {
        printf("Invalid move selected.\n");
        return;
    }

    Move selectedMove = attacker->moves[moveChoice - 1];
    printf("%s used %s!\n", attacker->name, selectedMove.name);

    defender->hp -= selectedMove.damage; // This is a simplified damage calculation
    printf("%s now has %d HP.\n", defender->name, defender->hp);
}

void changeSupemon(Player *player) {
    printf("Choose a Supemon to switch to:\n");
    for (int i = 0; i < 3; i++) {
        if (&player->supemons[i] != player->selectedSupemon) {
            printf("%d - %s (HP: %d/%d)\n", i + 1, player->supemons[i].name,
                   player->supemons[i].hp, player->supemons[i].maxHp);
        }
    }

    int supemonChoice;
    scanf("%d", &supemonChoice);
    getchar(); // consume the newline character

    if (supemonChoice < 1 || supemonChoice > 3 || &player->supemons[supemonChoice - 1] == player->selectedSupemon) {
        printf("Invalid choice.\n");
        return;
    }

    player->selectedSupemon = &player->supemons[supemonChoice - 1];
    printf("Go %s!\n", player->selectedSupemon->name);
}

void useItem(Player *player, Supemon *targetSupemon) {
    printf("Choose an item to use:\n");
    printf("1 - Potion (%d available)\n", player->items[POTION]);
    printf("2 - Super Potion (%d available)\n", player->items[SUPER_POTION]);
    printf("3 - Rare Candy (%d available)\n", player->items[RARE_CANDY]);

    int itemChoice;
    scanf("%d", &itemChoice);
    getchar(); // consume the newline character

    // Handle the item use
    switch (itemChoice) {
        case 1: // Potion
            // Assume usePotion function is implemented correctly
            usePotion(player, targetSupemon);
            break;
        case 2: // Super Potion
            // Assume useSuperPotion function is implemented correctly
            useSuperPotion(player, targetSupemon);
            break;
        case 3: // Rare Candy
            // Assume useRareCandy function is implemented correctly
            useRareCandy(player, targetSupemon);
            break;
        default:
            printf("Invalid item selected.\n");
            break;
    }
}

BattleStatus playerMove(Player *player, Supemon *enemySupemon) {
    printHeader("      What will you do now ?");
    printf("        1 - Move\n");
    printf("        2 - Change Supemon\n");
    printf("        3 - Use item\n");
    printf("        4 - Capture\n");
    printf("        5 - Run away\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // consume the newline character

    switch (choice) {
        case 1: // Move
            executeMove(player->selectedSupemon, enemySupemon);
            if (enemySupemon->hp <= 0) return BATTLE_WON;
            break;
        case 2: // Change Supemon
            changeSupemon(player);
            break;
        case 3: // Use item
            useItem(player, player->selectedSupemon);
            break;
        case 4: // Capture
            if (tryToCapture(player, enemySupemon)) {
                return BATTLE_WON;
            }
            printf("Capture attempt failed!\n");
            break;
        case 5: // Run away
            if (tryToRunAway(player, enemySupemon)) {
                printf("You successfully ran away!\n");
                return BATTLE_RAN_AWAY;
            }
            printf("You couldn't escape!\n");
            break;
        default:
            printf("Invalid choice. Please select an option from 1 to 5.\n");
            break;
    }

    return BATTLE_ONGOING; // Default return value if no other condition is met
}

void usePotion(Player *player, Supemon *targetSupemon) {
    if (player->items[POTION] > 0) {
        const int potionHealAmount = 5; // Define how much a potion heals
        targetSupemon->hp += potionHealAmount;
        if (targetSupemon->hp > targetSupemon->maxHp) {
            targetSupemon->hp = targetSupemon->maxHp; // Prevent overhealing
        }
        player->items[POTION]--; // Decrement the potion count
        printf("Used Potion on %s. %s's health is now %d/%d.\n",
               targetSupemon->name, targetSupemon->name, targetSupemon->hp, targetSupemon->maxHp);
    } else {
        printf("You don't have any Potions!\n");
    }
}

void useSuperPotion(Player *player, Supemon *targetSupemon) {
    if (player->items[SUPER_POTION] > 0) {
        const int superPotionHealAmount = 10; // Define how much a super potion heals
        targetSupemon->hp += superPotionHealAmount;
        if (targetSupemon->hp > targetSupemon->maxHp) {
            targetSupemon->hp = targetSupemon->maxHp; // Prevent overhealing
        }
        player->items[SUPER_POTION]--; // Decrement the super potion count
        printf("Used Super Potion on %s. %s's health is now %d/%d.\n",
               targetSupemon->name, targetSupemon->name, targetSupemon->hp, targetSupemon->maxHp);
    } else {
        printf("You don't have any Super Potions!\n");
    }
}

void useRareCandy(Player *player, Supemon *targetSupemon) {
    if (player->items[RARE_CANDY] > 0) {
        targetSupemon->level++; // Increment the Supemon's level
        player->items[RARE_CANDY]--; // Decrement the rare candy count
        // You could also increase the Supemon's stats here if that's part of your game mechanics
        printf("%s leveled up! %s is now level %d.\n", targetSupemon->name, targetSupemon->name, targetSupemon->level);
    } else {
        printf("You don't have any Rare Candies!\n");
    }
}

void addSupemonToPlayer(Player *player, Supemon *capturedSupemon) {
    // Logic to add the captured Supemon to the player's list of Supemons
    // Ensure there's an available slot, and copy the Supemon data over.
    for (int i = 0; i < 3; i++) {
        if (player->supemons[i].name[0] == '\0') { // Check if the name is empty, indicating an unused slot
            player->supemons[i] = *capturedSupemon; // Assign captured Supemon
            printf("%s has been added to your team!\n", capturedSupemon->name);
            return;
        }
    }
    printf("You have no room for more Supemons! Release one first.\n");
}

void executeEnemyMove(Supemon *enemy, Supemon *playerSupemon) {
    int moveIndex = rand() % 2; // Assuming the enemy Supemon has 2 moves
    Move enemyMove = enemy->moves[moveIndex];

    playerSupemon->hp -= enemyMove.damage; // Apply damage
    printf("%s uses %s against %s!\n", enemy->name, enemyMove.name, playerSupemon->name);
    printf("%s now has %d/%d HP.\n", playerSupemon->name, playerSupemon->hp, playerSupemon->maxHp);
}

void rewardPlayer(Player *player, Supemon *enemySupemon) {
    int rewardCoins = (rand() % (401)) + 100; // Random between 100 and 500
    int rewardExp = (rand() % (401)) + 100; // Random between 100 and 500
    rewardExp *= enemySupemon->level; // Multiply by enemy level
    player->supocoins += rewardCoins;
    addExperience(player->selectedSupemon, rewardExp);
    printf("You earned %d Supocoins and %s gained %d experience!\n", rewardCoins, player->selectedSupemon->name, rewardExp);
}

void goIntoTheWild(Player *player) {
    srand((unsigned int)time(NULL)); // Seed the random number generator
    if (player->selectedSupemon->hp <= 0) {
        printf("Selected pokemon has no hp\n");
        return; // Early return if the selected Supemon has no HP
    }

    Supemon enemySupemon;
    generateEnemySupemon(&enemySupemon,player); // Initializes enemySupemon
    printf("A wild %s has appeared\n", enemySupemon.name);
    printStatus(player->selectedSupemon, &enemySupemon,player->name);

    BattleStatus status = BATTLE_ONGOING;
    bool playerTurn = (player->selectedSupemon->speed > enemySupemon.speed) ||
                      (player->selectedSupemon->speed == enemySupemon.speed && (rand() % 2) == 0);

    while (status == BATTLE_ONGOING) {
        if (playerTurn) {
            status = playerMove(player, &enemySupemon);
            printf("______________________________________________\n");
        } else {
            executeEnemyMove(&enemySupemon, player->selectedSupemon);
            printf("______________________________________________\n");
            if (player->selectedSupemon->hp <= 0) {
                status = BATTLE_LOST;
            }
        }
        if (status == BATTLE_ONGOING) {
            playerTurn = !playerTurn; // Switch turns
        }
    }

    switch (status) {
        case BATTLE_WON:
            rewardPlayer(player, &enemySupemon);
            break;
        case BATTLE_LOST:
            printf("You lost the battle...\n");
            printf("___________________________________________\n");
            break;
        case BATTLE_RAN_AWAY:
            // Handled in playerMove
            break;

    }
}

int increaseStat(int stat) {
    float increase = stat * 0.3f;
    int roundedIncrease = (int)increase;

    // Simulate a 50% chance to round up if the increase is not an integer
    if (increase > (float)roundedIncrease) {
        // There's a 50% chance to round up
        if (rand() % 2) {
            roundedIncrease++;
        }
    }

    return stat + roundedIncrease;
}

void levelUp(Supemon *supemon) {
    supemon->level++;

    // Increase statistics by 30% and handle the 50% chance to round up or down if not an integer
    supemon->maxHp = increaseStat(supemon->maxHp);
    supemon->attack = increaseStat(supemon->attack);
    supemon->defense = increaseStat(supemon->defense);
    supemon->speed = increaseStat(supemon->speed);


    supemon->hp = supemon->maxHp;

    printf("%s grew to level %d!\n", supemon->name, supemon->level);
}

void addExperience(Supemon *supemon, int exp) {
    printf("%s gained %d experience points!\n", supemon->name, exp);
    supemon->experience += exp;

    // The experience needed for the next level increases by 1,000 points each level.
    // It starts at 500 for the first level and then increases by 1,000 each level after.
    int experienceToNextLevel = 500 + 1000 * (supemon->level - 1);

    // Check if the Supemon has enough experience to level up
    while (supemon->experience >= experienceToNextLevel) {
        supemon->experience -= experienceToNextLevel; // Subtract the experience for the next level
        levelUp(supemon); // Handle the level up process

        // Increase the threshold for the next level
        experienceToNextLevel += 1000;
    }
}
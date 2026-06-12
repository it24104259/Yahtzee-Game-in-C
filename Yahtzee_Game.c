#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h> 

#define NUM_DICE 5 
#define NUM_ROLLS 3 
#define NUM_ROUNDS 13
#define NUM_CATEGORIES 13 
#define NUM_SIDES 6  

// Function prototypes
void rollDice(); //Roll dice to generate values
void printDice(); //Print dice values
void chooseDiceToReroll(); //Choosing whether the dice needs to be rerolled or not
int calculateScore(); //Calculating the score according to the categories
void chooseCategoryAndScore();//Choosing a category 
void automatedPlayerTurn(); //Rolling automated players dice values
void playTurn();//Choosing which dice needs to be rerolled
void printScores();//printing scores 
int calculateTotalScore();//calculate the final score 
void findWinner();//deciding the winner

void rollDice(int dice[NUM_DICE], int toRoll[NUM_DICE]) {
    for (int i = 0; i < NUM_DICE; i++) {
        if (toRoll[i] == 1) {
            dice[i] = rand() % NUM_SIDES + 1;
        }
    }
} 

void printDice(int dice[NUM_DICE]) {
    printf("Dice: ");
    for (int i = 0; i < NUM_DICE; i++) {
        printf("%d ", dice[i]);
    }
    printf("\n");
}

void chooseDiceToReroll(int toRoll[NUM_DICE]) {
    printf("Enter 1 to re-roll and 0 to keep for each die:\n");
    for (int i = 0; i < NUM_DICE; i++) {
        printf("Die %d: ", i + 1);
        scanf("%d", &toRoll[i]);
    }
}

int calculateScore(int dice[NUM_DICE], int category) {
    int score = 0;
    int counts[NUM_SIDES + 1] = {0}; 

    for (int i = 0; i < NUM_DICE; i++) {
        counts[dice[i]]++;
    }

    switch (category) {
        case 1: score += counts[1] * 1; break; // Ones
        case 2: score += counts[2] * 2; break; // Twos
        case 3: score += counts[3] * 3; break; // Threes
        case 4: score += counts[4] * 4; break; // Fours
        case 5: score += counts[5] * 5; break; // Fives
        case 6: score += counts[6] * 6; break; // Sixes
        case 7: //Three of a kind
        {
    int ThreeOfTheSameKind = 0;
    int threeOfAKindValue = 0;

    // Check for a number that appears three times
    for (int i = 1; i <= NUM_SIDES; i++) {
        if (counts[i] == 3) {
            ThreeOfTheSameKind = 1;
            threeOfAKindValue = i;  // Store the value of the number that appears three times
            break;  // Exit the loop after finding the three-of-a-kind
        }
    }

    if (ThreeOfTheSameKind) {
        // The score for three of a kind: i * 3
        score = threeOfAKindValue * 3;

        // Add the sum of the remaining dice
        for (int j = 0; j < NUM_DICE; j++) {
            if (dice[j] != threeOfAKindValue) {
                score += dice[j];  // Add all dice except the three matching dice
            }
        }
    }
    break;
}

        case 8: //Four of a kind
        {
    int FourOfTheSameKind = 0;
    int fourOfAKindValue = 0;

    // Check for a number that appears exactly four times
    for (int i = 1; i <= NUM_SIDES; i++) {
        if (counts[i] == 4) {
            FourOfTheSameKind = 1;
            fourOfAKindValue = i;  // Value of the number that appears four times
            break;  // Exit the loop after finding the four of a kind
        }
    }

    if (FourOfTheSameKind) {
        // Calculate the score for four of a kind: i * 4
        score = fourOfAKindValue * 4;

        // Add the sum of the remaining dice
        for (int j = 0; j < NUM_DICE; j++) {
            if (dice[j] != fourOfAKindValue) {
                score += dice[j];  // Add all dice except the four matching dice
            }
        }
    }
    break;
}
        
        
    case 9: //full house
            {
    int hasThreeOfAKind = 0;
    int hasPair = 0;

    // To check for three of a kind and a pair
    for (int i = 1; i <= NUM_SIDES; i++) {
        if (counts[i] == 3) {
            hasThreeOfAKind = 1;  // Number repeated three times
        } else if (counts[i] == 2) {
            hasPair = 1;  // Number repeated two times
        }
    }

    // If both conditions are met, it is a Full House
    if (hasThreeOfAKind && hasPair) {
        score = 25;
    }
    break;
}
        
    case 10: //small straight
        if ((counts[1] && counts[2] && counts[3] && counts[4]) || (counts[2] && counts[3] && counts[4] && counts[5]) || (counts[3] && counts[4] && counts[5] && counts[6])) score = 30; break;
    case 11: //large straight
        if ((counts[1] && counts[2] && counts[3] && counts[4] && counts[5]) || (counts[2] && counts[3] && counts[4] && counts[5] && counts[6])) score = 40; break;
    case 12: //yahtzee
        for (int i = 1; i <= NUM_SIDES; i++) { if (counts[i] == 5) { score = 50; break; } } break;
    case 13: //chance(sum of all dice)
        score = dice[0] + dice[1] + dice[2] + dice[3] + dice[4]; break;
    }
    return score;
}

void chooseCategoryAndScore(int dice[NUM_DICE], int scores[NUM_CATEGORIES]) {
    int category;
    
    //Defining categories
    const char *categoryNames[] = {
        "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", "Three of a Kind", "Four of a Kind","Full House", "Small Straight", "Large Straight", "Yahtzee", "Chance"
    };

    // Display the available categories
    printf("The categories are as below:\n");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        printf("%d: %s\n", i + 1, categoryNames[i]);
    }
    printf("Choose the category:");
    scanf("%d", &category);
    
    // Validate the input
    if (category < 1 || category > NUM_CATEGORIES) {
        printf("Invalid category. Choose again.\n");
        // Recursively call the function 
        chooseCategoryAndScore(dice, scores);
    } else {
        category--; 
        if (scores[category] != -1) {
            printf("Category already used. Choose again.\n");
            chooseCategoryAndScore(dice, scores);
        } else {
            // Calculate the score for the chosen category based on the dice values
            int score = calculateScore(dice, category + 1); 

            //updates the scores array 
            scores[category] = score;
            printf("\nChose category %d-%s and scored %d points.\n",category+1,categoryNames[category],score);

        }
    }
}

void automatedPlayerTurn(char *player, int scores[NUM_CATEGORIES]) {
    int dice[NUM_DICE];
    int toRoll[NUM_DICE];
    int bestCategory = -1;
    int maxScore = 0;
    int rerolls = 0;

    for (int i = 0; i < NUM_DICE; i++) toRoll[i] = 1; // Reroll all 
    rollDice(dice, toRoll);

    printf("\n%s's turn:\n", player);
    printDice(dice);

    // Rerolling
    while (rerolls < NUM_ROLLS-1) {
        // Analyze dice and determine whether to reroll
        int counts[NUM_SIDES + 1] = {0};
        for (int i = 0; i < NUM_DICE; i++) counts[dice[i]]++;

        // Decide which dice to keep
        for (int i = 0; i < NUM_DICE; i++) {
            if (counts[dice[i]] >= 3) { // Keep if part of a three of a kind or better
                toRoll[i] = 0;
            } else if ((counts[dice[i]] >= 2) && rerolls == 0) { // Keep pairs 
                toRoll[i] = 0;
            } else {
                toRoll[i] = 1; // Otherwise, reroll
                
            }
        }

        // Rerolling
        rollDice(dice, toRoll);
        printDice(dice);
        rerolls++;

        // Re-evaluate if valid patterns exist
        bool validPattern = false;
        for (int i = 0; i < NUM_CATEGORIES; i++) {
            if (scores[i] == -1) { // Category available
                int potentialScore = calculateScore(dice, i + 1);
                if (potentialScore > 0) {
                    validPattern = true;
                    break;
                }
            }
        }

 }

    // Choose the best category
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (scores[i] == -1) { // Category available
            int potentialScore = calculateScore(dice, i + 1);
            if (potentialScore > maxScore) {
                maxScore = potentialScore;
                bestCategory = i;
            }
        }
    }
    
    // Otherwise,pick the first unused category
    if (bestCategory == -1) {
        for (int i = 0; i < NUM_CATEGORIES; i++) {
            if (scores[i] == -1) {
                bestCategory = i;
                break;
            }
        }
    }

    // Assign score to the picked category
    if (bestCategory != -1) {
        scores[bestCategory] = calculateScore(dice, bestCategory + 1);
        const char *categoryNames[] = {
            "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes","Three of a Kind", "Four of a Kind", "Full House","Small Straight", "Large Straight", "Yahtzee", "Chance"
        };
        
        printf("\n%s chose category %d-%s and scored %d points.\n", player,bestCategory+1, categoryNames[bestCategory], scores[bestCategory]);

    }
}


void playTurn(char *player, int scores[NUM_CATEGORIES]) {
    int dice[NUM_DICE];
    int toRoll[NUM_DICE];  
    int reRoll; //variable to store the choice of rerolling
    
    printf("%s's turn\n", player);

    for (int i = 0; i < NUM_DICE; i++) {
        toRoll[i] = 1; 
    }

    for (int roll = 0; roll < NUM_ROLLS; roll++) {
        printf("Roll %d:\n", roll + 1);
        rollDice(dice, toRoll);
        printDice(dice); // Display the results of the roll

        if (roll < NUM_ROLLS - 1) {
            while(1){ // Loop until valid input (0 or 1) is received
            printf("Do you want to re-roll? (1: yes, 0: no): ");
           
            scanf("%d", &reRoll);
            if (reRoll == 0 || reRoll == 1) {
                break; // Exit the loop when valid input in received
            } else {
                printf("Invalid input. Please enter 1 or 0.\n");
            }
        }
            //if doesn't reroll,end 
             if (reRoll == 0) break;
            
            //otherwise,choose which dice to reroll
            chooseDiceToReroll(toRoll);
        }
           
    }
    //to choose a scoring category 
    chooseCategoryAndScore(dice, scores);
}

void printScores(char *player, int scores[NUM_CATEGORIES]) {
    printf("\n%s's scores:\n", player);
    const char *categories[] = {
        "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes","Three of a Kind", "Four of a Kind", "Full House","Small Straight", "Large Straight", "Yahtzee", "Chance"
    };
    
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (scores[i] == -1) {
            printf("%s: Not used\n", categories[i]);
        } else {
            printf("%s: %d points\n", categories[i], scores[i]);
            
        }
    }
}

int calculateTotalScore(int scores[NUM_CATEGORIES]) {
    int totalScore = 0;
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (scores[i] != -1) { // Only add categories that have been used
            totalScore += scores[i];
        }
    }
    return totalScore;
}

void findWinner(char *player1, int scoresPlayer1[NUM_CATEGORIES], char *player2, int scoresPlayer2[NUM_CATEGORIES]) {
    int totalScorePlayer1 = calculateTotalScore(scoresPlayer1);
    int totalScorePlayer2 = calculateTotalScore(scoresPlayer2);

    
    if (totalScorePlayer1 > totalScorePlayer2) {
        printf("\nWinner of the game is %s!\n", player1);
    } else if (totalScorePlayer1 < totalScorePlayer2) {
        printf("\nWinner of the game is %s!\n", player2);
    } else {
        printf("\nIt's a tie between %s and %s!\n", player1, player2);
    }
}


int main() {
    srand(time(NULL));  


    char player1[50];
    char player2[] = "Automated Player";

    printf("\nWELCOME TO YAHTZEE!\n");

    printf("\nEnter your name: ");
    fgets(player1, sizeof(player1), stdin);
    player1[strcspn(player1, "\n")] = '\0'; // Remove the newline character from the input

    // Score arrays for both players
    int scoresPlayer1[NUM_CATEGORIES];
    int scoresPlayer2[NUM_CATEGORIES];

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        scoresPlayer1[i] = -1;
        scoresPlayer2[i] = -1;
    }

    for (int round = 0; round < NUM_ROUNDS; round++) {
        printf("\n---------- Round %d ----------\n", round + 1);
        
        //player's turn
        playTurn(player1, scoresPlayer1);
        //automated player's turn
        automatedPlayerTurn(player2, scoresPlayer2);

        // Print current scores after both turns
        printScores(player1, scoresPlayer1);
        printScores(player2, scoresPlayer2);
    }

    printf("\n-- Game over!-- \nFinal scores:\n");
    printScores(player1, scoresPlayer1);
    printScores(player2, scoresPlayer2);

    // Calculate the total scores for both players
    int totalScorePlayer1 = calculateTotalScore(scoresPlayer1);
    int totalScorePlayer2 = calculateTotalScore(scoresPlayer2);

    printf("\n%s's Total Score: %d points\n", player1, totalScorePlayer1);
    printf("\n%s's Total Score: %d points\n", player2, totalScorePlayer2);

    //Determine and display the winner
    findWinner(player1, scoresPlayer1, player2, scoresPlayer2);

    return 0;
}

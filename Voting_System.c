#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define C1 "CANDIDATE 1"
#define C2 "CANDIDATE 2"
#define C3 "CANDIDATE 3"
#define C4 "CANDIDATE 4"

// Define passwords for reset and winner declaration
#define RESET_PASSWORD "123"//You can change the password here.
#define WINNER_PASSWORD "123"//You can change the password here.

int votesCount1 = 0, votesCount2 = 0, votesCount3 = 0, votesCount4 = 0, spoiledVotes = 0;

// Function to safely input an integer
void safeInput(int *choice) {
    while (scanf("%d", choice) != 1) {
        printf("Invalid input. Please enter a valid number: ");
        while (getchar() != '\n');  // Clear the input buffer
    }
}

// Function to ask for confirmation
int confirmAction(const char *message) {
    char choice;
    while (getchar() != '\n'); // Clear any leftover characters in the input buffer
    printf("%s (Y/N): ", message);
    scanf("%c", &choice);  // Read user input for confirmation

    if (choice == 'y' || choice == 'Y') {
        return 1;  // User confirmed the action
    } else if (choice == 'n' || choice == 'N') {
        return 0;  // User canceled the action
    } else {
        printf("Invalid choice. Please enter 'y' to confirm or 'n' to cancel.\n");
        return confirmAction(message);  // Recursively ask again
    }
}

// Function to cast a vote
void castVote() {
    int choice;
    printf("\n\n ### Please choose your Candidate ####\n");
    printf("\n\t 1. %s", C1);
    printf("\n\t 2. %s", C2);
    printf("\n\t 3. %s", C3);
    printf("\n\t 4. %s", C4);
    printf("\n\t 5. %s", "None of These");

    printf("\n\n Input your choice (1 - 5) : ");
    safeInput(&choice);  // Use safe input to handle invalid input

    switch(choice) {
        case 1: votesCount1++; break;
        case 2: votesCount2++; break;
        case 3: votesCount3++; break;
        case 4: votesCount4++; break;
        case 5: spoiledVotes++; break;
        default: printf("\n Error: Wrong Choice!! Please retry"); break;
    }
    printf("\n\tThanks for voting !!!");
}

// Function to display vote count
void votesCount() {
    printf("\n\n ##### Voting Statistics ####");
    printf("\n %s - %d ", C1, votesCount1);
    printf("\n %s - %d ", C2, votesCount2);
    printf("\n %s - %d ", C3, votesCount3);
    printf("\n %s - %d ", C4, votesCount4);
    printf("\n %s - %d ", "Spoiled Votes", spoiledVotes); 
}

// Function to find and display the candidates sorted by votes
void getLeadingCandidate() {
    if (confirmAction("Are you sure you want to see the leading candidates")) {
        // Array to store candidate names and their corresponding votes
        char *candidates[] = {C1, C2, C3, C4};
        int votes[] = {votesCount1, votesCount2, votesCount3, votesCount4};

        printf("\n\n #### All Candidates and Their Vote Counts ####\n\n");

        // Display all candidates and their vote counts
        for (int i = 0; i < 4; i++) {
            printf("%s: %d votes\n", candidates[i], votes[i]);
        }

        // Sorting the candidates based on vote count using a simple bubble sort algorithm
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3 - i; j++) {
                if (votes[j] < votes[j + 1]) {
                    // Swap votes
                    int tempVotes = votes[j];
                    votes[j] = votes[j + 1];
                    votes[j + 1] = tempVotes;
                    // Swap candidate names accordingly
                    char *tempCandidate = candidates[j];
                    candidates[j] = candidates[j + 1];
                    candidates[j + 1] = tempCandidate;
                }
            }
        }

        // Display sorted candidates with votes
        printf("\n#### Sorted Candidates by Vote Count ####\n");
        for (int i = 0; i < 4; i++) {
            printf("%s: %d votes\n", candidates[i], votes[i]);
        }
    } else {
        printf("\nReturning to the main menu without showing the leading candidates.\n");
    }
}

// Reset function to clear all vote counts
void resetVotes() {
    char password[20];
    
    printf("\nPlease enter the reset password: ");
    scanf("%s", password);  // Get password input

    // Check if the entered password is correct
    if (strcmp(password, RESET_PASSWORD) == 0) {
        // If password matches, reset votes
        votesCount1 = 0;
        votesCount2 = 0;
        votesCount3 = 0;
        votesCount4 = 0;
        spoiledVotes = 0;
        printf("\nVotes have been reset successfully!\n");
    } else {
        printf("\nIncorrect password. Reset failed.\n");
    }
}

// Function to declare the winner with password protection
void declareWinner() {
    char password[20];
    
    printf("\nPlease enter the password to declare the winner: ");
    scanf("%s", password);  // Get password input

    // Check if the entered password is correct
    if (strcmp(password, WINNER_PASSWORD) == 0) {
        // If password matches, display all votes
        printf("\n\n ########### Final Vote Tally ###########\n");
        printf("Votes for %s: %d\n", C1, votesCount1);
        printf("Votes for %s: %d\n", C2, votesCount2);
        printf("Votes for %s: %d\n", C3, votesCount3);
        printf("Votes for %s: %d\n", C4, votesCount4);

        // Determine and declare the winner
        printf("\n###########################################\n");

        if (votesCount1 > votesCount2 && votesCount1 > votesCount3 && votesCount1 > votesCount4) {
            printf("\n🎉🎉 The Winner is: %s 🎉🎉\n", C1);
        } else if (votesCount2 > votesCount1 && votesCount2 > votesCount3 && votesCount2 > votesCount4) {
            printf("\n🎉🎉 The Winner is: %s 🎉🎉\n", C2);
        } else if (votesCount3 > votesCount1 && votesCount3 > votesCount2 && votesCount3 > votesCount4) {
            printf("\n🎉🎉 The Winner is: %s 🎉🎉\n", C3);
        } else if (votesCount4 > votesCount1 && votesCount4 > votesCount2 && votesCount4 > votesCount3) {
            printf("\n🎉🎉 The Winner is: %s 🎉🎉\n", C4);
        } else {
            printf("\n🤔 There is a tie or no clear winner yet.\n");
        }

        printf("\n###########################################\n");

    } else {
        printf("\n❌ Incorrect password. Cannot declare the winner. ❌\n");
    }
}

// Function to ask for exit confirmation
int confirmExit() {
    char choice;
    while (getchar() != '\n');  // Clear any remaining characters in the buffer
    printf("\nAre you sure you want to exit? (Y/N): ");
    scanf("%c", &choice);  // Read the user's choice

    if (choice == 'y' || choice == 'Y') {
        return 1;  // User confirmed exit
    } else if (choice == 'n' || choice == 'N') {
        return main();  // User canceled exit
    } else {
        printf("Invalid choice. Please enter 'y' to confirm or 'n' to cancel.\n");
        return confirmExit();  // Recursively ask the user again if the input is invalid
    }
}

int main() {
    int choice;

    do {
        printf("\n\n ###### Welcome to Election/Voting #####");
        printf("\n\n \t 1. Cast the Vote");
        printf("\n \t 2. Find Vote Count");
        printf("\n \t 3. Find Leading Candidate");
        printf("\n \t 4. Reset Votes");
        printf("\n \t 5. Declare Winner");
        printf("\n \t 0. Exit");

        printf("\n\n Please enter your choice : ");
        safeInput(&choice);  // Validate menu input

        switch(choice) {
            case 1: castVote(); break;
            case 2: votesCount(); break;
            case 3: getLeadingCandidate(); break;
            case 4: resetVotes(); break;
            case 5: declareWinner(); break;
            case 0:
                if (confirmExit()) {
                    printf("Exiting the program. Goodbye, Keep Voting!\n");
                    exit(0); // Exit the program
                }
                break;
            default: printf("\n Error: Invalid Choice!! Please retry");
        }
    } while(choice != 0);

    return 0;
}

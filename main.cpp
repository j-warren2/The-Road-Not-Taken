#include <iostream>
#include <string>
#include <map>
using namespace std;

// Helper function to handle user choices.
string getPlayerChoice(char maxChoice) {
    string user_choice;
    maxChoice = toupper(maxChoice);  // Allows for varying number of choices.

    // Use a while loop for input validation.
    while (true) {
        cout << "Enter your choice (A to " << maxChoice << "): ";
        cin >> user_choice;

        // Check 1: Ensure length of user_choice is exactly one character long.
        if (user_choice.length() != 1) {
            cout << "Invalid input. Please type a single letter choice." << endl;
            continue;
        }

        // Check 2: Ensure uppercase.
        char choiceLetter = toupper(user_choice[0]);

        // Check 3: Ensure choice is within bounds.
        if (choiceLetter >= 'A' && choiceLetter <= maxChoice) {
            // Convert the char to a string.
            return string(1, choiceLetter);
        }

        cout << "Invalid choice! Please choose a letter between A and " << maxChoice << "." << endl;
    }
}

// Helper function to generate ONE random choice.
string getRandomChoice(int numOptions) {
    // Get a random number between 0 and (numOptions - 1)
    int randomNumber = rand() % numOptions;

    // Shift it to a character (Ex: 'A' + 0 would be 'A' and 'A' + 1 would be 'B', etc.)
    char randomChoice = 'A' + randomNumber;

    return string(1, randomChoice);
}

int main() {
    // Outer Key: Player ID | Inner Key: Chapter | Inner Value: Choice Made
    map<string, map<string, string>> gameDatabase;
}

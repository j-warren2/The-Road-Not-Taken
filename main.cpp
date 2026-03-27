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

int main() {
    // Outer Key: Player ID | Inner Key: Chapter | Inner Value: Choice Made
    map<string, map<string, string>> gameDatabase;
}

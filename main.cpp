#include <iostream>
#include <string>
#include "HashMap.h"
#include "Trie.h"
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

// Function to generate random players.
void generateRandomPlayers(HashMap& hashDatabase, Trie& trieDatabase, int numPlayers) {
    for (int i = 1; i <= numPlayers; ++i) {
        string currentPath = "";

        // Scene 1
        string s1 = getRandomChoice(3);
        currentPath += s1;
        if (currentPath == "C") {
            hashDatabase.insertDecisionPath(currentPath);
            trieDatabase.insertDecisionPath(currentPath);
            continue;
        }

        // Scene 2
        string s2 = getRandomChoice(2);
        currentPath += s2;

        // Scene 3
        currentPath += getRandomChoice(2);
        if (currentPath == "AAA" || currentPath == "ABB" || currentPath == "BAA" || currentPath == "BAB" || currentPath == "BBB") {
            hashDatabase.insertDecisionPath(currentPath);
            trieDatabase.insertDecisionPath(currentPath);
            continue;
        }

        // Scene 4
        currentPath += getRandomChoice(2);
        if (currentPath == "AABA" || currentPath == "ABAA" || currentPath == "ABAB" || currentPath == "BBAB") {
            hashDatabase.insertDecisionPath(currentPath);
            trieDatabase.insertDecisionPath(currentPath);
            continue;
        }

        // Scene 5
        currentPath += getRandomChoice(2);
        if (currentPath == "AABBA" || currentPath == "AABBB" || currentPath == "BBAAA" || currentPath == "BBAAB") {
            hashDatabase.insertDecisionPath(currentPath);
            trieDatabase.insertDecisionPath(currentPath);
            continue;
        }

        // 3. Insert into both
        hashDatabase.insertDecisionPath(currentPath);
        trieDatabase.insertDecisionPath(currentPath);
    }
}

int main() {
    // 1. Initialize your custom HashMap and Trie
    HashMap hashGameStats(1000);
    Trie trieGameStats;

    // 2. Generate 10 random players
    generateRandomPlayers(hashGameStats, trieGameStats, 10);

    // DEBUGGING STUFF - COMMENT OUT LATER
    // 1. Display Hashmap Results
    cout << "HASHMAP DATA\n";
    vector<pair<string, int>> hashData;
    hashGameStats.collectVisualData(hashData);
    for (const auto& entry : hashData) {
        cout << "Path [" << entry.first << "]: " << entry.second << " users\n";
    }

    // 2. Display Trie Results
    // Note: Trie uses PathNode struct (pathSoFar, usersPassedThrough)
    cout << "\nTRIE DATA (Prefix Tree)\n";
    vector<PathNode> trieData;
    trieGameStats.collectVisualData(trieData);
    for (const auto& node : trieData) {
        // This will print every prefix/node in the tree
        if (!node.pathSoFar.empty()) {
            cout << "Node [" << node.pathSoFar << "]: " << node.usersPassedThrough << " users passed through\n";
        }
    }

    // 3. Compare Stats for a specific path
    if (!hashData.empty()) {
        string testPath = "BAA";
        cout << "\n\tComparison for Path: " << testPath << "\n";
        
        cout << "\n[HashMap Stats]:";
        hashGameStats.printPerChoiceStatistics(testPath);
        
        cout << "\n[Trie Stats]:";
        trieGameStats.printPerChoiceStatistics(testPath);
    }

    return 0;
}

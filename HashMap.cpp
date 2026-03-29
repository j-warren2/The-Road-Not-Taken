#include "HashMap.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor
HashMap::HashMap(int size) {
    // Number of buckets
    tableSize=size;
    // Create a table
    table.resize(tableSize);
}

// Converts inputted path into a value to store onto the table
// O(m) time complexity, due to loop
int HashMap::hash(const std::string& key)const {
    int value= 0;
    for(char c : key) {
        value = (value * 31 + c) % tableSize;
    }
    return value;
}

// Insertion Function
// O(m + k) time complexity, due to hashing and loop
void HashMap::insertDecisionPath(string& decisionPath) {
    int index = hash(decisionPath);
    for (auto& entry : table[index]) {

        // If path exists, increment count
        if (entry.first == decisionPath) {
            entry.second++;
            // Tracks every insertion
            allStoredPaths.push_back(decisionPath);
            totalEntries++;
            return;
        }
    }

    // If it does not exist, add a new entry starting at 1
    table[index].push_back(std::make_pair(decisionPath, 1));
    // Tracks every insertion
    allStoredPaths.push_back(decisionPath);
    totalEntries++;
}

// Checks if a path is stored in the map
// O(m + k) time complexity, due to hashing and loop
bool HashMap::decisionPathExists(const string& decisionPath){
    int index= hash(decisionPath);
    for (const auto& entry : table[index]) {
        if (entry.first == decisionPath)
            return true;
    }
    return false;
}

// Returns how many users took a path
// O(m + k) time complexity, due to hashing and loop
int HashMap::getPathCount(const string& decisionPath) {
    int index= hash(decisionPath);
    for (const auto& entry : table[index]) {
        if (entry.first == decisionPath)
            return entry.second;
    }

    // Returns 0 path was not found
    return 0;
}

// Removes path from the map
// O(m + k) time complexity, due to hashing and loop
void HashMap::removeDecisionPath(const std::string& decisionPath) {
    int index= hash(decisionPath);
    auto& link= table[index];

    // i is the iterator
    for (auto i= link.begin(); i != link.end(); i++) {
        // If the iterator matches the decision path
        if (i->first == decisionPath) {
            // Erase what i is pointing at
            link.erase(i);
            // Decrease total entries
            totalEntries--;
            return;
        }
    }
}

// Compares paths and scores similarities 
// O(m) time complexity, due to loop
int HashMap::countSharedChoices(const string& pathA, const string& pathB) {
    int sharedChoices= 0;
    // Finds whatever path is shorter so it doesn't go out of range 
    int shorterLength= min(pathA.length(), pathB.length());
    // For the entire length of the shorter path
    for (int i = 0; i < shorterLength; i++) {
        // If the characters are equal, the number of shared choices increase
        if (pathA[i] == pathB[i]) {
            sharedChoices++;
        }

        // Otherwise, break the loop
        else {
            break;
        }
    }
    return sharedChoices;
}

// For each step in the path, counts how many stored users made the same choice at that step
// O(n * m^2) time complexity, due to nested for loop and checking
void HashMap::printPerChoiceStatistics(const string& currentUserPath) {

    // If the map is empty, print error message and return
    if (totalEntries == 0) {
        cout << "No paths stored in HashMap yet.\n";
        return;
    }

    // If the path doesn't exist, print error message and return
    if (!decisionPathExists(currentUserPath)) {
        cout << "Path not found in HashMap.\n";
        return;
    }

    cout << "\nPer-choice statistics for path: " << currentUserPath << "\n";

    for (int i = 0; i < (int)currentUserPath.length(); i++) {
        int matchCount = 0;

        // Scan every stored path
        for (const string& stored : allStoredPaths) {
            if ((int)stored.length() <= i) {
                continue;
            }
            // Check that preceding choice matches previous node
            bool prevMatch= true;
            for(int j = 0; j<=i;j++) {
                if(stored[j] != currentUserPath[j]) {
                    prevMatch= false;
                    break;
                }
            }
            // If it does, increase match count
            if(prevMatch) {
                matchCount++;
            }
        }

        double percentage= (double)matchCount / totalEntries * 100;
        cout << "Choice " << (i + 1) << " ('" << currentUserPath[i] << "'): "
             << matchCount << " users ("
             << (int)percentage << "%) made the same choice\n";
    }
}

// Finds most and least similar paths
// O(n * m) time complexity, due to nested for loops
void HashMap::findMostAndLeastSimilarPaths(const string& currentUserPath) {

    // Needs at least 2 paths to make a comparison
    if (allStoredPaths.size() <= 1) {
        cout << "Not enough paths stored to compare.\n";
        return;
    }

    string mostSimilarPath  = "";
    string leastSimilarPath = "";
    int highestScore = -1;
    int lowestScore  = (int)currentUserPath.length() + 1;

    // Track which paths we have already scored to avoid duplicates
    vector<string> seen;

    // Loop through every stored path and compare it to the user's
    for (const string& stored : allStoredPaths) {

        // Skip the current user's own path
        if (stored == currentUserPath) continue;

        // Skip if we have already scored this path
        bool alreadySeen = false;
        for (const string& s : seen) {
            if (s == stored) {
                alreadySeen = true;
                break;
            }
        }
        if (alreadySeen) {
            continue;
        }
        seen.push_back(stored);

        // Count the shared choices between paths
        int score = countSharedChoices(currentUserPath, stored);

        // Update the most and least similar paths
        if (score > highestScore) {
            highestScore = score;
            mostSimilarPath = stored;
        }
        if (score < lowestScore) {
            lowestScore = score;
            leastSimilarPath = stored;
        }
    }

    // Prints the most similar and least similar
    cout << "\nMost similar path:  " << mostSimilarPath + 1 << " (" << highestScore << " shared choices)\n";
    cout << "Least similar path: " << leastSimilarPath << " (" << lowestScore << " shared choices)\n";
}

// Puts all paths into a vector
// O(n + t) time complexity, due to nested for loops but not running completely through every time
void HashMap::collectVisualData(vector<pair<string, int>>& ans) {
    for (auto& bucket : table) {
        for (auto& entry : bucket) {
            ans.push_back(entry);
        }
    }
}

// Returns the total amount of users
// O(1) time complexity, just returns variable
int HashMap::getTotalUsers() {
    return totalEntries;
}

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
int HashMap::hash(std::string& key) {
    int value= 0;
    for(char c : key) {
        value = (value * 31 + c) % tableSize;
    }
    return value;
}

// Insertion Function
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

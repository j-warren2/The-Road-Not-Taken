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

// Checks if a path is stored in the map
bool HashMap::decisionPathExists(const string& decisionPath){
    int index= hash(decisionPath);
    for (const auto& entry : table[index]) {
        if (entry.first == decisionPath)
            return true;
    }
    return false;
}

// Returns how many users took a path
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

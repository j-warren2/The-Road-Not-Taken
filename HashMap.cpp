//
// Created by GVZ on 3/26/2026.
//

#include "HashMap.h"
#include <stdexcept>

// Constructor
HashMap::HashMap(int size) {
    tableSize=size;
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

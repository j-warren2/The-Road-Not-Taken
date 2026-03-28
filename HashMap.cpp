#include "HashMap.h"
#include <iostream>
#include <stdexcept>
using namespace std;

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

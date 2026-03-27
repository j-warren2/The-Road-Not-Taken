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



#ifndef PROJECT_2_HASHMAP_HASHMAP_H
#define PROJECT_2_HASHMAP_HASHMAP_H

#include <string>
#include <vector>
#include <list>
#include <utility>

class HashMap {
    int tableSize;
    int totalEntries;
    std::vector<std::list<std::pair<std::string, int>>> table;
    std::vector<std::string> allStoredPaths;
    int hash(std::string& key);

public:
    // Constructor
    HashMap(int size = 133000);

    // Inserts a decision path onto the map
    void insert(std::string& key);

    // Gets the number of users who took a certain path
    int getCount(const std::string& key);

    // Removes a path entirely
    void remove(const std::string& key);

    // Gets all current paths, as well as the amount of users that took each one
    std::vector<std::pair<std::string, int>> getPaths();

};

#endif //PROJECT_2_HASHMAP_HASHMAP_H

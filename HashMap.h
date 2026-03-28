
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
    void insertDecisionPath(std::string& decisionPath);

    // Gets the number of users who took a certain path
    int getCount(const std::string& key);

    // Removes a path entirely
    void removeDecisionPath(const std::string& decisionPath);

    // Gets all current paths, as well as the amount of users that took each one
    int getPathCount(const std::string& decisionPath);

};

#endif //PROJECT_2_HASHMAP_HASHMAP_H

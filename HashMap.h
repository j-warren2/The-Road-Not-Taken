
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

    // Checks if a path exists
    bool decisionPathExists(const std::string& decisionPath);

    // Gets the number of users who took a certain path
    int getPathCount(const std::string& decisionPath);

    // Removes a path entirely
    void removeDecisionPath(const std::string& decisionPath);

    // Compares paths and scores similarities
    int countSharedChoices(const std::string& pathA, const std::string& pathB);

    // Compares how many stored users made the same choice at each step.
    void printPerChoiceStatistics(const std::string& currentUserPath);

    // Finds most and least similar paths
    void findMostAndLeastSimilarPaths(const std::string& currentUserPath);
};

#endif //PROJECT_2_HASHMAP_HASHMAP_H

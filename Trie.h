#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> nextChoices;
    bool isCompleteUserPath;
    int usersPassedThrough;
    TrieNode() : isCompleteUserPath(false), usersPassedThrough(0) {}
};

struct PathNode {
    string pathSoFar;
    int usersPassedThrough;
};

class Trie {
private:
    TrieNode* storyRoot;
    vector<string> allStoredPaths;
    void traverseForVisual(TrieNode* currentNode, string pathSoFar, vector<PathNode>& result);
    void deleteNodes(TrieNode* node);

public:
    Trie();
    ~Trie();
    void insertDecisionPath(const string& decisionPath);
    bool decisionPathExists(const string& decisionPath);
    int countSharedChoices(const string& pathA, const string& pathB);
    void printPerChoiceStatistics(const string& currentUserPath);
    void findMostAndLeastSimilarPaths(const string& currentUserPath);
    void collectVisualData(vector<PathNode>& result);
    int getTotalUsers();
};

#endif

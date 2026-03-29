#include "Trie.h"

void Trie::traverseForVisual(TrieNode* currentNode, string pathSoFar, vector<PathNode>& result) {
    result.push_back({pathSoFar, currentNode->usersPassedThrough});
    for (auto& [choice, childNode] : currentNode->nextChoices) {
        traverseForVisual(childNode, pathSoFar + choice, result);
    }
}

Trie::Trie() {
    storyRoot = new TrieNode();
}
void Trie::deleteNodes(TrieNode* node) {
    for (auto& [choice, child] : node->nextChoices) {
        deleteNodes(child);
    }
    delete node;
}

Trie::~Trie() {
    deleteNodes(storyRoot);
}

// time complexity: O(m) where m = length of the decision path string
// walks the path once, creating nodes where needed
void Trie::insertDecisionPath(const string& decisionPath) {
    TrieNode* currentNode = storyRoot;
    for (char storyChoice : decisionPath) {
        if (currentNode->nextChoices.find(storyChoice) == currentNode->nextChoices.end())
            currentNode->nextChoices[storyChoice] = new TrieNode();
        currentNode = currentNode->nextChoices[storyChoice];
        currentNode->usersPassedThrough++;
    }
    currentNode->isCompleteUserPath = true;
    allStoredPaths.push_back(decisionPath);
}

// time complexity: O(m) - walks the path, returns false if any character is missing
// isCompleteUserPath identifies a full path from a prefix that only exists as part of a longer stored path
bool Trie::decisionPathExists(const string& decisionPath) {
    TrieNode* currentNode = storyRoot;
    for (char storyChoice : decisionPath) {
        if (currentNode->nextChoices.find(storyChoice) == currentNode->nextChoices.end())
            return false;
        currentNode = currentNode->nextChoices[storyChoice];
    }
    return currentNode->isCompleteUserPath;
}

// time complexity: O(m) - counts matching characters from the start before first divergence
// used by findMostAndLeastSimilarPaths to score similarity between paths
int Trie::countSharedChoices(const string& pathA, const string& pathB) {
    int sharedChoices = 0;
    int shorterLength = min(pathA.length(), pathB.length());
    for (int i = 0; i < shorterLength; i++) {
        if (pathA[i] == pathB[i]) sharedChoices++;
        else break;
    }
    return sharedChoices;
}

// time complexity: O(m) - walks the current user's path and reports what percentage of all users made the same choice at each scene
void Trie::printPerChoiceStatistics(const string& currentUserPath) {
    if (allStoredPaths.empty()) {
        cout << "No paths stored in Trie yet.\n";
        return;
    }
    if (!decisionPathExists(currentUserPath)) {
        cout << "Path not found in Trie.\n";
        return;
    }
    TrieNode* currentNode = storyRoot;
    cout << "\nPer-choice statistics for path: " << currentUserPath << "\n";
    for (int i = 0; i < (int)currentUserPath.length(); i++) {
        char storyChoice = currentUserPath[i];
        if (currentNode->nextChoices.find(storyChoice) == currentNode->nextChoices.end()) {
            cout << "Missing node at choice " << (i + 1) << "\n";
            return;
        }
        currentNode = currentNode->nextChoices[storyChoice];
        double percentage = (double)currentNode->usersPassedThrough
                            / allStoredPaths.size() * 100;
        cout << "Choice " << (i + 1) << " ('" << storyChoice << "'): "
             << currentNode->usersPassedThrough << " users ("
             << (int)percentage << "%) made the same choice\n";
    }
}

// time complexity: O(n*m) - compares current path against all n stored paths using countSharedChoices (O(m) each - the only Trie operation that changes with dataset size)
void Trie::findMostAndLeastSimilarPaths(const string& currentUserPath) {
    if (allStoredPaths.size() <= 1) {
        cout << "Not enough paths stored to compare.\n";
        return;
    }
    string mostSimilarPath = "";
    string leastSimilarPath = "";
    int highestScore = -1;
    int lowestScore = (int)currentUserPath.length() + 1;

    for (const string& storedPath : allStoredPaths) {
        if (storedPath == currentUserPath) continue;
        int score = countSharedChoices(currentUserPath, storedPath);
        if (score > highestScore) {
            highestScore = score; mostSimilarPath = storedPath;
        }
        if (score < lowestScore) {
            lowestScore = score; leastSimilarPath = storedPath;
        }
    }

    cout << "\nMost similar path:  " << mostSimilarPath << " (" << highestScore + 1 << " shared choices)\n";
    cout << "Least similar path: " << leastSimilarPath << " (" << lowestScore << " shared choices)\n";
}

// time complexity: O(k) where k = number of unique nodes in the Trie (unique prefixes)
// k is much smaller than n*m because of prefix compression - referenced from: https://www.geeksforgeeks.org/dsa/compressed-tries/
void Trie::collectVisualData(vector<PathNode>& result) {
    for (auto& [choice, childNode] : storyRoot->nextChoices)
        traverseForVisual(childNode, string(1, choice), result);
}

int Trie::getTotalUsers() {
    return (int)allStoredPaths.size();
}

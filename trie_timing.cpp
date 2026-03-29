#include "Trie.h"
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

int main() {
    vector<string> testPaths;
    testPaths.reserve(120000);
    string choices = "AB";
    srand(42);
    for (int i = 0; i < 120000; i++) {
        int len = 3 + rand() % 3;
        string path = "";
        for (int j = 0; j < len; j++)
            path += choices[rand() % 2];
        testPaths.push_back(path);
    }

    Trie trie;

    // Time: insertDecisionPath
    auto start = high_resolution_clock::now();
    for (const string& path : testPaths)
        trie.insertDecisionPath(path);
    auto end = high_resolution_clock::now();
    cout << "insertDecisionPath (all 13 paths): "
         << duration_cast<microseconds>(end - start).count()
         << " microseconds\n";

    // Time: decisionPathExists
    start = high_resolution_clock::now();
    trie.decisionPathExists("AABBA");
    end = high_resolution_clock::now();
    cout << "decisionPathExists:                "
         << duration_cast<microseconds>(end - start).count()
         << " microseconds\n";

    // Time: printPerChoiceStatistics
    start = high_resolution_clock::now();
    trie.printPerChoiceStatistics("AABBA");
    end = high_resolution_clock::now();
    cout << "printPerChoiceStatistics:          "
         << duration_cast<microseconds>(end - start).count()
         << " microseconds\n";

    // --- Time: findMostAndLeastSimilarPaths ---
    start = high_resolution_clock::now();
    trie.findMostAndLeastSimilarPaths("AABBA");
    end = high_resolution_clock::now();
    cout << "findMostAndLeastSimilarPaths:      "
         << duration_cast<microseconds>(end - start).count()
         << " microseconds\n";

    // Time: collectVisualData
    vector<PathNode> visualData;
    start = high_resolution_clock::now();
    trie.collectVisualData(visualData);
    end = high_resolution_clock::now();
    cout << "collectVisualData:                 "
         << duration_cast<microseconds>(end - start).count()
         << " microseconds\n";

    // Time: getTotalUsers
    start = high_resolution_clock::now();
    trie.getTotalUsers();
    end = high_resolution_clock::now();
    cout << "getTotalUsers:                     "
         << duration_cast<microseconds>(end - start).count()
         << " microseconds\n";

    return 0;
}

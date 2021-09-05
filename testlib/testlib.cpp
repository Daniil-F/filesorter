#include "testlib.h"

#include <random>

using namespace std;

random_device rnd_device;
mt19937_64 rnd(rnd_device());

void generateFile(ofstream& file, unsigned long long numStrings, size_t maxStrLen) {
    for (int i = 0; i < numStrings; i++) {
        string toPut(rnd() % maxStrLen + 1, 'a');
        for (auto& c : toPut) {
            c = rnd() % ('z' - 'a' + 1) + 'a';
        }
        file << toPut << endl;
    }
}

bool checkIfSorted(ifstream& file) {
    string prev;
    getline(file, prev);
    for (string cur; getline(file, cur); prev = cur) {
        if (cur < prev) {
            return false;
        }
    }
    return true;
}

bool checkIfCorrect(const vector<string>& sorted, ifstream& file) {
    vector<string> result;
    for (string s; getline(file, s); result.push_back(s));
    return result == sorted;
}

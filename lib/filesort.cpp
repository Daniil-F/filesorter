#include "filesort.h"
#include "tmpmgr.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

typedef unsigned long long lsize_t;

void mergeSortFile(ifstream& from, ofstream& to, TmpManager& tmp,
                   const lsize_t nStrings,const size_t NumToSortInRam,
                   const size_t depth = 0) {
    if (nStrings <= NumToSortInRam) {
        vector<string> toSort(nStrings);
        for (auto& s : toSort) {
            getline(from, s);
        }
        sort(toSort.begin(), toSort.end());
        for (const auto& s : toSort) {
            to << s << endl;
        }
        return;
    }
    const auto leftNStrings = nStrings / 2;
    const auto rightNStrings = nStrings - leftNStrings;
    ofstream toLeft(tmp.getTmp(depth));
    mergeSortFile(from, toLeft, tmp, leftNStrings, NumToSortInRam, depth + 1);
    ofstream toRight(tmp.getTmp(depth + 1));
    mergeSortFile(from, toRight, tmp, rightNStrings, NumToSortInRam, depth + 2);
    toLeft.close();
    toRight.close();
    ifstream leftResult(tmp.getTmp(depth));
    ifstream rightResult(tmp.getTmp(depth + 1));
    int leftDone = 0, rightDone = 0;
    string leftCurrent, rightCurrent;
    getline(leftResult, leftCurrent);
    getline(rightResult, rightCurrent);
    while (leftDone < leftNStrings || rightDone < rightNStrings) {
        const bool leftHasStrings = leftDone < leftNStrings;
        const bool rightHasStrings = rightDone < rightNStrings;
        if (leftHasStrings && (!rightHasStrings || leftCurrent <= rightCurrent)) {
            to << leftCurrent << endl;
            leftDone++;
            getline(leftResult, leftCurrent);
        }
        else {
            to << rightCurrent << endl;
            rightDone++;
            getline(rightResult, rightCurrent);
        }
    }
}

void sortFileWithBuffer(ifstream& in, ofstream& out, const size_t numToSortInRam) {
    string content;
    lsize_t numStrings = 0;
    while (in.peek() != char_traits<char>::eof()) {
        getline(in, content);
        numStrings++;
    }
    in.seekg(0);
    TmpManager tmp;
    mergeSortFile(in, out, tmp, numStrings, numToSortInRam);
}

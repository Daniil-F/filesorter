#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <filesort.h>

using namespace std;

#ifndef NUM_TO_SORT_IN_RAM_DEFAULT
#define NUM_TO_SORT_IN_RAM_DEFAULT 1
#endif


int main(int argc, const char** argv) {

    const vector<string> args(argv, argv + argc);
    if (argc >= 3 && argc <= 4) {
        size_t numToSortInRam = NUM_TO_SORT_IN_RAM_DEFAULT;
        if (argc == 4) {
            numToSortInRam = atoi(argv[3]);
        }
        const string sourceFilename = args[1];
        const string targetFilename = args[2];
        cerr << "sorting " << sourceFilename << " , writing result to " << targetFilename << " ..." << endl;
        ifstream from(sourceFilename);
        ofstream to(targetFilename);
        sortFileWithBuffer(from, to, numToSortInRam);
        cerr << "done" << endl;
        return 0;
    }
    else {
        cerr << "invalid command line arguments, use " << args[0] << " SOURCE TARGET [NUM_TO_SORT_IN_RAM]" << endl;
        return 1;
    }
}

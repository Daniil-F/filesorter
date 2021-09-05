#include <testlib.h>
#include <iostream>

using namespace std;

int main(int argc, const char** argv) {
    vector<string> args(argv, argv + argc);
    if (args[1] == "generate") {
        ofstream fout(args[2]);
        cerr << "generating file " << args[2] << " with " << args[3] << " strings of len <= " << args[4] << endl;
        generateFile(fout, atoll(argv[3]), atoi(argv[4]));
        return 0;
    }
    if (args[1] == "check") {
        if (argc == 3) {
            ifstream fin(args[2]);
            if (checkIfSorted(fin))
                cerr << "OK\n";
            else
                cerr << "FAIL\n";
        }
        if (argc == 4) {
            ifstream orig(args[2]);
            vector<string> expected;
            for (string s; getline(orig, s); expected.push_back(s));
            sort(expected.begin(), expected.end());
            ifstream res(args[3]);
            if (checkIfCorrect(expected, res))
                cerr << "OK\n";
            else
                cerr << "FAIL\n";
        }
    }
}

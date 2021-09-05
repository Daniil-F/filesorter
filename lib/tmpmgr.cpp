#include "tmpmgr.h"
#include <random>
#include <sstream>

using namespace std;

random_device rnd_device;
mt19937_64 rnd(rnd_device());

TmpManager::TmpManager() {}

TmpManager::~TmpManager() {
    for (const auto& p : tmpPaths) {
        filesystem::remove(p);
    }
}

void TmpManager::expandTmpPaths() {
    stringstream ss;
    ss << rnd() << "_bufferfile";
    auto tmpDir = filesystem::temp_directory_path();
    tmpDir.append(ss.str());
    tmpPaths.push_back(tmpDir);
}

filesystem::path TmpManager::getTmp(const size_t idx) {
    while (tmpPaths.size() <= idx) {
        expandTmpPaths();
    }
    return tmpPaths[idx];
}

#include <fstream>
#include <filesystem>
#include <vector>

class TmpManager {
public:
    TmpManager();
    ~TmpManager();
    std::filesystem::path getTmp(const size_t idx);
private:
    void expandTmpPaths();
    std::vector<std::filesystem::path> tmpPaths;
};

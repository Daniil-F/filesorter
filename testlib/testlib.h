#include <fstream>
#include <string>
#include <vector>

void generateFile(std::ofstream& file, unsigned long long numStrings, size_t maxStrLen);
bool checkIfSorted(std::ifstream& file);
bool checkIfCorrect(const std::vector<std::string>& sorted, std::ifstream& file);

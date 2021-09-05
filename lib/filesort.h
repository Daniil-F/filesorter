#pragma once

#include <fstream>

void sortFileWithBuffer(std::ifstream& from, std::ofstream& to, const size_t numToSortInRam);
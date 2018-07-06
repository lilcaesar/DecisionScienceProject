#ifndef GENERICFUNCTIONS_H
#define GENERICFUNCTIONS_H

#include <experimental/filesystem>

#include <string>
#include <vector>

void parseInitialFile(const std::experimental::filesystem::directory_entry path, std::vector<std::pair<int,int>>& coordinates, std::vector<int>& demand);

#endif // GENERICFUNCTIONS_H

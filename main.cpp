#include <experimental/filesystem>
#include <iostream>

#include <genericfunctions.h>

int main()
{
    std::vector<std::pair<int,int>> coordinates;
    std::vector<int> demand;
    std::string path = "/root/Scrivania/DecisionScienceProjectData";

    for(const std::experimental::filesystem::directory_entry & p : std::experimental::filesystem::directory_iterator(path)){
        parseInitialFile(p, coordinates, demand);
    }
    return 0;
}

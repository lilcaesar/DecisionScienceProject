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

        std::cout << p << std::endl;

        for (auto const& value : coordinates)
        {
            std::cout << value.first << "  " << value.second << std::endl;
            //std::cout << value << std::endl;
        }

        for (auto const& value : demand)
        {
            std::cout << value << std::endl;
        }

        coordinates.clear();
        demand.clear();
    }

    return 0;
}

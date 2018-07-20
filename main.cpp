#include <experimental/filesystem>
#include <iostream>

#include <genericfunctions.h>
#include <clarkwrightfunctions.h>

int main()
{
    std::vector<std::pair<int,int>> coordinates;
    std::vector<int> demand;
    std::vector<std::vector<float>> distances;
    std::vector<std::vector<float>> savings;
    std::string path = "/root/Scrivania/DecisionScienceProjectData";

    for(const std::experimental::filesystem::directory_entry & p : std::experimental::filesystem::directory_iterator(path)){
        int optimalValue;
        parseInitialFile(p, coordinates, demand, optimalValue);

        computeDistanceTable(coordinates,distances);
        computeSavingsTable(distances, savings);



        coordinates.clear();
        demand.clear();
        distances.clear();
        savings.clear();
    }


    return 0;
}

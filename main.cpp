#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

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

        boost::filesystem::path temporaryFilePath(p.path().string());
        std::string outputFileName = "output/solution-" + temporaryFilePath.stem().string() + ".txt";
        std::ofstream outputFile(outputFileName);

        std::vector<std::vector<int>> finalRoutes;
        std::vector<std::vector<int>> initialRoutes;
        createInitialRoutes(initialRoutes, distances.size());

        sequentialClarkAndWright(demand, savings,initialRoutes, finalRoutes);


        outputFile.close();

        coordinates.clear();
        demand.clear();
        distances.clear();
        savings.clear();
    }


    return 0;
}

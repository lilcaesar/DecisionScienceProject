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

        std::vector<std::pair<float,std::pair<int,int>>> sequentialList;

        computeSavingsTable(distances, savings, sequentialList);

        std::vector<std::pair<float,std::pair<int,int>>> parallelList(sequentialList);

        boost::filesystem::path temporaryFilePath(p.path().string());
        std::string outputFileName = "output/solution-" + temporaryFilePath.stem().string() + ".txt";
        std::ofstream outputFile(outputFileName);

        std::vector<std::vector<int>> routes;
        createInitialRoutes(routes, distances.size());

        sequentialClarkAndWright(demand, sequentialList, routes);

        outputFile.close();

        coordinates.clear();
        demand.clear();
        distances.clear();
        savings.clear();
    }


    return 0;
}

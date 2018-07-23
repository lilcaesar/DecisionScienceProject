#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

#include <genericfunctions.h>
#include <clarkwrightfunctions.h>


bool sortinrev(const std::pair<float,std::pair<int,int>> &a,
               const std::pair<float,std::pair<int,int>> &b)
{
       return (a.first > b.first);
}

int main()
{
    /*std::vector<std::pair<int,int>> coordinates;
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
    }*/


    std::vector<int> demand;
    std::vector<std::vector<float>> savings;

    demand.push_back(37);
    demand.push_back(35);
    demand.push_back(30);
    demand.push_back(25);
    demand.push_back(32);

    std::vector<float> vettore;

    vettore.push_back(-1);
    vettore.push_back(38);
    vettore.push_back(19);
    vettore.push_back(27);
    vettore.push_back(42);

    savings.push_back(vettore);
    vettore.clear();

    vettore.push_back(-1);
    vettore.push_back(-1);
    vettore.push_back(13);
    vettore.push_back(36);
    vettore.push_back(33);

    savings.push_back(vettore);
    vettore.clear();

    vettore.push_back(-1);
    vettore.push_back(-1);
    vettore.push_back(-1);
    vettore.push_back(15);
    vettore.push_back(27);

    savings.push_back(vettore);
    vettore.clear();

    vettore.push_back(-1);
    vettore.push_back(-1);
    vettore.push_back(-1);
    vettore.push_back(-1);
    vettore.push_back(34);

    savings.push_back(vettore);

    std::vector<std::pair<float,std::pair<int,int>>> sequentialList;

    for(unsigned long i = 0; i<savings.size(); i++){
        for(unsigned long j= i+1; j<savings.size()+1; j++){
            sequentialList.push_back(std::make_pair(savings[i][j],std::make_pair(i+1,j+1)));
        }
    }

    sort(sequentialList.begin(), sequentialList.end(), sortinrev);

    std::vector<std::vector<int>> routes;
    createInitialRoutes(routes, 6);

    sequentialClarkAndWright(demand, sequentialList, routes);

    int cisao=0;
    return 0;
}

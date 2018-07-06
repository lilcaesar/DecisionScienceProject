#include <iostream>
#include <fstream>
#include <string>
#include <experimental/filesystem>

using namespace std;

int main()
{
    std::vector<std::pair<int,int>> coordinates;
    string path = "/root/Scrivania/DecisionScienceProjectData";

    for(auto & p : std::experimental::filesystem::directory_iterator(path)){
        string line;
        std::ifstream fs (p.path().string());
        int dimension;
        int capacity;
        istringstream tokenStream;
        string token;

        //Skipping 3 lines and using the 4th
        for(int i=0; i<4;i++){
            getline(fs, line);
        }
        //parsing the 4th line
        tokenStream.str(line);
        for(int i=0; i<3; i++){
            getline(tokenStream, token, ' ');
        }
        dimension = stoi(token);

        //skipping 3 lines
        for(int i=0; i<3;i++){
            getline(fs, line);
        }

        //parsing the coordinates data
        tokenStream.clear();
        tokenStream.str(line);

        fs.close();
    }
    return 0;
}

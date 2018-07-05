#include <iostream>
#include <fstream>
#include <string>
#include <experimental/filesystem>

using namespace std;

int main()
{
    string path = "/root/Scrivania/DecisionScienceProjectData";

    for(auto & p : std::experimental::filesystem::directory_iterator(path)){
        string line;
        std::ifstream fs (p.path().string());

        while(getline(fs, line)){
            cout << line << endl;
        }

        fs.close();
    }
    return 0;
}

#include "genericfunctions.h"

#include <iostream>
#include <fstream>

void parseInitialFile(const std::experimental::filesystem::directory_entry path, std::vector<std::pair<int,int>>& coordinates, std::vector<int>& demand, int& optimalValue){
    std::string line;
    std::ifstream fs (path.path().string());
    int dimension;
    std::istringstream tokenStream;
    std::string token;

    //Skipping 1 lines and using the 2nd
    for(int i=0; i<2;i++){
        getline(fs, line);
    }
    //parsing the 2nd line
    tokenStream.str(line);
    for(int i=0; i<13; i++){
        getline(tokenStream, token, ' ');
    }
    token = token.substr(0, token.size()-2);
    optimalValue = stoi(token);
    tokenStream.clear();

    //Skipping 1 lines and using the 4th
    for(int i=0; i<2;i++){
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
    for(int i=0; i<dimension;i++){
        int x,y;
        getline(fs, line);
        tokenStream.clear();
        tokenStream.str(line);

        //Skip dello spazio iniziale e dell'indice
        getline(tokenStream, token, ' ');
        getline(tokenStream, token, ' ');
        //leggo le coordinate
        getline(tokenStream, token, ' ');
        x = stoi(token);
        getline(tokenStream, token, ' ');
        y = stoi(token);

        coordinates.push_back(std::pair<int,int>(x,y));
    }

    //skip di una linea
    getline(fs, line);

    //parsing the demand data
    for(int i=0; i<dimension;i++){
        int d;
        getline(fs, line);
        tokenStream.clear();
        tokenStream.str(line);

        //Skip dell'indice
        getline(tokenStream, token, ' ');
        //leggo le coordinate
        getline(tokenStream, token, ' ');
        d = stoi(token);

        demand.push_back(d);
    }

    fs.close();
}

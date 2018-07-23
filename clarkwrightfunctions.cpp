#include "clarkwrightfunctions.h"

#include<math.h>
#include<bits/stdc++.h>

bool sortinrev(const std::pair<float,std::pair<int,int>> &a,
               const std::pair<float,std::pair<int,int>> &b)
{
       return (a.first > b.first);
}

void computeDistanceTable(const std::vector<std::pair<int, int> > &coordinates, std::vector<std::vector<float>> &distances){
    unsigned long dimension = coordinates.size();
    distances.resize(dimension);
    for(unsigned long i=0; i<dimension;i++){
        distances[i].resize(dimension);
        for(unsigned long j=0; j<dimension;j++){
            if(i == j){
                distances[i][j]=-1;
            }else{
                distances[i][j]=sqrtf(static_cast<float> (pow((coordinates[i].first)-(coordinates[j].first),2.0) +
                                                pow((coordinates[i].second)-(coordinates[j].second),2.0)));
            }
        }
    }
}

void computeSavingsTable(const std::vector<std::vector<float>> &distances, std::vector<std::vector<float>> &savings){
    unsigned long dimension = distances.size()-1;
    savings.resize(dimension);
    for(unsigned long i=1; i<dimension+1;i++){
        savings[i-1].resize(dimension);
        for(unsigned long j=1; j<dimension+1;j++){
            if(i-1==j-1){
                savings[i-1][j-1]=-1;
            }else{
                savings[i-1][j-1]= (distances[0][i]*2 + distances[0][j]*2)-(distances[0][i]+distances[0][j]+distances[i][j]);
            }
        }
    }
}

void createInitialRoutes(std::vector<std::vector<int> > &routes, unsigned long dimension){
    for(unsigned long i = 0; i < dimension; i++){
        std::vector<int> row;
        row.push_back(0);
        row.push_back(i+1);
        row.push_back(0);
        routes.push_back(row);
    }
}

void sequentialClarkAndWright(const std::vector<int> &demand, const std::vector<std::vector<float>> &savings, std::vector<std::vector<int>> &initialRoutes, std::vector<std::vector<int>> &finalRoutes){
    std::vector<std::pair<float,std::pair<int,int>>> lista;

    for(unsigned long i = 0; i<savings.size()-1; i++){
        for(unsigned long j= i+1; j<savings.size(); j++){
            lista.push_back(std::make_pair(savings[i][j],std::make_pair(i+1,j+1)));
        }
    }

    sort(lista.begin(), lista.end(), sortinrev);


}

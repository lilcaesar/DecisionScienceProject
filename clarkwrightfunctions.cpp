#include "clarkwrightfunctions.h"

#include<math.h>

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

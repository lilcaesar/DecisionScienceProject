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
                distances[i][j]=0;
            }else{
                distances[i][j]=sqrtf(static_cast<float> (pow((coordinates[i].first)-(coordinates[j].first),2.0) +
                                                pow((coordinates[i].second)-(coordinates[j].second),2.0)));
            }
        }
    }
}

void computeSavingsTable(const std::vector<std::vector<float>> &distances, std::vector<std::vector<float>> &savings, std::vector<std::pair<float,std::pair<int,int>>> &lista){
    unsigned long dimension = distances.size();
    savings.resize(dimension-1);
    for(unsigned long i=0; i<dimension-1;i++){
        savings[i].resize(dimension);
        for(unsigned long j=0; j<dimension;j++){
            if((i==0)||(j<=i)){
                savings[i][j]=0;
            }else{
                savings[i][j]= (distances[0][i]*2 + distances[0][j]*2)-(distances[0][i]+distances[0][j]+distances[i][j]);
            }
        }
    }


    for(unsigned long i = 0; i<savings.size(); i++){
        for(unsigned long j= i+1; j<savings.size()+1; j++){
            lista.push_back(std::make_pair(savings[i][j],std::make_pair(i,j)));
        }
    }

    sort(lista.begin(), lista.end(), sortinrev);
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

void sequentialClarkAndWright(const std::vector<int> &demand, std::vector<std::pair<float, std::pair<int, int> > > &sequentialList, std::vector<std::vector<int>> &routes){
    unsigned long routeIndex=0;
    int capacity;
    while ((!sequentialList.empty())&&(routeIndex<routes.size())) {
        bool found = false;
        bool isFirst = false;
        capacity=100 - demand[routes[routeIndex][1]];
        unsigned long savingIndex=0;
        while(capacity > 0){
            if(found){
                //aggiungo route
                int foundValue;
                int addedValue;
                float savingValue = sequentialList[savingIndex].first;
                routes[routeIndex].pop_back();
                if(isFirst){
                    foundValue=sequentialList[savingIndex].second.first;
                    addedValue=sequentialList[savingIndex].second.second;
                    routes[routeIndex].push_back(addedValue);
                }else{
                    foundValue=sequentialList[savingIndex].second.second;
                    addedValue=sequentialList[savingIndex].second.first;
                    routes[routeIndex].push_back(addedValue);
                }
                routes[routeIndex].push_back(0);

                for(unsigned long i=savingIndex; i<sequentialList.size(); i++){
                    if((sequentialList[i].second.first == foundValue)||(sequentialList[i].second.second == foundValue)){
                        sequentialList.erase(sequentialList.begin() + i);
                        i--; //perchè se eliminiamo una riga e poi incrementiamo saltiamo quella
                        //successiva che potrebbe avere un valore non valido
                    }
                }

                for(unsigned long i = routeIndex+1; i<routes.size(); i++){
                    if(routes[i][1]==addedValue){
                        routes.erase(routes.begin()+i);
                        i=routes.size();
                    }
                }

                capacity -= demand[addedValue];
                savingIndex=0;
                found=false;
            }else{
                if(savingIndex>=sequentialList.size()){
                    capacity=-1;

                    for(unsigned long i=0; i<sequentialList.size(); i++){
                        if((sequentialList[i].second.first == routes[routeIndex][routes[routeIndex].size()-2])
                                ||(sequentialList[i].second.second == routes[routeIndex][routes[routeIndex].size()-2])){
                            sequentialList.erase(sequentialList.begin() + i);
                            i--;
                        }
                    }

                }else{
                    /*Nella soluzione per il file A-n61-k9 la prima stazione da aggiungere dovrebbe essere
                     * la 14, che nel nostro caso si trova in posizione 1670 con un saving value di 0,33129 circa
                     * if((sequentialList[savingIndex].second.first==14 && sequentialList[savingIndex].second.second == 1)
                            ||(sequentialList[savingIndex].second.first==1 && sequentialList[savingIndex].second.second == 14)){
                        float valore = sequentialList[savingIndex].first;
                        int ciao = 0;
                    }*/
                    if((sequentialList[savingIndex].second.first == routes[routeIndex][routes[routeIndex].size()-2])
                            && (capacity-demand[sequentialList[savingIndex].second.second] >= 0)){
                        found=true;
                        isFirst = true;
                    }else if((sequentialList[savingIndex].second.second == routes[routeIndex][routes[routeIndex].size()-2])
                             && (capacity-demand[sequentialList[savingIndex].second.first] >= 0)){
                        found=true;
                        isFirst=false;
                    }else{
                        savingIndex++;
                    }
                }
            }
        }
        routeIndex++;
    }
}

float computeCost(const std::vector<std::vector<float>> &distances, const std::vector<int> &route){
    float cost=0;
    for(unsigned long j=0; j<route.size()-1; j++){
        cost+= distances[j][j+1];
    }
    return cost;
}

void saveResults(const std::vector<std::vector<float> > &distances, const std::vector<std::vector<int> > &routes, std::ofstream &outputFile){
    for(unsigned long i=0; i<routes.size(); i++){
        std::string line = "Route #" + std::to_string(i+1) + " Cost: " + std::to_string(static_cast<int>(computeCost(distances,routes[i]))) + ",   ";
        for(unsigned long j=0; j<routes[i].size(); j++){
            line += " " + std::to_string(routes[i][j]);
        }
        line+="\n";
        outputFile << line;
    }
}

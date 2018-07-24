#ifndef CLARKWRIGHTFUNCTIONS_H
#define CLARKWRIGHTFUNCTIONS_H

#include <vector>
#include <fstream>

void computeDistanceTable(const std::vector<std::pair<int,int>>& coordinates, std::vector<std::vector<float> > &distances);
void computeSavingsTable(const std::vector<std::vector<float> > &distances, std::vector<std::vector<float> > &savings, std::vector<std::pair<float, std::pair<int, int> > > &lista);
void createInitialRoutes(std::vector<std::vector<int>> &routes, unsigned long dimension);
void sequentialClarkAndWright(const std::vector<int> &demand, std::vector<std::pair<float,std::pair<int,int>>> &sequentialList, std::vector<std::vector<int> > &routes);
float computeCost(const std::vector<std::vector<float>> &distances, const std::vector<int> &route);
void saveResults(const std::vector<std::vector<float>> &distances, const std::vector<std::vector<int>> &routes, std::ofstream &outputFile);


#endif // CLARKWRIGHTFUNCTIONS_H

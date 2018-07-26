#ifndef CLARKEWRIGHTFUNCTIONS_H
#define CLARKEWRIGHTFUNCTIONS_H

#include <vector>
#include <fstream>

void computeDistanceTable(const std::vector<std::pair<int,int>>& coordinates, std::vector<std::vector<float> > &distances);
void computeSavingsTable(const std::vector<std::vector<float> > &distances, std::vector<std::vector<float> > &savings, std::vector<std::pair<float, std::pair<int, int> > > &list);
void createInitialRoutes(std::vector<std::vector<int>> &routes, unsigned long dimension);
void sequentialClarkeAndWright(const std::vector<int> &demand, std::vector<std::pair<float,std::pair<int,int>>> &sequentialList, std::vector<std::vector<int> > &routes);
void parallelClarkeAndWright(const std::vector<int> &demand, std::vector<std::pair<float,std::pair<int,int>>> &parallelList, std::vector<std::vector<int> > &routes);
float computeCost(const std::vector<std::vector<float>> &distances, const std::vector<int> &route);
void saveResults(const std::vector<std::vector<float>> &distances, const std::vector<std::vector<int>> &routes, std::ofstream &outputFile, double duration, std::ofstream &finalTableFile, int optimalValue, std::string inputFileName);


#endif // CLARKEWRIGHTFUNCTIONS_H

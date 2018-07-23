#ifndef CLARKWRIGHTFUNCTIONS_H
#define CLARKWRIGHTFUNCTIONS_H

#include <vector>

void computeDistanceTable(const std::vector<std::pair<int,int>>& coordinates, std::vector<std::vector<float> > &distances);
void computeSavingsTable(const std::vector<std::vector<float> > &distances, std::vector<std::vector<float> > &savings, std::vector<std::pair<float, std::pair<int, int> > > &lista);
void createInitialRoutes(std::vector<std::vector<int>> &routes, unsigned long dimension);
void sequentialClarkAndWright(const std::vector<int> &demand, std::vector<std::pair<float,std::pair<int,int>>> &sequentialList, std::vector<std::vector<int> > &routes);


#endif // CLARKWRIGHTFUNCTIONS_H

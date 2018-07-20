#ifndef CLARKWRIGHTFUNCTIONS_H
#define CLARKWRIGHTFUNCTIONS_H

#include <vector>

void computeDistanceTable(const std::vector<std::pair<int,int>>& coordinates, std::vector<std::vector<float> > &distances);
void computeSavingsTable(const std::vector<std::vector<float> > &distances, std::vector<std::vector<float> > &savings);


#endif // CLARKWRIGHTFUNCTIONS_H

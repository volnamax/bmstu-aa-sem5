//
// Created by User on 10.12.2023.
//

#ifndef CPP_KMEANS_H
#define CPP_KMEANS_H

#include <vector>
#include <cstdlib>
#include <random>
#include <set>
#include <vector>


#include "Claster.h"
#include "../in_out_file/Document.h"

std::vector<std::vector<double>> kMeans(const std::vector<std::vector<double>> &docs, int k);


#endif //CPP_KMEANS_H

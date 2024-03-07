//
// Created by User on 28.12.2023.
//

#ifndef CPP_KLASTERING_H
#define CPP_KLASTERING_H

#include "Claster.h"
#include "../in_out_file/io.h"
#include <thread>
#include <vector>
#include <mutex>

#define MAX_DEPTH 1

std::vector<Cluster> hierarchicalClustering(std::vector<Document> &documents, int depth);

void parallelDocClustering(const std::vector<std::string> &filenames,
                           const std::vector<std::string> &filenames_out,
                           int num_threads);

void parallelDocClustering(const std::vector<std::string> &filenames,
                           const std::vector<std::string> &filenames_out,
                           int num_threads, int count_f);

#endif //CPP_KLASTERING_H

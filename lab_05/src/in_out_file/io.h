//
// Created by User on 10.12.2023.
//

#ifndef CPP_IO_H
#define CPP_IO_H

#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Term.h"
#include "Document.h"
#include "../klasters/Claster.h"

std::vector<Document> readDocumentsFromCSV(const std::string &filename);

void saveClustersToJson(const std::vector<Cluster> &clusters,
                        const std::vector<Document> &documents,
                        const std::string &filename);


#endif //CPP_IO_H

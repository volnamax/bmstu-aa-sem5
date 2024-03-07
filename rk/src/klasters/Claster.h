//
// Created by User on 10.12.2023.
//

#ifndef CPP_CLASTER_H
#define CPP_CLASTER_H

#include <vector>
#include <numeric> // Для std::accumulate
#include <algorithm> // Для std::transform
#include <vector>
#include <math.h>

#include "../in_out_file/Document.h"
#include "Kmeans.h"

#include <vector>
#include <thread>
#include <mutex>


struct Cluster {
    std::vector<std::vector<double>> docs;
    std::vector<double> centroid;

    void calculateCentroid() {
        size_t dimensions = docs[0].size();
        centroid.assign(dimensions, 0.0);
        // Сложите все вектора TF-IDF
        for (auto &point: docs) {
            for (size_t i = 0; i < dimensions; ++i) {
                centroid[i] += point[i];
            }
        }
        // Усредните вектор
        for (size_t i = 0; i < dimensions; ++i) {
            centroid[i] /= docs.size();
        }
    }
};

#include <vector>
#include <thread>
#include <mutex>
#include <functional>
void divideCluster_(std::vector<Document> &documents, int depth, int maxDepth, std::vector<Cluster> &clusters);

double cosineDistance(const std::vector<double> &v1, const std::vector<double> &v2);

void hierarchicalClustering_help(const std::vector<std::vector<double>> &docs,
                                 int depth,
                                 int maxDepth,
                                 std::vector<Cluster> &clusters);
//
//class Cluster {
//public:
//    Cluster() {}
//
//    // Конструктор, который принимает вектор документов
//    Cluster(const std::vector<Document>& docs) {
//        for (const auto& doc : docs) {
//            addDocument(doc);
//        }
//    }
//
//    // Добавление документа в кластер
//    void addDocument(const Document& document) {
//        documents.push_back(document);
//    }
//
//    // Получение всех документов в кластере
//    const std::vector<Document>& getDocuments() const {
//        return documents;
//    }
//
//    // Вычисление центроида кластера (среднее значение всех точек)
//    std::vector<double> calculateCentroid() const {
//        if (documents.empty()) {
//            return {};
//        }
//
//        std::vector<double> centroid(documents[0].getTermsVector().size(), 0.0);
//        for (const auto& doc : documents) {
//            auto docVector = doc.getTermsVector();
//            for (size_t i = 0; i < docVector.size(); ++i) {
//                centroid[i] += docVector[i];
//            }
//        }
//
//        // Делим сумму на количество документов, чтобы получить среднее
//        for (auto& val : centroid) {
//            val /= documents.size();
//        }
//
//        return centroid;
//    }
//
//    // Очистка кластера от документов
//    void clear() {
//        documents.clear();
//    }
//
//private:
//    std::vector<Document> documents;
//};
//


#endif //CPP_CLASTER_H

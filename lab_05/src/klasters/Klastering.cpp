//
// Created by User on 28.12.2023.
//

#include "Klastering.h"

std::vector<Cluster> hierarchicalClustering(std::vector<Document> &documents, int depth) {
    std::vector<std::vector<double>> docs;
    for (const auto &doc: documents) {
        docs.push_back(doc.getTermsVector());
    }

    std::vector<Cluster> clusters;
    divideCluster(docs, 0, depth, clusters);

    return clusters;
}




//
//void hierarchicalClustering(std::vector<Document> &documents, int numClusters) {
//    // Преобразование вектора документов в вектор векторов TF-IDF
//    std::vector<std::vector<double>> docs;
//    for (const auto& doc : documents) {
//        docs.push_back(doc.getTermsVector());
//    }
//
//    // Выполнить k-средних
//    std::vector<std::vector<double>> centroids = kMeans(docs, numClusters);
//
//    // Инициализация начальных кластеров
//    std::vector<Cluster> clusters(numClusters);
//    for (int i = 0; i < numClusters; ++i) {
//        clusters[i].centroid = centroids[i];
//    }
//
//    // Назначение документов кластерам
//    for (size_t docIndex = 0; docIndex < docs.size(); ++docIndex) {
//        int closestClusterIndex = 0;
//        double closestDistance = -1.0; // Максимальное косинусное расстояние
//
//        for (int i = 0; i < numClusters; ++i) {
//            double dist = cosineDistance(docs[docIndex], clusters[i].centroid);
//            if (dist > closestDistance) {
//                closestDistance = dist;
//                closestClusterIndex = i;
//            }
//        }
//
//        clusters[closestClusterIndex].points.push_back(docs[docIndex]);
//    }
//
//    // Вывод результатов кластеризации
//    for (int i = 0; i < numClusters; ++i) {
//        std::cout << "KLASTER " << i + 1 << ":" << std::endl;
//        for (size_t j = 0; j < clusters[i].points.size(); ++j) {
//            // Найти исходный документ, соответствующий этому TF-IDF вектору
//            for (size_t k = 0; k < documents.size(); ++k) {
//                if (docs[k] == clusters[i].points[j]) {
//                    std::cout << "DOC : " << documents[k].getNameDoc() << std::endl;
//                    break;
//                }
//            }
//        }
//    }
//}
// Функция для выполнения иерархической кластеризации

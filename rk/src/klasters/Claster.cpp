//
// Created by User on 10.12.2023.
//

#include "Claster.h"

//косинусное расстояние:
double cosineDistance(const std::vector<double> &v1, const std::vector<double> &v2) {
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0;
    for (unsigned int i = 0; i < v1.size(); ++i) {
        dot += v1[i] * v2[i];
        denom_a += v1[i] * v1[i];
        denom_b += v2[i] * v2[i];
    }
    double denom = (sqrt(denom_a) * sqrt(denom_b));
    return denom == 0.0 ? 0.0 : dot / denom;
}


void divideClusterParallel(const std::vector<std::vector<double>> &points,
                           int depth,
                           int maxDepth,
                           std::vector<Cluster> &clusters,
                           std::mutex &mutex,
                           int numThreads);

std::vector<Cluster> hierarchicalClusteringParallel(std::vector<Document> &documents, int depth, int numThreads) {
    std::vector<std::vector<double>> docs;
    for (const auto &doc: documents) {
        docs.push_back(doc.getTermsVector());
    }

    std::vector<Cluster> clusters;
    std::mutex mutex;
    divideClusterParallel(docs, 0, depth, clusters, mutex, numThreads);

    return clusters;
}

void divideClusterParallel(const std::vector<std::vector<double>> &points,
                           int depth,
                           int maxDepth,
                           std::vector<Cluster> &clusters,
                           std::mutex &mutex,
                           int numThreads) {
    if (depth == maxDepth) {
        std::lock_guard<std::mutex> lock(mutex);
        Cluster cluster;
        cluster.docs = points;
        cluster.calculateCentroid();
        clusters.push_back(cluster);
        return;
    }

    // Применяем k-средних для разделения на 2 кластера
    std::vector<std::vector<double>> centroids = kMeans(points, 2);
    std::vector<std::vector<double>> cluster1Points, cluster2Points;

    // Разделение точек на кластеры, возможно, с использованием нескольких потоков
    auto assignPoints = [&](int start, int end) {
        for (int i = start; i < end; ++i) {
            if (cosineDistance(points[i], centroids[0]) < cosineDistance(points[i], centroids[1])) {
                cluster1Points.push_back(points[i]);
            } else {
                cluster2Points.push_back(points[i]);
            }
        }
    };

    std::vector<std::thread> threads;
    int blockSize = points.size() / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int start = i * blockSize;
        int end = (i == numThreads - 1) ? points.size() : (i + 1) * blockSize;
        threads.emplace_back(assignPoints, start, end);
    }

    for (auto &t : threads) {
        t.join();
    }

    // Рекурсивное деление
    if (numThreads > 1) {
        std::thread t1(divideClusterParallel, std::ref(cluster1Points), depth + 1, maxDepth, std::ref(clusters), std::ref(mutex), numThreads / 2);
        std::thread t2(divideClusterParallel, std::ref(cluster2Points), depth + 1, maxDepth, std::ref(clusters), std::ref(mutex), numThreads / 2);
        t1.join();
        t2.join();
    } else {
        divideClusterParallel(cluster1Points, depth + 1, maxDepth, clusters, mutex, numThreads);
        divideClusterParallel(cluster2Points, depth + 1, maxDepth, clusters, mutex, numThreads);
    }
}


void hierarchicalClustering_help(const std::vector<std::vector<double>> &docs,
                                 int depth,
                                 int maxDepth,
                                 std::vector<Cluster> &clusters) {
    if (depth == maxDepth) {
        // Добавляем конечные кластеры
        Cluster cluster;
        cluster.docs = docs;
        cluster.calculateCentroid();
        clusters.push_back(cluster);
        return;
    }

    // Применяем k-средних для разделения на 2 кластера
    std::vector<std::vector<double>> centroids = kMeans(docs, 2);
    std::vector<std::vector<double>> cluster1Docs, cluster2Docs;

    for (const auto &doc: docs) {
        if (cosineDistance(doc, centroids[0]) < cosineDistance(doc, centroids[1])) {
            cluster1Docs.push_back(doc);
        }
        else {
            cluster2Docs.push_back(doc);
        }
    }

    // Рекурсивно разделяем каждый подкластер
    hierarchicalClustering_help(cluster1Docs, depth + 1, maxDepth, clusters);
    hierarchicalClustering_help(cluster2Docs, depth + 1, maxDepth, clusters);
}



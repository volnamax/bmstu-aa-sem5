std::vector<std::vector<double>> kMeans(const std::vector<std::vector<double>> &docs, int k) {
    int n = docs.size();
    std::vector<std::vector<double>> centroids(k, std::vector<double>(docs[0].size()));
    std::vector<int> assignments(n, 0);
    // Инициализация центроидов
    for (int i = 0; i < k; ++i) {
        centroids[i] = docs[rand() % n];
    }
    bool changed;
    do {
        changed = false;
        // Назначение точек кластерам
        for (int i = 0; i < n; ++i) {
            double bestDist = -1.0;
            int bestCluster = 0;
            for (int j = 0; j < k; ++j) {
                double dist = cosineDistance(docs[i], centroids[j]);
                if (dist > bestDist) {
                    bestDist = dist;
                    bestCluster = j;
                }
            }
            if (assignments[i] != bestCluster) {
                assignments[i] = bestCluster;
                changed = true;
            }
        }
        // Обновление центроидов
        std::vector<int> counts(k, 0);
        std::vector<std::vector<double>> newCentroids(k, std::vector<double>(docs[0].size(), 0.0));
        for (int i = 0; i < n; ++i) {
            for (size_t j = 0; j < docs[i].size(); ++j) {
                newCentroids[assignments[i]][j] += docs[i][j];
            }
            counts[assignments[i]]++;
        }
        for (int j = 0; j < k; ++j) {
            if (counts[j] != 0) {
                for (size_t m = 0; m < newCentroids[j].size(); ++m) {
                    newCentroids[j][m] /= counts[j];
                }
            }
            else {
                newCentroids[j] = centroids[j]; 
            }
        }
        centroids = newCentroids;
    } while (changed);

    return centroids;
}
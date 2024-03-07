MAXITER // -5
docs // -3
k   // -4
int n = docs.size // -1
std::vector<std::vector<double>> centroids(k, std::vector<double>(docs[0].size())); // -2 
std::vector<std::vector<double>> kMeans(const std::vector<std::vector<double>> &docs, int n, std::vector<std::vector<double>> centroids, int k,) {
    // центроиды проинициализированы случ значениями
    size_t iter = 0; // 0
    std::vector<int> assignments(n, 0); // 1
    bool changed;                      // 2
    do {                              // 3
        changed = false;             // 4
        // Назначение точек кластерам
        for (int i = 0; i < n; ++i) {        // 5
            double bestDist = -1.0;         // 6
            int bestCluster = 0;           // 7
            for (int j = 0; j < k; ++j) { // 8
                double dist = cosineDistance(docs[i], centroids[j]);    // 9
                if (dist > bestDist) {   // 10
                    bestDist = dist;    // 11
                    bestCluster = j;   // 12
                }
            }
            if (assignments[i] != bestCluster) { // 13
                assignments[i] = bestCluster;   // 14
                changed = true;                // 15
            }
        }
        // Обновление центроидов
        centroids = updateCentroids(docs, assignments, k); // 16
    } while (changed && ++iter != MAXITER ); // 17
    return centroids;// 18 
    }
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
    hierarchicalClustering_help(docs, 0, depth, clusters);

    return clusters;
}



void processDocuments(const std::vector<std::string> &filenames,
                      const std::vector<std::string> &filenames_out,
                      int start_index, int end_index,
                      std::mutex &io_mutex) {
    for (int i = start_index; i < end_index; ++i) {
        // Загрузка и обработка документа
        std::vector<Document> documents = readDocumentsFromCSV(filenames[i]);
        standardizeDocumentLengths(documents);

        // Выполнение иерархической кластеризации
        std::vector<Cluster> clusters = hierarchicalClustering(documents, MAX_DEPTH);

        // Синхронизированное сохранение результатов
        std::lock_guard<std::mutex> lock(io_mutex);
        saveClustersToJson(clusters, documents, filenames_out[i]);
    }
}


void parallelDocClustering(const std::vector<std::string> &filenames,
                           const std::vector<std::string> &filenames_out,
                           int num_threads, int count_f) {
    std::mutex io_mutex;

    // Расчет размера подгруппы для каждого потока
    int chunk_size = count_f / num_threads;
    std::thread threads[num_threads]; // Массив потоков

    int start_index = 0;
    for (int i = 0; i < num_threads; ++i) {
        int end_index = start_index + chunk_size + (i < count_f % num_threads ? 1 : 0);

        // Создание потока для обработки подгруппы документов
        threads[i] = std::thread(processDocuments, std::ref(filenames), std::ref(filenames_out),
                                 start_index, end_index, std::ref(io_mutex));
        start_index = end_index;
    }

    // Дождаться завершения всех потоков
    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }
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
//        clusters[closestClusterIndex].docs.push_back(docs[docIndex]);
//    }
//
//    // Вывод результатов кластеризации
//    for (int i = 0; i < numClusters; ++i) {
//        std::cout << "KLASTER " << i + 1 << ":" << std::endl;
//        for (size_t j = 0; j < clusters[i].docs.size(); ++j) {
//            // Найти исходный документ, соответствующий этому TF-IDF вектору
//            for (size_t k = 0; k < documents.size(); ++k) {
//                if (docs[k] == clusters[i].docs[j]) {
//                    std::cout << "DOC : " << documents[k].getNameDoc() << std::endl;
//                    break;
//                }
//            }
//        }
//    }
//}
// Функция для выполнения иерархической кластеризации

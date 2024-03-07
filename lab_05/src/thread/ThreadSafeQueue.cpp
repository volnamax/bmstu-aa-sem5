//
// Created by User on 28.12.2023.
//

#include "ThreadSafeQueue.h"

// Функция обслуживания 1 - чтение из файла и помещение в очереди
void serviceRead(const std::vector<std::string>& filenames, ThreadSafeQueue<std::vector<Document>> &readQueue, ThreadSafeQueue<std::vector<Document>> &documentQueue, int f_count) {
    for (int i = 0; i < f_count; ++i) {
        std::vector<Document> documents = readDocumentsFromCSV(filenames[i]);
        readQueue.push(documents);
        documentQueue.push(documents); // Добавляем в новую очередь
    }
}

// Функция обслуживания 2 - кластеризация
void serviceCluster(ThreadSafeQueue<std::vector<Document>>
                    &readQueue,
                    ThreadSafeQueue<std::vector<Cluster>> &writeQueue,
                    int depth) {
    while (!readQueue.empty()) {
        auto documents = readQueue.pop();
        standardizeDocumentLengths(documents);
        auto clusters = hierarchicalClustering(documents, depth);
        writeQueue.push(clusters);
    }
}

void serviceWrite(ThreadSafeQueue<std::vector<Cluster>>& clusterQueue, ThreadSafeQueue<std::vector<Document>>& documentQueue, const std::vector<std::string> filenames_out, std::atomic<bool>& done) {
    while (!done || !clusterQueue.empty()) {
        if (!clusterQueue.empty() && !documentQueue.empty()) {
            auto clusters = clusterQueue.pop();
            auto documents = documentQueue.pop();

            saveClustersToJson(clusters, documents, filenames_out[0]);

            std::cout << "Результаты сохранены в файл: " << filenames_out[0] << std::endl;
        }
    }

    // Обработка оставшихся элементов в очереди после установки флага done
    while (!clusterQueue.empty() && !documentQueue.empty()) {
        auto clusters = clusterQueue.pop();
        auto documents = documentQueue.pop();

        saveClustersToJson(clusters, documents, filenames_out[0]);

        std::cout << "Результаты сохранены в файл: " << filenames_out[0] << std::endl;
    }
}
timespec get_time() {
    timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return time;
}
double diff_timespec(const timespec &end, const timespec &start) {
    return ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_nsec - start.tv_nsec) / 1000000.0);
}



void device1(AtomicQueue<Request> &from, AtomicQueue<Request> &to) {
//  std::cout  << "new request\n";

    while (true) {
        Request req = from.pop();
        if (req.is_last) {
            to.push(req);
            break;
        }

        req.time_start_1 = get_time();
        req.documents = readDocumentsFromCSV(req.filename_in);
        standardizeDocumentLengths(req.documents);
        req.time_end_1 = get_time();

        to.push(req);
//        std::cout  << "device1 = "<< diff_timespec(req.time_end_1, req.time_start_1)<< "\n";

    }
}

void device2(AtomicQueue<Request> &from, AtomicQueue<Request> &to) {
    while (true) {
        Request req = from.pop();
        if (req.is_last) {
            to.push(req);
            break;
        }

        req.time_start_2 = get_time();
        req.clusters = hierarchicalClustering(req.documents, MAX_DEPTH);
        req.time_end_2 = get_time();

        to.push(req);
//        std::cout << "device2 = " << diff_timespec(req.time_end_2, req.time_start_2) << "\n";
    }
}

void device3(AtomicQueue<Request> &from, AtomicQueue<Request> &completedRequests) {
    while (true) {
        Request req = from.pop();
        if (req.is_last) {
            break;
        }

        req.time_start_3 = get_time();
        saveClustersToJson(req.clusters, req.documents, req.filename_out);
        req.time_end_3 = get_time();
        completedRequests.push(req);

//        std::cout << "device3 = "<<diff_timespec(req.time_end_3, req.time_start_3)<< "\n";
    }
}


void generator(AtomicQueue<Request> &q, const std::vector<std::string> &filenames,
               const std::vector<std::string> &filenames_out, int count_f) {
    for (size_t i = 0; i < count_f; ++i) {
        q.push({{}, {}, filenames[i], filenames_out[i]});
    }
    // Посылаем сигнал о завершении для каждого потока device1
    q.push({{}, {}, "", "", true}); // Для первого потока device1
    q.push({{}, {}, "", "", true}); // Для второго потока device1
}

void run_pipeline(const std::vector<std::string> &filenames, const std::vector<std::string> &filenames_out, int count_f,
                  AtomicQueue<Request> &completedRequests) {
        AtomicQueue<Request> queue1, queue2, queue3;

    std::thread genThread(generator, std::ref(queue1), std::ref(filenames), std::ref(filenames_out), count_f);
    std::thread t1(device1, std::ref(queue1), std::ref(queue2));
    std::thread t1_2(device1, std::ref(queue1), std::ref(queue2));
    std::thread t2(device2, std::ref(queue2), std::ref(queue3));
    std::thread t3(device3, std::ref(queue3), std::ref(completedRequests));
    genThread.join();
    t1.join();
    t1_2.join();
    t2.join();
    t3.join();
}

#include <iomanip> // Для std::setw и std::setprecision

void createReport(AtomicQueue<Request> &requests) {
    std::cout << std::left; // Выравнивание текста по левому краю
    std::cout << "| " << std::setw(5) << "N" << " | "
              << std::setw(15) << "Time 1 (ms)" << " | "
              << std::setw(15) << "Time 2 (ms)" << " | "
              << std::setw(15) << "Time 3 (ms)" << " |"
              << std::setw(15) << "Total Time (ms)" << " |" << std::endl;

    double totalDuration1 = 0.0;
    double totalDuration2 = 0.0;
    double totalDuration3 = 0.0;
    double totalOverallTime = 0.0;

    int requestCount = requests.size();

    for (int i = 0; i < requestCount; ++i) {
        Request req = requests.pop();

        double duration1 = diff_timespec(req.time_end_1, req.time_start_1) ; // В миллисекундах
        double duration2 = diff_timespec(req.time_end_2, req.time_start_2) ;
        double duration3 = diff_timespec(req.time_end_3, req.time_start_3) ;
        double totalDuration = duration1 + duration2 + duration3;

        totalDuration1 += duration1;
        totalDuration2 += duration2;
        totalDuration3 += duration3;
        totalOverallTime += totalDuration;

        std::cout << "| " << std::setw(5) << i + 1 << " | "
                  << std::setw(15) << std::fixed << std::setprecision(2) << duration1 << " | "
                  << std::setw(15) << duration2 << " | "
                  << std::setw(15) << duration3 << " |"
                  << std::setw(15) << totalDuration << " |" << std::endl;
    }

    std::cout << "Average Time 1: " << std::fixed << std::setprecision(2) << (totalDuration1 / requestCount) << " ms\n";
    std::cout << "Average Time 2: " << (totalDuration2 / requestCount) << " ms\n";
    std::cout << "Average Time 3: " << (totalDuration3 / requestCount) << " ms\n";
    std::cout << "Total Overall Time: " << totalOverallTime << " ms\n";
}


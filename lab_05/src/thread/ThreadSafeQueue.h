//
// Created by User on 28.12.2023.
//

#ifndef CPP_THREADSAFEQUEUE_H
#define CPP_THREADSAFEQUEUE_H

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "Atomic.h"
#define MAX_DEPTH 2
#include "../in_out_file/Document.h"
#include "../in_out_file/io.h"
#include "../klasters/Claster.h"
#include "../klasters/Klastering.h"

// Потокобезопасная очередь
template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cond_var;

public:
    void push(T value) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(value);
        cond_var.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mutex);
        cond_var.wait(lock, [this] { return !queue.empty(); });
        T value = queue.front();
        queue.pop();
        return value;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }
};

void serviceRead(const std::vector<std::string> &filenames, ThreadSafeQueue<std::vector<Document>> &readQueue,
                 ThreadSafeQueue<std::vector<Document>> &documentQueue, int f_count);


void serviceCluster(ThreadSafeQueue<std::vector<Document>>
                    &readQueue,
                    ThreadSafeQueue<std::vector<Cluster>> &writeQueue,
                    int depth);

void
serviceWrite(ThreadSafeQueue<std::vector<Cluster>> &clusterQueue, ThreadSafeQueue<std::vector<Document>> &documentQueue,
             const std::vector<std::string> filenames_out, std::atomic<bool> &done);


#include <ctime>



struct Request {
    std::vector<Document> documents;
    std::vector<Cluster> clusters;
    std::string filename_in;
    std::string filename_out;
    bool is_last = false;
    // Временные метки для каждого этапа
    timespec time_start_1, time_end_1; // Для device1
    timespec time_start_2, time_end_2; // Для device2
    timespec time_start_3, time_end_3; // Для device3
};

void createReport(AtomicQueue <Request> &requests);

void run_pipeline(const std::vector<std::string> &filenames, const std::vector<std::string> &filenames_out, int count_f,
                  AtomicQueue <Request> &completedRequests);

void device3(AtomicQueue <Request> &from, AtomicQueue <Request> &completedRequests);

void device2(AtomicQueue <Request> &from, AtomicQueue <Request> &to);

void device1(AtomicQueue <Request> &from, AtomicQueue <Request> &to);

#endif //CPP_THREADSAFEQUEUE_H

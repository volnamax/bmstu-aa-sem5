//
// Created by User on 03.01.2024.
//

#ifndef CPP_ATOMIC_H
#define CPP_ATOMIC_H


#include <queue>
#include <mutex>
#include <stdexcept>


#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class AtomicQueue {
private:
    std::queue<T> queue;
    mutable std::mutex mtx;
    std::condition_variable cv;

public:
    // Добавить элемент в очередь
    void push(const T& value) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            queue.push(value);
        }
        cv.notify_one();
    }

    // Извлечь элемент из очереди
    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]{ return !queue.empty(); });
        T value = queue.front();
        queue.pop();
        return value;
    }

    // Проверить, пуста ли очередь
    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }

    // Получить размер очереди
    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.size();
    }
};



#endif //CPP_ATOMIC_H

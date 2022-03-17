#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class SafeQueue {
    public:
        SafeQueue(void)
            : q()
            , m()
            , c()
        {}

        void enqueue(T t) {
            std::lock_guard<std::mutex> lock(m);
            q.push(t);
            c.notify_one();
        }

        void pop() {
            q.pop();
        }

        // front() and pop()
        T dequeue() {
            std::unique_lock<std::mutex> lock(m);
            while (q.empty()) {
                c.wait(lock);
            }
            T val = q.front();
            q.pop();
            return val;
        }

        bool empty() {
            return q.empty();
        }

        float size() {
            return q.size();
        }

        T front() {
            return q.front();
        }

    private:
        std::queue<T> q;
        mutable std::mutex m;
        std::condition_variable c;
};
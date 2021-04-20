#pragma once
#include <condition_variable>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <list>
#include <functional>
#include <atomic>
#include <vector>
#include <iostream>

#include "figures.h"

class Handler {
	using FigPtr = std::shared_ptr<Figure>;
    std::mutex               mutex;
    std::thread              thread;
    std::condition_variable  condVar;
    std::vector<FigPtr>      figures;
    std::vector <std::function <void(std::vector<FigPtr>&)> >
	                         handlers;
							 
    size_t max = 0;

public:
    bool running;

    Handler(size_t size = 3)
	  : max(size),
	    running(true),
		thread(std::thread(Printing, this))
	{}

    ~Handler() {
        running = false;
        condVar.notify_one();
        thread.join();
    }

    void AddFuction(std::function <void(const std::vector<FigPtr>&)>&& func) {
        handlers.push_back(func);
    }

    void Push(FigPtr fig) {
        std::unique_lock<std::mutex> uLock(mutex);
        figures.push_back(fig);
        if (IsFull()) {
            condVar.notify_one();
            condVar.wait(uLock, [this]() {
                return figures.empty();
            });
        }
    }

    bool IsFull() {
        return figures.size() >= max;
    }

    static void Printing(Handler* t) {
        while (t->running) {
            std::unique_lock<std::mutex> lock(t->mutex);
            t->condVar.wait(lock, [t]() {
                return t->IsFull()||!t->running;
            });
            for (auto& item : t->handlers) {
                item(t->figures);
            }

            t->figures.clear();
            lock.unlock();
            t->condVar.notify_one();
        }
    }

};
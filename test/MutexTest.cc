// Copyright (c) 2010
// All rights reserved.

#include <mutex>
#include <thread>
#include <iostream>
#include <atomic>

#include "gtest/gtest.h"

volatile int counter(0);  // non-atomic counter
std::mutex mtx;           // locks access to counter

void attempt_10k_increases() {
    for (int i = 0; i < 10000; ++i) {
        std::lock_guard<std::mutex> lck(mtx);
        // if (mtx.try_lock()) {   // only increase if currently not locked:
            ++counter;
        //     mtx.unlock();
        // }
    }
}

TEST(MutexTest, mutexTest) {
    std::thread threads[10];
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(attempt_10k_increases);
    }

    for (auto& th : threads) {
        th.join();
    }

    EXPECT_EQ(counter, 100000);
}

std::timed_mutex tm_mtx;

void fireworks() {
  // waiting to get a lock: each thread prints "-" every 200ms:
  while (!tm_mtx.try_lock_for(std::chrono::milliseconds(200))) {
    // std::cout << "-";
  }
  // got a lock! - wait for 1s, then this thread prints "*"
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "*\n";
  tm_mtx.unlock();
}

TEST(MutexTest, timedMutexTest) {
    std::thread threads[10];
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(fireworks);
    }

    for (auto& th : threads) {
        th.join();
    }

    SUCCEED();
}


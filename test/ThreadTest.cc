// Copyright (c) 2010
// All rights reserved.

#include <thread>
#include <iostream>
#include <atomic>

#include "gtest/gtest.h"

void thread_task() {
  std::cout << "hello thread!!!" << std::endl;
}

void f1(int n) {
  for (int i = 0; i < 5; ++i) {
    std::cout << "Thread " << n << " executing\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void f2(int& n) {  // NOLINT
  for (int i = 0; i < 5; ++i) {
    std::cout << "Thread 2 executing\n"; ++n;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

TEST(ThreadTest, globalFuncTest) {
  std::thread t(thread_task);
  t.join();

  int n = 0;
  std::thread t1;  // t1 is not a thread
  std::thread t2(f1, n + 1);  // pass by value
  std::thread t3(f2, std::ref(n));  // pass by reference

  // t4 is now running f2().
  // t3 is no longer a thread
  std::thread t4(std::move(t3));

  t2.join();
  t4.join();

  EXPECT_EQ(n, 5);
}

void threads_task(int n) {
  std::this_thread::sleep_for(std::chrono::seconds(n));
  std::cout << "hello thread "
            << std::this_thread::get_id()
            << " paused " << n << " seconds"
            << std::endl;
}

TEST(ThreadTest, groupTest) {
  std::thread threads[5];
  std::cout << "Spawning 5 threads...\n";
  for (int i = 0; i < 5; i++) {
    threads[i] = std::thread(threads_task, i + 1);
  }

  std::cout << "Done spawning threads! Now wait for them to join\n";
  for (auto& t : threads) {
    t.join();
  }

  SUCCEED();
}

std::atomic<int> global_counter(0);

void increase_global(int n) {
  for (int i=0; i < n; ++i)
    ++global_counter;
}

void increase_reference(std::atomic<int>& variable, int n) {  // NOLINT
  for (int i=0; i < n; ++i)
    ++variable;
}

struct C : std::atomic<int> {
  C() : std::atomic<int>(0) {}

  void increase_member(int n) {
    for (int i=0; i < n; ++i)
      fetch_add(1);
  }
};

TEST(ThreadTest, increaseTest) {
  std::vector<std::thread> threads;

  std::cout << "increase global counter with 10 threads...\n";
  for (int i=1; i <= 10; ++i) {
    threads.push_back(std::thread(increase_global, 1000));
  }

  std::cout << "increase counter (foo) with 10 threads using reference...\n";
  std::atomic<int> foo(0);
  for (int i=1; i <= 10; ++i) {
    threads.push_back(std::thread(increase_reference, std::ref(foo), 1000));
  }

  std::cout << "increase counter (bar) with 10 threads using member...\n";
  C bar;
  for (int i=1; i <= 10; ++i) {
    threads.push_back(std::thread(&C::increase_member, &bar, 1000));
  }

  std::cout << "synchronizing all threads...\n";
  for (auto& th : threads) {
    th.join();
  }

  EXPECT_EQ(global_counter, 10000);
  EXPECT_EQ(foo, 10000);
  EXPECT_EQ(bar, 10000);
}

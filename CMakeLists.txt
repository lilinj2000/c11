cmake_minimum_required(VERSION 2.8)

project(c11)

set(home_3rd "$ENV{HOME}/3rd")

# googltest set
set(home_googletest "${home_3rd}/googletest")
set(GTEST_INCLUDE_PATH "${home_googletest}/include" CACHE STRING "googletest include path")
set(GTEST_LIB_PATH "${home_googletest}/lib" CACHE STRING "googletest lib path")
include_directories(${GTEST_INCLUDE_PATH})
# link_directories(${GTEST_LIB_PATH})

# We need thread support
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

function(cxx_test name)
    add_executable(${name} ${ARGN})
    target_link_libraries(${name} 
        ${GTEST_LIB_PATH}/libgtest.a 
        ${GTEST_LIB_PATH}/libgtest_main.a)
    target_link_libraries(${name} ${CMAKE_THREAD_LIBS_INIT})
    add_test(${name} ${name})
endfunction()

enable_testing()

cxx_test(chrono_test test/ChronoTest.cc)
cxx_test(array_test test/ArrayTest.cc)
cxx_test(auto_test test/AutoTest.cc)
cxx_test(io_test test/IOTest.cc)
cxx_test(set_test test/SetTest.cc)
cxx_test(type_info_test test/TypeInfoTest.cc)
cxx_test(lambda_test test/LambdaTest.cc)
cxx_test(alignof_test test/AlignofTest.cc)
cxx_test(thread_test test/ThreadTest.cc)
cxx_test(mutex_test test/MutexTest.cc)
cxx_test(all_test test/AllTest.cc)



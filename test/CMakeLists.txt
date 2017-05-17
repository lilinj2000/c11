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

cxx_test(chrono_test ChronoTest.cc)
cxx_test(array_test ArrayTest.cc)
cxx_test(auto_test AutoTest.cc)
cxx_test(io_test IOTest.cc)
cxx_test(set_test SetTest.cc)
cxx_test(type_info_test TypeInfoTest.cc)
cxx_test(lambda_test LambdaTest.cc)
cxx_test(all_test AllTest.cc)

# add_executable(chrono_test ChronoTest.cc)



cmake_minimum_required(VERSION 3.0.0)
project(accelerate_programing VERSION 0.1.0)

# include(CTest)
# enable_testing()

# add_executable(accelerate_programing main.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

###############################################################################
# C++ core
###############################################################################
message(STATUS "========== [START] C++ Build Core ==========")

add_subdirectory(ch2_simple_accelerate)

message(STATUS "========== [END] C++ Build Core ==========")
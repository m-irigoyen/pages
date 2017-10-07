#########
# SCENELIB #
#########

cmake_minimum_required(VERSION 3.1)

# mutils
SET(LIB_NAME "scenelib")

set (CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

FILE(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/scenelib/*.hpp)

add_library(${LIB_NAME} ${SRC} ${HEADERS})

target_link_libraries(${LIB_NAME} mutils)

# CATCH unit tests
# include_directories(${CATCH_INCLUDE_DIR})

# FILE(GLOB_RECURSE SRC_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/src/*tests.cpp)
# add_executable("mutils-tests" tests/maintests.cpp ${SRC_TESTS})
# target_link_libraries("mutils-tests" mutils)

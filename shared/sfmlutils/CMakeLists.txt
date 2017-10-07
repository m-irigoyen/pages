#########
# SFMLUTILS #
#########

cmake_minimum_required(VERSION 3.1)

SET(LIB_NAME "sfmlutils")

set (CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
include_directories(${MUTILS_INCLUDE_DIR})

FILE(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/sfmlutils/*.hpp)

add_library(${LIB_NAME} ${SRC} ${HEADERS})

target_link_libraries(${LIB_NAME} mutils)


# SFML
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)
if (SFML_FOUND)
   include_directories(${SFML_INCLUDE_DIR})
   target_link_libraries(${LIB_NAME} ${SFML_LIBRARIES})
else()
	MESSAGE("SFML not found, fix your environment variables or specify it manually")
endif()

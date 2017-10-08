#########
# pages #
#########

cmake_minimum_required(VERSION 3.1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

SET(EXE_NAME "pages")
SET(PROJECT_NAME ${EXE_NAME}-dev)

Project(${PROJECT_NAME})

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmakeconfig")

# Shared libraries
SET (MUTILS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/shared/mutils/include")
SET (SCENELIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/shared/scenelib/include")
SET (SFMLUTILS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/shared/sfmlutils/include")
SET (SFMLTEMPLATE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/shared/sfmltemplate/include")
SET (CATCH_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/shared/catch/include")

include_directories(${MUTILS_INCLUDE_DIR}
	${SCENELIB_INCLUDE_DIR}
	${SFMLUTILS_INCLUDE_DIR}
	${SFMLTEMPLATE_INCLUDE_DIR}
	${CATCH_INCLUDE_DIR})

add_subdirectory(shared/mutils)
add_subdirectory(shared/scenelib)
add_subdirectory(shared/sfmlutils)
add_subdirectory(shared/sfmltemplate)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}src)
FILE(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

add_executable(${EXE_NAME} ${SRC} ${HEADERS})

target_link_libraries(${EXE_NAME} "mutils" "scenelib" "sfmlutils" "sfmltemplate")

# SFML
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)
if (SFML_FOUND)
   include_directories(${SFML_INCLUDE_DIR})
   target_link_libraries(${EXE_NAME} ${SFML_LIBRARIES})
endif()

set_target_properties(mutils PROPERTIES FOLDER shared)
set_target_properties(scenelib PROPERTIES FOLDER shared)
set_target_properties(sfmlutils PROPERTIES FOLDER shared)
set_target_properties(sfmltemplate PROPERTIES FOLDER shared)

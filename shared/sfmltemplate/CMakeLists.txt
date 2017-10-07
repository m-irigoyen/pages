#########
# SFMLTEMPLATE #
#########

cmake_minimum_required(VERSION 3.1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

SET(LIB_NAME "sfmltemplate")

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmakeconfig")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#headers
FILE(GLOB_RECURSE HEADERS_CORE
	${CMAKE_CURRENT_SOURCE_DIR}/include/sfmltemplate/core/*.hpp)

SET (HEADERS_GUI
	${CMAKE_CURRENT_SOURCE_DIR}/include/sfmltemplate/gui/abstractradiobutton.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/sfmltemplate/gui/abstractinteractable.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/sfmltemplate/gui/abstractpushbutton.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/sfmltemplate/gui/abstracttextbox.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/sfmltemplate/gui/abstracttogglebutton.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/sfmltemplate/gui/scenegraph.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/sfmltemplate/gui/radiobuttongroup.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/sfmltemplate/gui/scenenode.hpp
	)
FILE(GLOB_RECURSE
	HEADERS_GUI_DRA	${CMAKE_CURRENT_SOURCE_DIR}/include/sfmltemplate/gui/drawables/*.hpp)
FILE(GLOB_RECURSE
	HEADERS_GUI_NOD	${CMAKE_CURRENT_SOURCE_DIR}/include/sfmltemplate/gui/nodes/*.hpp)
FILE(GLOB_RECURSE
	HEADERS_GUI_SHA ${CMAKE_CURRENT_SOURCE_DIR}/include/sfmltemplate/gui/shaders/*.hpp)
# source files
FILE(GLOB_RECURSE SRC_CORE
	${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp)

SET(SRC_GUI
	${CMAKE_CURRENT_SOURCE_DIR}/src/gui/abstractradiobutton.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/gui/abstractinteractable.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/gui/abstractpushbutton.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/gui/abstracttextbox.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/gui/abstracttogglebutton.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/gui/scenegraph.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/gui/radiobuttongroup.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/gui/scenenode.cpp)
FILE(GLOB_RECURSE SRC_GUI_DRA ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/drawables/*.cpp)
FILE(GLOB_RECURSE SRC_GUI_NOD ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/nodes/*.cpp)


add_library(${LIB_NAME}
	${SRC_CORE}
	${SRC_GUI} ${SRC_GUI_DRA} ${SRC_GUI_NOD}
	${HEADERS_CORE}
	${HEADERS_GUI} ${HEADERS_GUI_DRA} ${HEADERS_GUI_NOD} ${HEADERS_GUI_SHA})

target_link_libraries(${LIB_NAME} "mutils" "sfmlutils")

# SFML
find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)
if (SFML_FOUND)
   include_directories(${SFML_INCLUDE_DIR})
   target_link_libraries(${LIB_NAME} ${SFML_LIBRARIES})
endif()

# Source grouping

SET(F_H "Headers")
SET(F_S "Sources")
SET(SOURCE_GROUP_DELIMITER "/")
source_group(${F_H}/core FILES ${HEADERS_CORE})
source_group(${F_H}/gui FILES ${HEADERS_GUI})
source_group(${F_H}/gui/drawables FILES ${HEADERS_GUI_DRA})
source_group(${F_H}/gui/nodes FILES ${HEADERS_GUI_NOD})
source_group(${F_H}/gui/shaders FILES ${HEADERS_GUI_SHA})
source_group(${F_S}/core FILES ${SRC_CORE})
source_group(${F_S}/gui FILES ${SRC_GUI})
source_group(${F_S}/gui/drawables FILES ${SRC_GUI_DRA})
source_group(${F_S}/gui/nodes FILES ${SRC_GUI_NOD})

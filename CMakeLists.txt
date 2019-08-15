cmake_minimum_required(VERSION 2.8)

project(BaluEngine)

file(GLOB_RECURSE ${PROJECT_NAME}_SRC
    "Source/*.h"
    "Source/*.cpp"
	"submodules/pugixml/src/*.cpp"
	"submodules/poly2tri/poly2tri/**/*.cpp"
	"submodules/nanovg/src/*.cpp"
)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "-g -std=c++11 -w -pedantic")
endif()

include_directories("Include")
include_directories("Source")
include_directories("submodules/BaluRender/easyloggingpp/src")
include_directories("submodules/nanovg/src")
include_directories("submodules/poly2tri/poly2tri")
include_directories("submodules/pugixml/src")

add_definitions(-DBALUENGINEDLL_EXPORTS -DBALUENGINE_DESIGN_TIME -DNANOVG_GLEW)

if (NOT TARGET BaluLib)
add_subdirectory(submodules/BaluRender/BaluLib)
include_directories(${BaluLib_SOURCE_DIR}/Include)
endif()

if (NOT TARGET BaluRender)
add_subdirectory(submodules/BaluRender)
include_directories(${BaluRender_SOURCE_DIR}/Include)
endif()
if (NOT TARGET BaluScript)
add_subdirectory(submodules/BaluScript)
include_directories(${BaluScript_SOURCE_DIR}/Include)
endif()

file(GLOB_RECURSE ${PROJECT_NAME}_SRC
    "submodules/Box2D/Box2D/*.h"
    "submodules/Box2D/Box2D/*.cpp"
)

include_directories("submodules/Box2D/Box2D")
include_directories("submodules/Box2D/Box2D/Box2D")

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(DevIL REQUIRED)
include_directories(${IL_INCLUDE_DIR})

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${${PROJECT_NAME}_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})

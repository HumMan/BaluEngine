cmake_minimum_required(VERSION 2.8)

project(BaluEngine)

file(GLOB_RECURSE ${PROJECT_NAME}_SRC
    "Source/*.h"
    "Source/*.cpp"
	"pugixml/src/*.cpp"
	"poly2tri/poly2tri/**/*.cpp"
	"nanovg/src/*.cpp"
)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "-g -std=c++11 -w -pedantic")
endif()

include_directories("Include")
include_directories("Source")
include_directories("easyloggingpp/src")
include_directories("nanovg/src")
include_directories("poly2tri/poly2tri")
include_directories("pugixml/src")

add_definitions(-DBALUENGINEDLL_EXPORTS -DBALUENGINE_DESIGN_TIME -DNANOVG_GLEW)

if (NOT TARGET BaluLib)
add_subdirectory(BaluLib)
include_directories(${BaluLib_SOURCE_DIR}/Include)
endif()

if (NOT TARGET BaluRender)
add_subdirectory(BaluRender)
include_directories(${BaluRender_SOURCE_DIR}/Include)
endif()
if (NOT TARGET BaluScript)
add_subdirectory(BaluScript)
include_directories(${BaluScript_SOURCE_DIR}/Include)
endif()

add_subdirectory("Box2D/Box2D/Box2D")

include_directories("Box2D/Box2D")
include_directories("Box2D/Box2D/Box2D")

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(DevIL REQUIRED)
include_directories(${IL_INCLUDE_DIR})

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})

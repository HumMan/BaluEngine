cmake_minimum_required(VERSION 2.8)

project(BindingMacroGenerator)

file(GLOB_RECURSE ${PROJECT_NAME}_SRC
    "GenerateBindingTemplates.cpp"
)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "-g -std=c++11 -w -pedantic")
endif()

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})

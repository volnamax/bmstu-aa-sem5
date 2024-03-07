cmake_minimum_required(VERSION 3.26)
project(cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp main.cpp
        in_out_file/Document.cpp
        in_out_file/Document.h
        in_out_file/Term.cpp
        in_out_file/Term.h
        in_out_file/io.cpp
        in_out_file/io.h
        klasters/Claster.cpp
        klasters/Claster.h
        klasters/Kmeans.cpp
        klasters/Kmeans.h
        thread/ThreadSafeQueue.cpp
        thread/ThreadSafeQueue.h
        klasters/Klastering.cpp
        klasters/Klastering.h
        thread/Atomic.cpp
        thread/Atomic.h)

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.9.1
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(cpp PRIVATE nlohmann_json::nlohmann_json)

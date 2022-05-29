cmake_minimum_required(VERSION 3.22)
project(apriori)

set(CMAKE_CXX_STANDARD 17)

# Tell cmake where to look for cmake modules..
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/cmake")


include_directories(include)
add_subdirectory(src)

list(APPEND LIBRARIES project_lib)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(apriori main.cpp)
target_link_libraries(apriori ${LIBRARIES})
target_include_directories(apriori PRIVATE
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/include/"
        )
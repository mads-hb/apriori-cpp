# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB SRC_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(project_lib ${SRC_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(project_lib PUBLIC ../include)

# Link libraries to project_lib
target_link_libraries(project_lib PRIVATE ${LIBRARIES})

# All users of this library will need at least C++11
target_compile_features(project_lib PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})

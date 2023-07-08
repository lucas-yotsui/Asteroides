cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(my_project LANGUAGES CXX)

# Using C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use SFML static libraries
set(BUILD_SHARED_LIBS FALSE)

# Include FetchContent module
include(FetchContent)

# Fetch SFML dependency statement declaration
FetchContent_Declare(
    SFML
    SYSTEM
    GIT_REPOSITORY 
        https://github.com/SFML/SFML.git
    GIT_TAG 
        2.6.x
)

# Message to inform user that script is not bugged, just busy resolving dependecy
message(STATUS "Baixando SFML e incluindo-o no projeto")

# Efectively fetch SFML dependency
FetchContent_MakeAvailable(SFML)

# Include all of the program's header and source files
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/*.h)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/source/*.cpp)

# Configure the project to look for include files in the 'include' directory
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# Create program executable and link against all of the program's headers and source files
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link SFML libraries against program executable
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-system)

# Set compiler warnings and make them be treated as errors
set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_OPTIONS "-Wall;-Wextra;-pedantic;-Werror"
)

# Copy all assets to build directory to make them available to the program
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(${PROJECT_NAME} copy_assets)
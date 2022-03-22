cmake_minimum_required(VERSION 3.0.0)
project(wordleSolver VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)


include(CTest)
enable_testing()

# include(FetchContent)

# FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
# FetchContent_MakeAvailable(json)



add_subdirectory(solver)
add_subdirectory(dataLoader)

add_executable(wordleSolver main.cpp)

target_link_libraries(wordleSolver PUBLIC solver)

target_include_directories(wordleSolver PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/solver"
                          )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

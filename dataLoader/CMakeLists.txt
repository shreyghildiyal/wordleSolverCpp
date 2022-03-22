set(dataLoaderFiles
    loader.h
    loader.cpp
)

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

add_library(dataLoader ${dataLoaderFiles})

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

target_include_directories(solver PUBLIC 
                        "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/jsoncpp"
                          "${PROJECT_SOURCE_DIR}/dataLoader"
                          )

target_link_libraries(dataLoader PUBLIC nlohmann_json::nlohmann_json)
set(solverFiles
    solver.h
    solver.cpp
)

add_library(solver ${solverFiles})

target_include_directories(solver PUBLIC 
                        "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/solver"
                          "${PROJECT_SOURCE_DIR}/dataLoader"
                          )

target_link_libraries(solver PUBLIC dataLoader)

# target_include_directories(wordleSolver PUBLIC
#                           "${PROJECT_BINARY_DIR}"
#                           "${PROJECT_SOURCE_DIR}/solver"
#                           )
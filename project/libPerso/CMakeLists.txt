include_directories(include)
file(GLOB_RECURSE SRC_FILES *.cpp *.hpp)
add_library(libPerso ${SRC_FILES})
target_link_libraries(libPerso assimp)

set(HEADER_LIST inc/Tile.hpp)
set(SRC_LIST src/Tile.cpp)
set(DEPENDENCIES_LIST sfml-graphics)

add_library(tile STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(tile PUBLIC . inc src)

target_link_libraries(tile PUBLIC ${DEPENDENCIES_LIST} figure)
add_dependencies(tile ${DEPENDENCIES_LIST})
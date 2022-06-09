set(HEADER_LIST inc/Tile.hpp)
set(SRC_LIST src/Tile.cpp)


add_library(tile ${SRC_LIST} ${HEADER_LIST})

target_include_directories(tile PUBLIC . inc src)

target_link_libraries(tile PUBLIC sfml-graphics)
add_dependencies(tile sfml-graphics)
set(HEADER_LIST inc/Board.hpp)
set(SRC_LIST src/Board.cpp)


add_library(board ${SRC_LIST} ${HEADER_LIST})

target_include_directories(board PUBLIC . inc src)

target_link_libraries(board PUBLIC sfml-graphics)
target_link_libraries(board PUBLIC tile)

add_dependencies(board sfml-graphics)
add_dependencies(board tile)
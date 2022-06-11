set(HEADER_LIST inc/Board.hpp)
set(SRC_LIST src/Board.cpp)
set(DEPENDENCIES_LIST sfml-graphics tile pawn)

add_library(board STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(board PUBLIC . inc src)

target_link_libraries(board PUBLIC ${DEPENDENCIES_LIST} move)
add_dependencies(board ${DEPENDENCIES_LIST})
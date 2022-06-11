set(HEADER_LIST inc/move.hpp)
set(SRC_LIST src/move.cpp)
set(DEPENDENCIES_LIST sfml-graphics)

add_library(move STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(move PUBLIC . inc src)

target_link_libraries(move PUBLIC ${DEPENDENCIES_LIST} figure)
add_dependencies(move ${DEPENDENCIES_LIST})
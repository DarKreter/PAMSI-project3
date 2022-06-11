set(HEADER_LIST inc/piece.hpp)
set(SRC_LIST src/piece.cpp)
set(DEPENDENCIES_LIST sfml-graphics figure)

add_library(piece STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(piece PUBLIC . inc src)

target_link_libraries(piece PUBLIC ${DEPENDENCIES_LIST})
# add_dependencies(piece ${DEPENDENCIES_LIST})

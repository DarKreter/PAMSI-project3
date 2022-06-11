set(HEADER_LIST inc/Pawn.hpp)
set(SRC_LIST src/Pawn.cpp)
set(DEPENDENCIES_LIST sfml-graphics figure)

add_library(pawn STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(pawn PUBLIC . inc src)

target_link_libraries(pawn PUBLIC ${DEPENDENCIES_LIST})
# add_dependencies(pawn ${DEPENDENCIES_LIST})

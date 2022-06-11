set(HEADER_LIST inc/Figure.hpp)
set(SRC_LIST src/Figure.cpp)
set(DEPENDENCIES_LIST sfml-graphics move board)

add_library(figure STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(figure PUBLIC . inc src)

target_link_libraries(figure PUBLIC ${DEPENDENCIES_LIST})
# add_dependencies(figure ${DEPENDENCIES_LIST})
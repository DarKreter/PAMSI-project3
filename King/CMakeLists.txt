set(HEADER_LIST inc/King.hpp)
set(SRC_LIST src/King.cpp)
set(DEPENDENCIES_LIST sfml-graphics figure)

add_library(king STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(king PUBLIC . inc src)

target_link_libraries(king PUBLIC ${DEPENDENCIES_LIST})
# add_dependencies(king ${DEPENDENCIES_LIST})

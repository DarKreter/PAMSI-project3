set(HEADER_LIST inc/Algorithms.hpp)
set(SRC_LIST src/Algorithms.cpp)
set(DEPENDENCIES_LIST move tile figure piece king board)

add_library(algorithms STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(algorithms PUBLIC . inc src)

target_link_libraries(algorithms PUBLIC ${DEPENDENCIES_LIST})
# add_dependencies(figure ${DEPENDENCIES_LIST})
add_executable(firmware src/main.cpp src/game.cpp)
target_include_directories(firmware PUBLIC . inc src)

set(DEPENDENCIES_LIST sfml-graphics tile move figure pawn board)

target_link_libraries(firmware PUBLIC ${DEPENDENCIES_LIST})
# add_dependencies(firmware ${DEPENDENCIES_LIST})
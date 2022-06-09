add_executable(firmware main.cpp)
target_include_directories(firmware PUBLIC .)

target_link_libraries(firmware PUBLIC sfml-graphics)
target_link_libraries(firmware PUBLIC tile)
target_link_libraries(firmware PUBLIC board)

add_dependencies(firmware sfml-graphics)
add_dependencies(firmware tile)
add_dependencies(firmware board)
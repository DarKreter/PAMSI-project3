add_executable(firmware main.cpp)
target_include_directories(firmware PUBLIC .)


target_link_libraries(firmware PUBLIC sfml-graphics)
add_dependencies(firmware sfml-graphics)
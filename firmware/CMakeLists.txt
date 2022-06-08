add_executable(firmware main.cpp)
target_include_directories(firmware PUBLIC .)


target_link_libraries(firmware PUBLIC SFML::Graphics)
add_dependencies(firmware SFML::Graphics)
# add_dependencies(firmware sfml‑window)
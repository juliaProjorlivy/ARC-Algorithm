project(${CMAKE_PROJECT_NAME})

add_executable(arc_main main.cpp)

target_link_libraries(arc_main PRIVATE arc)


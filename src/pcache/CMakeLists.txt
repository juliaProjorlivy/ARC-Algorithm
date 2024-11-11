project(${CMAKE_PROJECT_NAME})

add_executable(pmain pmain.cpp)

target_link_libraries(pmain PRIVATE pcache)


cmake_minimum_required (VERSION 3.0.0)
project (cexchange)

include_directories("include" "/usr/local/include")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


file (GLOB WS_SOURCES "src/c++/ws/*.cpp")
add_library(ws SHARED ${WS_SOURCES})

set(APP_LINK_LIBS ws boost_filesystem boost_date_time boost_system boost_regex boost_program_options rt pthread crypto ssl openblas)
set(APP_INCLUDE_PATHS include /usr/local/include src/c++/)

add_executable(simple_example "src/c++/examples/simple_example.cpp")
target_include_directories(simple_example SYSTEM PUBLIC ${APP_INCLUDE_PATHS})
target_link_libraries(simple_example ${APP_LINK_LIBS})

add_executable(general_listener "src/c++/examples/general_listener.cpp" "src/c++/examples/config.cpp")
target_include_directories(general_listener SYSTEM PUBLIC ${APP_INCLUDE_PATHS})
target_link_libraries(general_listener ${APP_LINK_LIBS})



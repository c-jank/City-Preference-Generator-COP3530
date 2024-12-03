cmake_minimum_required(VERSION 3.28)
project(City-Preference-Generator-COP3530)

set(CMAKE_CXX_STANDARD 17)

include_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/bridges/include)
link_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/bridges/lib)

include_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/curl/include)
link_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/curl/lib)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)


add_executable(City-Preference-Generator-COP3530 main.cpp)
target_link_libraries(City-Preference-Generator-COP3530 libcurl.lib)
target_link_libraries(City-Preference-Generator-COP3530 sfml-system sfml-window sfml-graphics sfml-audio)


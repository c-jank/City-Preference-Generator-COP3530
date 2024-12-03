cmake_minimum_required(VERSION 3.28)
project(City-Preference-Generator-COP3530)

set(CMAKE_CXX_STANDARD 14)

include_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/bridges/include)
link_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/bridges/lib)

include_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/curl/include)
link_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/curl/lib)

add_executable(City-Preference-Generator-COP3530 main.cpp)
target_link_libraries(City-Preference-Generator-COP3530 libcurl.lib)
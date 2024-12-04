cmake_minimum_required(VERSION 3.28)
project(City-Preference-Generator-COP3530)

set(CMAKE_CXX_STANDARD 14)

include_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/bridges/include)
link_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/bridges/lib)

include_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/curl/include)
link_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/curl/lib)

add_executable(City-Preference-Generator-COP3530 main.cpp
        maxHeap.h
        maxHeap.cpp
        UI.cpp
        SplayTree.h)
target_link_libraries(City-Preference-Generator-COP3530 libcurl.lib sfml-system sfml-window sfml-graphics sfml-audio)


include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)


target_compile_features(City-Preference-Generator-COP3530 PRIVATE cxx_std_14)
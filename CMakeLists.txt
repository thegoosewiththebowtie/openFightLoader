
cmake_minimum_required(VERSION 3.28)
project(openFightLoader LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(openFightMaker src/main.cpp
               src/uidrawer.cpp
               src/uidrawer.h
               src/common.cpp
               src/common.h
               src/patternparser.cpp
               src/patternparser.h
               src/you.cpp
               src/you.h
               src/uiparser.cpp
               src/uiparser.h)
target_compile_features(openFightMaker PRIVATE cxx_std_17)
target_link_libraries(openFightMaker PRIVATE SFML::Graphics)

cmake_minimum_required(VERSION 3.10)
project(MenagerieGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Add executable
add_executable(menagerie main.cpp)

# Link SFML libraries
target_link_libraries(menagerie sfml-graphics sfml-window sfml-system sfml-audio)

# Copy assets to build directory
file(COPY sprites/ DESTINATION ${CMAKE_BINARY_DIR}/sprites/)
file(COPY arial.ttf DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY openal32.dll DESTINATION ${CMAKE_BINARY_DIR}/)

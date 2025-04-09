cmake_minimum_required(VERSION 3.30)
project(proiect1)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define executable
add_executable(proiect1
        main.cpp
        Movie.cpp
        Movie.h
        MovieDate.cpp
        MovieDate.h
        Room.cpp
        Room.h
        Exceptions.h
        StaffFunctions.h
        TemplateClasses.h
)

# Ensure `passwords.txt` is copied to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/passwords.txt DESTINATION ${CMAKE_BINARY_DIR})

# Include directories (if you have headers in a separate folder)
target_include_directories(proiect1 PRIVATE ${CMAKE_SOURCE_DIR})

# Add compiler warnings (optional but recommended)
target_compile_options(proiect1 PRIVATE -Wall -Wextra -pedantic)

# Link libraries if needed (for example, linking threading or filesystem)
find_package(Threads REQUIRED)
target_link_libraries(proiect1 PRIVATE Threads::Threads)
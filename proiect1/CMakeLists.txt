cmake_minimum_required(VERSION 3.30)
project(proiect1)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source and header directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Disabling warings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

# Define executable
add_executable(proiect1
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/Movie.cpp
        ${INCLUDE_DIR}/Movie.h
        ${SRC_DIR}/MovieDate.cpp
        ${INCLUDE_DIR}/MovieDate.h
        ${SRC_DIR}/Room.cpp
        ${INCLUDE_DIR}/Room.h
        ${INCLUDE_DIR}/Exceptions.h
        ${INCLUDE_DIR}/StaffFunctions.h
        ${INCLUDE_DIR}/TemplateClasses.h
        ${SRC_DIR}/Ticket.cpp
        ${INCLUDE_DIR}/Ticket.h
        ${INCLUDE_DIR}/MovieDateFactory.h
)

# Ensure `passwords.txt` is copied to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets/passwords.txt DESTINATION ${CMAKE_BINARY_DIR})

# Include directories (if you have headers in a separate folder)
target_include_directories(proiect1 PRIVATE ${CMAKE_SOURCE_DIR})

# Add compiler warnings (optional but recommended)
target_compile_options(proiect1 PRIVATE -Wall -Wextra -pedantic)

# Link libraries if needed (for example, linking threading or filesystem)
find_package(Threads REQUIRED)
target_link_libraries(proiect1 PRIVATE Threads::Threads)
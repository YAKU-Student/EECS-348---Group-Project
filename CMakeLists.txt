cmake_minimum_required(VERSION 3.28)
project(boolean_simulator VERSION 0.1.0)

# Add warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(boolean_simulator)

target_sources(boolean_simulator PRIVATE
    "src/main.cpp"
    "src/ast.cpp"
)

#Includes the header files from src
target_include_directories(boolean_simulator PUBLIC "src")

target_compile_definitions(boolean_simulator PUBLIC PROGRAM_VERSION="${PROJECT_VERSION}")

#Use this command to build: cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B build && make -C build
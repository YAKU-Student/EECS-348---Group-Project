cmake_minimum_required(VERSION 3.21)
project(boolean_simulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(boolean_simulator)

target_sources(boolean_simulator PRIVATE
    "src/main.cpp"
    "src/ast/ast.cpp"
    "src/error/error.cpp"
    "src/parser/parser.cpp"
    "src/test/test.cpp"
    "src/types/types.cpp"
)

#Includes the header files from src
target_include_directories(boolean_simulator PRIVATE 
    "src"
    "src/ast"
    "src/error"
    "src/parser"
    "src/test"
    "src/types"
)

target_compile_options(boolean_simulator PRIVATE
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O1> # Apply -O1 if the compiler is not MSVC
    $<$<CXX_COMPILER_ID:MSVC>:/O1>        # Apply /O1 if the compiler is MSVC
)
#Use this command to build: cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build && make -C build

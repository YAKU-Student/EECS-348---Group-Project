# Final Project - EECS348  

This is the repository for our final project for EECS-348 (Software Engineering I) at KU

## Project Objective  

> This project delves into the world of digital logic. You will develop a C++ program acting as a    
> simplified Boolean logic simulator. The aim of this project is to develop a program that    
> simulates the behavior of logic circuits, including operations such as AND, OR, NOT, NAND, and    
> XOR. The program should be able to handle complex logic circuits with multiple gates and   
> input/output signals. The project will provide students with comprehensive hands-on experience   
> in software engineering, emphasizing the development process from project planning to fully   
> realized product. While aiming for the functionality of a full-fledged circuit simulator, we'll focus   
> on evaluating Boolean expressions for an introductory learning experience.   
> 
> This project provides an opportunity to explore the fascinating concepts of logic gates, truth   
> tables, and expression evaluation. You'll gain valuable skills in parsing, data structures,   
> algorithm design, and software engineering principles.   

## Quick Links   

- [Installation](#installation)
- [Quickstart Guide](#start-guide)
  * [Flags](#flags)
- [Build from Source](#building-from-source)
  * [Dependencies](#required-dependencies)
  * [Linux](#linux)
  * [macOS](#macos)
  * [Windows](#windows)
- [Members](#members)

## Installation   

This program requires [building from source](#building-from-source). You can download the latest version from the [release page](https://github.com/YAKU-Student/EECS-348---Group-Project/releases).    

## Start Guide   

Below are examples of general program usage. For a more in-depth look, please look at the [User Manual](https://github.com/YAKU-Student/EECS-348---Group-Project/blob/main/doc/06-Users-Manual.pdf).    

```console
user@archlinux:~$ boolean_simulator 'T & F'
Result: False!

user@archlinux:~$ boolean_simulator -c 'T & F'
Expected 1 argument, received 2. Please pass in -c/--continuous, -v/--version, or an expression.
Make sure to wrap the expression in quotes.

user@archlinux:~$ boolean_simulator -c
Please enter your boolean expression, or enter history to see all prior evaluated expressions (enter exit, quit, or q to exit the program): T & F
Result: False!

Please enter your boolean expression, or enter history to see all prior evaluated expressions (enter exit, quit, or q to exit the program): T @ F
Result: True!

Please enter your boolean expression, or enter history to see all prior evaluated expressions (enter exit, quit, or q to exit the program): (T | F) $ (F & T)
Result: True!

Please enter your boolean expression, or enter history to see all prior evaluated expressions (enter exit, quit, or q to exit the program): history
Expression: T & F
Result: False!
Expression: T @ F
Result: True!
Expression: (T | F) $ (F & T)
Result: True!

Please enter your boolean expression, or enter history to see all prior evaluated expressions (enter exit, quit, or q to exit the program): quit
Exiting...
```

### Flags

- Without any flags, the program will expect a boolean expression as the input. For example: `boolean_simulator 'T & F'`
- With the `-c` or `--continuous` flag, the program will run in continuous mode. The user will be prompted for boolean expressions to evaluate until exiting the program by typing `exit`, `quit`, or `q`. Passing in any other arguments along with `-c` will result in an error and the program will not run.
- With the `-v` or `--version` flag. The program simply displays the version information of the program.    
- The flag `-t` or `--test` is mainly intended for developer use. Launching the program in this mode will take a list of expressions from `expressions.txt` and place the results in `results.txt`. The project must be ran from the root of the project directory: `build/boolean_simulator -t`, and `expressions.txt` must be present in the root.

## Building from source

### Required dependencies

- A valid c++ compiler, we recommend [clang++](https://clang.llvm.org/), but you can use [g++](https://gcc.gnu.org/)   
  - [LLVM](https://www.llvm.org/)
    * [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
    * [clang++](https://clang.llvm.org/)
- [CMake](https://cmake.org/)

### Linux

Dependencies    

```bash
sudo apt-get install cmake
sudo apt install clang
```

Build    

```bash
cmake -B build && make -C build
```

Run    

```bash
build/boolean_simulator
```

### macOS

Dependencies

```bash
brew install cmake
brew install clang
```

Build

```bash
cmake -B build && make -C build
```

Run

```bash
build/boolean_simulator
```

### Windows

Use [wsl](https://learn.microsoft.com/en-us/windows/wsl/install) and install via [Linux](#linux)    

Or, you can use your own choice of installation for llvm/gcc and cmake.    

```powershell
cmake -B build && make -C build
```

## Members     

| Member           | Role                         | Email                   |
| ---------------- | ---------------------------- | ----------------------- |
| Alexander Phibbs | Project Lead, Developer      | alex.r.phibbs@gmail.com |
| Caden LeCluyse   | Product Owner, Developer     | lecluyse20@gmail.com    |
| Ceres Botkin     | Second Team Lead, Developer  | N/A                     | 
| Theodora Okhagbuzo | Meeting Secretary, Developer | theo.ekp@gmail.com    |
| Justin Daugherty | Debugger, Developer          | justin.darty03@gmail.com |
| Cole Charpentier | Division of Tasks, Developer | c287c458@ku.edu         |

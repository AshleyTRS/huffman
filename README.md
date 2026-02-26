# Huffman Coding Algorithm Implementation

## Overview

This project is a graphical application that implements the Huffman coding algorithm and provides a visual representation of the generated Huffman tree. The application allows the user to enter a text input, compute the frequency table, generate binary codes for each symbol, display the encoded output, and render the full Huffman tree dynamically.

The goal of the project is both educational and practical. It demonstrates how lossless compression works internally while also providing an interactive visualization of the tree construction. The graphical interface makes it easier to understand how symbol frequencies influence tree structure and binary code length.

The application is built using C++ and wxWidgets, with CMake used as the build system. It separates the core Huffman logic from the graphical interface, following a modular architecture.

## Tools and Versions

This project is written in C++20 and requires a modern C++ compiler with full C++20 support. The recommended compiler is Microsoft Visual C++ (MSVC) provided with Visual Studio 2022.

The application depends on wxWidgets 3.x. It was built and tested using the 64-bit dynamic MSVC configuration (vc_x64_dll) compiled in Release mode. wxWidgets must be built manually from source before compiling this project.

The build system used is CMake version 3.20 or newer. CMake must be installed and accessible from the command line. You can verify this by running:

```bash
cmake --version
```

The recommended development setup on Windows includes Visual Studio 2022 with the “Desktop development with C++” workload installed. During installation, ensure that MSVC v143 build tools and the Windows 10 or Windows 11 SDK are selected. The project uses the 64-bit toolchain and must be built from the “x64 Native Tools Command Prompt for VS” when compiling wxWidgets manually.

The application was developed and tested on Windows 11 using the MSVC x64 toolchain. While it may work on Windows 10, it has not been tested with MinGW or other compilers.

Before proceeding with the development environment configuration, ensure that the following software is installed and properly configured on your system:

- Visual Studio 2022 with C++ workload
- CMake 3.20 or newer
- wxWidgets 3.x source code
- Windows 10 or 11 SDK
- x64 MSVC build tools

These components are required to successfully build and run the application as described in the next section.

## Development Environment Configuration (Windows + MSVC)

This project was developed and tested on Windows using Microsoft Visual Studio 2022 (MSVC x64), CMake, and wxWidgets built manually from source.

First, download the wxWidgets source code as a Windows ZIP archive from:

<https://wxwidgets.org/downloads/>

Extract the archive to:

```bash
C:\cpp-lib-wxwidgets
```

Then create an environment variable pointing to this directory. Open PowerShell or Command Prompt and run:

```bash
setx WXWIN "C:\cpp-lib-wxwidgets"
```

Close and reopen the terminal after setting the variable.

To build wxWidgets, open the Visual Studio Developer Command Prompt:

```bash
x64 Native Tools Command Prompt for VS
```

Then navigate to the wxWidgets MSVC build directory:

```bash
cd C:\cpp-lib-wxwidgets\build\msw
```

Build wxWidgets in 64-bit Release mode with shared libraries:

```bash
Build wxWidgets in 64-bit Release mode with shared libraries:
```

After compilation, the generated libraries will appear in:

```bash
C:\cpp-lib-wxwidgets\lib\vc_x64_dll
```

Since this is a shared (DLL) build, the runtime DLL files must be accessible. You can either add them to your system PATH:

```bash
setx PATH "%PATH%;C:\cpp-lib-wxwidgets\lib\vc_x64_dll"
```

Or copy the DLL files into your project’s executable directory after building:

```bash
copy C:\cpp-lib-wxwidgets\lib\vc_x64_dll\*.dll build\Release\
```

Next, configure your CMakeLists.txt at the root of your project as follows:

```code
cmake_minimum_required(VERSION 3.15)
project(Huffman)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(wxWidgets_ROOT_DIR $ENV{WXWIN})
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Huffman WIN32 ${SOURCES})

target_include_directories(Huffman PRIVATE src)
target_link_libraries(Huffman ${wxWidgets_LIBRARIES})
```

For Visual Studio Code IntelliSense support, configure .vscode/c_cpp_properties.json like this:

```json
{
    "configurations": [
        {
            "name": "Win32",
            "compilerPath": "cl.exe",
            "intelliSenseMode": "windows-msvc-x64",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/cpp-lib-wxwidgets/include",
                "C:/cpp-lib-wxwidgets/lib/vc_x64_dll/mswu"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "cppStandard": "c++20"
        }
    ],
    "version": 4
}
```

Finally, from the root of your project, configure and build using CMake:

```bash
cmake -S . -B build
cmake --build build --config Release
```

The executable will be generated at:

```bash
build\Release\Huffman.exe
```

Run the application using:

```bash
build\Release\Huffman.exe
```

If the application fails to launch due to missing DLLs, verify that the wxWidgets dynamic libraries are either included in the system PATH or copied into the Release directory.

If you need to rebuild use the following for a clean rebuild:

```bash
rm -r -fo build
cmake -S . -B build
cmake --build build --config Release
```

## Compilation and Execution

After completing the development environment configuration and successfully building wxWidgets in Release mode (vc_x64_dll), the project can be compiled using CMake and MSVC.

Open a terminal in the root directory of the project. It is recommended to use a normal PowerShell or Command Prompt for configuring and building the application, since wxWidgets has already been compiled using the x64 Native Tools Command Prompt.

Generate the build files using CMake with an out-of-source build:

```bash
cmake -S . -B build
```

This command configures the project and generates the necessary Visual Studio build files inside the build directory.

Next, compile the project in Release mode:

```bash
cmake --build build --config Release
```

If the build completes successfully, the executable will be generated at:

```bash
build\Release\Huffman.exe
```

Run the application using:

```bash
build\Release\Huffman.exe
```

If the linker reports that it cannot open the executable file, ensure the application is not already running and that no previous instance is locking the file.

If the application fails to launch due to missing DLL files, verify that the wxWidgets dynamic libraries from:

```bash
C:\cpp-lib-wxwidgets\lib\vc_x64_dll
```

are either included in the system PATH environment variable or copied directly into the build\Release directory.

This project uses a shared wxWidgets build (SHARED=1), so the DLL files are required at runtime.

## Project Structure

The project follows a modular architecture that separates the compression logic from the graphical interface. The directory layout is organized as follows:

```code
Huffman/
│
├── CMakeLists.txt
├── build/
│
├── src/
│   ├── main.cpp
│   │
│   ├── core/
│   │   ├── Huffman.hpp
│   │   ├── Huffman.cpp
│   │
│   ├── gui/
│   │   ├── MainFrame.hpp
│   │   ├── MainFrame.cpp
│   │   ├── TreePanel.hpp
│   │   ├── TreePanel.cpp
│
└── .vscode/
    └── c_cpp_properties.json
```

The root directory contains the CMakeLists.txt file, which defines the build configuration, compiler settings, source discovery, and wxWidgets integration.

The src directory contains the application source code and is divided into logical components. The core folder implements the Huffman algorithm, including the data structures, tree construction, frequency analysis, and encoding logic. This part of the project is independent from the graphical interface and can be reused in other contexts.

The gui folder contains all user interface components built using wxWidgets. MainFrame manages the application window and layout, while TreePanel is a custom rendering panel responsible for dynamically drawing the Huffman tree.

The main.cpp file serves as the entry point of the application and initializes the wxWidgets application object.

The build directory is generated automatically by CMake during compilation. It contains intermediate build files and the final executable. This directory is not part of the source code and should not be committed to version control.

The .vscode folder contains configuration files for Visual Studio Code, including IntelliSense settings for wxWidgets and MSVC.

This separation ensures that the compression algorithm remains independent of the graphical interface, making the project easier to maintain, test, debug, and extend in the future.

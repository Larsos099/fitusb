cmake_minimum_required(VERSION 3.16)
project(fitusb) # Flash (ISO-)Image to USB
set(CMAKE_MAKE_PROGRAM "mingw32-make")
set(CMAKE_CXX_STANDARD 17) # C++ 17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "--static")
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp) # Source Files
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS include/*.hpp) # Header Files

add_executable(fitusb ${SOURCE_FILES} ${HEADER_FILES})
target_compile_options(fitusb PRIVATE -fexceptions)

if(MSVC)
    target_compile_options(fitusb PRIVATE /EHsc)
endif()

target_include_directories(fitusb PRIVATE include)

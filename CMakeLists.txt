cmake_minimum_required(VERSION 3.10)

project(CommandProcessor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
  src/cpp/main_software.cpp
  src/cpp/command_manager.cpp
  src/cpp/cpmenu_format.cpp
  src/cpp/menu_manager.cpp
  src/cpp/order_manager.cpp
)

set(HEADERS
  src/hpp/main_software.hpp
  src/hpp/command_manager.hpp
  src/hpp/cpmenu_format.hpp
  src/hpp/menu_manager.hpp
  src/hpp/order_manager.hpp
)

add_executable(main.out ${SOURCES} ${HEADERS})

target_include_directories(main.out PRIVATE src/hpp)
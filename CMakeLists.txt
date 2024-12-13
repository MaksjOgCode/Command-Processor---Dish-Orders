cmake_minimum_required(VERSION 3.10)

project(CommandProcessor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
  src/cpp/main.cpp
  src/cpp/command_manager.cpp
  src/cpp/cpmenu_format.cpp
  src/cpp/menu_manager.cpp
  src/cpp/order_manager.cpp
)

add_executable( main.out ${SOURCES} )

target_include_directories(main.out PRIVATE src/hpp)
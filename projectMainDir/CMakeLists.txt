cmake_minimum_required(VERSION 3.16)
project(projektGra)

set(CMAKE_CXX_STANDARD 17)

# Zastepuje -I w pierwotnej wersji budowy w terminalu
include_directories(include)
include_directories(libs/TGUI-1.11/install/include)

# Zastepuje -L przy linkowaniu w komendzie
link_directories(libs/TGUI-1.11/build/lib)

add_executable(projektGra src/main.cpp src/SnakeDetails.cpp)


target_link_libraries(projektGra sfml-graphics sfml-window sfml-system tgui)

set_target_properties(projektGra PROPERTIES
    BUILD_RPATH "${CMAKE_SOURCE_DIR}/libs/TGUI-1.11/build/lib"
)
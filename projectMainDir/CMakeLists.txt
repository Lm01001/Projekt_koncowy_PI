cmake_minimum_required(VERSION 3.16)
project(projektGra)

set(CMAKE_CXX_STANDARD 17)

# Zastepuje -I w pierwotnej wersji budowy w terminalu
include_directories(include)
include_directories(resources)

# Spersonalizowana konfiguracja pod konkretna platforme/os
if(WIN32)
    include_directories(libs/SFML-win-vc17-64bit/SFML-3.0.2/include)
    include_directories(libs/TGUI-1.11/install/include)

    # Zastepuje -L przy linkowaniu w komendzie
    link_directories(libs/TGUI-1.11/build/lib)
    link_directories(libs/SFML-win-vc17-64bit/SFML-3.0.2/lib)

    set(SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio)
    set(TGUI_LIBS tgui)

elseif(APPLE)
    
    find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)
    find_package(TGUI 1 REQUIRED)

    set(SFML_LIBS SFML::Graphics SFML::Window SFML::System SFML::Audio)
    set(TGUI_LIBS tgui)

elseif(UNIX)

    set(CMAKE_PREFIX_PATH /usr/local ${CMAKE_PREFIX_PATH})

    find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)
    find_package(TGUI REQUIRED)

    set(SFML_LIBS SFML::Graphics SFML::Window SFML::System SFML::Audio)
    set(TGUI_LIBS tgui)

endif()

add_executable(projektGra src/main.cpp src/SnakeDetails.cpp src/ButtonCreator.cpp)

target_link_libraries(projektGra ${SFML_LIBS} ${TGUI_LIBS})

if(WIN32)

    set_target_properties(projektGra PROPERTIES
        BUILD_RPATH "${CMAKE_SOURCE_DIR}/libs/TGUI-1.11/build/lib"
    )

elseif(APPLE)

    set_target_properties(projektGra PROPERTIES
        BUILD_RPATH "@executable_path;@loader_path"
        INSTALL_RPATH "@executable_path;@loader_path"
    )

elseif(UNIX)

    set_target_properties(projektGra PROPERTIES
        BUILD_RPATH "$ORIGIN"
        INSTALL_RPATH "$ORIGIN"
    )

endif()

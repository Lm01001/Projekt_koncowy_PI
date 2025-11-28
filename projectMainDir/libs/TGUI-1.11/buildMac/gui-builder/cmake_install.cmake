# Install script for directory: /Users/zofiamikoda/Documents/Projekt_koncowy_PI/projectMainDir/libs/TGUI-1.11/gui-builder

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gui-builder" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder" TYPE EXECUTABLE FILES "/Users/zofiamikoda/Documents/Projekt_koncowy_PI/projectMainDir/libs/TGUI-1.11/buildMac/gui-builder/gui-builder")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder/gui-builder" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder/gui-builder")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/zofiamikoda/Documents/Projekt_koncowy_PI/projectMainDir/libs/TGUI-1.11/buildMac/lib"
      -delete_rpath "/opt/homebrew/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder/gui-builder")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder/gui-builder")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gui-builder" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder" TYPE DIRECTORY FILES "/Users/zofiamikoda/Documents/Projekt_koncowy_PI/projectMainDir/libs/TGUI-1.11/gui-builder/resources")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gui-builder" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder" TYPE DIRECTORY FILES "/Users/zofiamikoda/Documents/Projekt_koncowy_PI/projectMainDir/libs/TGUI-1.11/themes")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/zofiamikoda/Documents/Projekt_koncowy_PI/projectMainDir/libs/TGUI-1.11/buildMac/gui-builder/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()

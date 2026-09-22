# Install script for directory: /home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/nikituch/Projects/nix-src/work/12.2.0/install")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/nix/store/z4c6k0mrlkwl3s4w9ysxc8vq1wylm3ms-gcc-wrapper-15.3.0/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "fmt_core" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE STATIC_LIBRARY FILES "/home/nikituch/Projects/nix-src/work/12.2.0/cmake-build/libfmt.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "fmt_core" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/fmt" TYPE FILE FILES
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/args.h"
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/base.h"
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/chrono.h"
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/color.h"
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/compile.h"
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/core.h"
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/format.h"
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/format-inl.h"
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/os.h"
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/ostream.h"
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/printf.h"
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/ranges.h"
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/std.h"
    "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/xchar.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "fmt_core" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE STATIC_LIBRARY FILES "/home/nikituch/Projects/nix-src/work/12.2.0/cmake-build/libfmt-c.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "fmt_core" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/fmt" TYPE FILE FILES "/home/nikituch/Projects/nix-src/work/12.2.0/fmt-12.2.0/include/fmt/fmt-c.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "fmt_core" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/fmt" TYPE FILE FILES
    "/home/nikituch/Projects/nix-src/work/12.2.0/cmake-build/fmt-config.cmake"
    "/home/nikituch/Projects/nix-src/work/12.2.0/cmake-build/fmt-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "fmt_core" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/fmt/fmt-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/fmt/fmt-targets.cmake"
         "/home/nikituch/Projects/nix-src/work/12.2.0/cmake-build/CMakeFiles/Export/52567436e6aeb216c623c7cea7a08046/fmt-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/fmt/fmt-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/fmt/fmt-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/fmt" TYPE FILE FILES "/home/nikituch/Projects/nix-src/work/12.2.0/cmake-build/CMakeFiles/Export/52567436e6aeb216c623c7cea7a08046/fmt-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/fmt" TYPE FILE FILES "/home/nikituch/Projects/nix-src/work/12.2.0/cmake-build/CMakeFiles/Export/52567436e6aeb216c623c7cea7a08046/fmt-targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "fmt_core" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/pkgconfig" TYPE FILE FILES "/home/nikituch/Projects/nix-src/work/12.2.0/cmake-build/fmt.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/nikituch/Projects/nix-src/work/12.2.0/cmake-build/test/cmake_install.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/nikituch/Projects/nix-src/work/12.2.0/cmake-build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/nikituch/Projects/nix-src/work/12.2.0/cmake-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()

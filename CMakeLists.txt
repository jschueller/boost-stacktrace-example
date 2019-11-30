

cmake_minimum_required (VERSION 3.1)

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the build type")

if(POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif()


project (boost-stacktrace-example)

include (GNUInstallDirs)

find_package (Boost REQUIRED)

add_executable (stacktrace main.cxx)

if (UNIX)
  target_compile_definitions(stacktrace PRIVATE BOOST_STACKTRACE_USE_ADDR2LINE)
  message(STATUS "Using Boost::stacktrace/addr2line")
  target_link_libraries(stacktrace PRIVATE dl)
elseif (MINGW)
  find_library(BOOST_STACKTRACE_BACKTRACE_LIBRARY NAMES boost_stacktrace_backtrace)
  if (NOT BOOST_STACKTRACE_BACKTRACE_LIBRARY)
    message(SEND_ERROR "libboost_stacktrace_backtrace is required")
  endif ()
  target_compile_definitions(stacktrace PRIVATE BOOST_STACKTRACE_USE_BACKTRACE)
  target_link_libraries(stacktrace PRIVATE boost_stacktrace_backtrace backtrace)
  message(STATUS "Using Boost::stacktrace/backtrace")
else ()
  message(SEND_ERROR "TODO")
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_definitions(stacktrace PRIVATE _GLIBCXX_ASSERTIONS)
  target_compile_options(stacktrace PRIVATE "-g;-fno-inline")
  target_link_options(stacktrace PRIVATE "-no-pie")
endif ()

install (TARGETS stacktrace DESTINATION ${CMAKE_INSTALL_BINDIR})

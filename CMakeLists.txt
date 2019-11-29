

cmake_minimum_required (VERSION 3.1)

set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the build type")

if(POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif()


project (boost-stacktrace-example)

include (GNUInstallDirs)

find_package(Boost REQUIRED)

add_executable (stacktrace main.cxx)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_definitions(stacktrace PRIVATE _GLIBCXX_ASSERTIONS)
  set(CMAKE_CXX_FLAGS "-no-pie ${CMAKE_CXX_FLAGS}")
endif ()

if (UNIX)
  target_compile_definitions(stacktrace PRIVATE BOOST_STACKTRACE_USE_ADDR2LINE)
  target_link_libraries(stacktrace dl)
elseif(WIN32)
  target_compile_definitions(stacktrace PRIVATE BOOST_STACKTRACE_USE_BACKTRACE)
  target_link_libraries(stacktrace PRIVATE boost_stacktrace_backtrace backtrace)
endif ()

install (TARGETS stacktrace DESTINATION ${CMAKE_INSTALL_BINDIR})

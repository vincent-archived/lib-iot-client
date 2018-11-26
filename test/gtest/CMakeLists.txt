cmake_minimum_required(VERSION 3.5.1)

project(. NONE)

include(ExternalProject)

ExternalProject_Add(googletest
        GIT_REPOSITORY    https://github.com/google/googletest.git
        GIT_TAG           release-1.8.1
        SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
        BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/googletest-build"
        )





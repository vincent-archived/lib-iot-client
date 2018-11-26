cmake_minimum_required(VERSION 3.5.1)

project(test NONE)

add_subdirectory(gtest)

if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/gtest/googletest-src/CMakeLists.txt")

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gtest/googletest-src )
    if(result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gtest/googletest-src )
    if(result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/gtest/googletest-src
            ${CMAKE_CURRENT_BINARY_DIR}/gtest/googletest-build
            EXCLUDE_FROM_ALL)
    include_directories(../serialport/src)

    add_executable(serialport_test serialport_uinttest.cpp)
    target_link_libraries(serialport_test gtest_main iot-client-serialport)
    add_test(NAME serialport_test COMMAND serialport_test)

else()
endif()




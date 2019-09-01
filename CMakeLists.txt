cmake_minimum_required(VERSION 3.14.3)

project(libtorrent_wrapper)

#----------------------
#   GoogleTest
#----------------------
# Download and unpack googletest at configure time
configure_file(googletest.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)


include_directories(${PROJECT_SOURCE_DIR}/wrapper/include/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(app ${PROJECT_SOURCE_DIR}/wrapper/src/main.cpp)
target_sources(app
  PUBLIC
)

enable_testing()
add_executable(app_test ${PROJECT_SOURCE_DIR}/wrapper/tests/main.cpp)
target_sources(app_test
  PUBLIC
)
target_link_libraries(app_test gtest_main)
target_link_libraries(app_test gmock_main)
add_test(NAME app_test COMMAND app_test)

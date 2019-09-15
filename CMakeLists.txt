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
add_subdirectory(
  ${CMAKE_CURRENT_BINARY_DIR}/googletest-src
  ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
  EXCLUDE_FROM_ALL
)

#----------------------
#   libtorrent
#----------------------
# Download and unpack libtorrent at configure time
configure_file(libtorrent.in libtorrent-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libtorrent-download )
if(result)
  message(FATAL_ERROR "CMake step for libtorrent failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libtorrent-download )
if(result)
  message(FATAL_ERROR "Build step for libtorrent failed: ${result}")
endif()

# Add libtorrent directly to our build. This defines
add_subdirectory(
  ${CMAKE_CURRENT_BINARY_DIR}/libtorrent-src
  ${CMAKE_CURRENT_BINARY_DIR}/libtorrent-build
  EXCLUDE_FROM_ALL
)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/libtorrent-src/include EXCLUDE_FROM_ALL)

#----------------------
#   App Config
#----------------------
include_directories(${PROJECT_SOURCE_DIR}/wrapper/include/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(torrent_start ${PROJECT_SOURCE_DIR}/wrapper/src/targets/torrent_start.cpp)
target_sources(torrent_start
  PUBLIC
  ${PROJECT_SOURCE_DIR}/wrapper/src/queue/QueueManager.cpp
  ${PROJECT_SOURCE_DIR}/wrapper/src/queue/stream/FileStream.cpp
)
target_link_libraries(torrent_start torrent-rasterbar)


add_executable(torrent_add ${PROJECT_SOURCE_DIR}/wrapper/src/targets/torrent_add.cpp)
target_sources(torrent_add
  PUBLIC
  ${PROJECT_SOURCE_DIR}/wrapper/src/queue/QueueManager.cpp
  ${PROJECT_SOURCE_DIR}/wrapper/src/queue/stream/FileStream.cpp
)

add_executable(torrent_rm ${PROJECT_SOURCE_DIR}/wrapper/src/targets/torrent_rm.cpp)
target_sources(torrent_rm
  PUBLIC
  ${PROJECT_SOURCE_DIR}/wrapper/src/queue/QueueManager.cpp
  ${PROJECT_SOURCE_DIR}/wrapper/src/queue/stream/FileStream.cpp
)

enable_testing()
add_executable(app_test ${PROJECT_SOURCE_DIR}/wrapper/tests/main.cpp)
target_include_directories(app_test
  PUBLIC
  ${PROJECT_SOURCE_DIR}/wrapper/tests/mocks/
  ${PROJECT_SOURCE_DIR}/wrapper/include/
)
target_sources(app_test
  PUBLIC
  ${PROJECT_SOURCE_DIR}/wrapper/src/queue/QueueManager.cpp
  ${PROJECT_SOURCE_DIR}/wrapper/tests/mocks/StringStreamTest.cpp
  ${PROJECT_SOURCE_DIR}/wrapper/tests/queue/QueueManagerTest.cpp
)
target_link_libraries(app_test gtest_main)
target_link_libraries(app_test gmock_main)
add_test(NAME app_test COMMAND app_test)

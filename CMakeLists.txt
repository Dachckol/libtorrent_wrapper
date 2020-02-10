cmake_minimum_required(VERSION 3.14.3)


SET (CMAKE_C_COMPILER             "/usr/bin/clang")
SET (CMAKE_C_FLAGS_INIT                "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
SET (CMAKE_CXX_FLAGS_INIT                "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")


project(libtorrent_wrapper)

#----------------------
#   libtorrent
#----------------------
add_subdirectory(libtorrent)

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
  ${PROJECT_SOURCE_DIR}/wrapper/src/torrent/Torrenter.cpp
)
target_compile_options(torrent_start PUBLIC -lboost_system)
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

cmake_minimum_required(VERSION 3.6)
project(platformer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(Titan/src/ Dependencies/TinyXML/)
file(GLOB_RECURSE SOURCE_FILES Titan/* Dependencies/TinyXML/*)
add_executable(platformer ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(platformer ${SFML_LIBRARIES})
endif()
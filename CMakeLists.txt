cmake_minimum_required(VERSION 3.6)
project(platformer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
set(EXECUTABLE_OUTPUT_PATH bin)

file(WRITE bin/settings/musicsettings.txt)
file(WRITE bin/settings/screensettings.txt)

file(GLOB MUSIC res/*)
file(COPY ${MUSIC} DESTINATION bin/res)
file(COPY res/levels/tileset_level_1.PNG DESTINATION bin)

# TODO: Find a better solution. For now IDK how to resolve this shit :(
# TODO: Duplicate _main symbol
file(REMOVE vendor/tinyxml2/xmltest.cpp vendor/tinyxml2/contrib/html5-printer.cpp)

include_directories(src/ vendor/tinyxml2)
file(GLOB_RECURSE SOURCE_FILES src/* vendor/*)
add_executable(platformer ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(platformer ${SFML_LIBRARIES})
endif()

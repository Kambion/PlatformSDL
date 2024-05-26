cmake_minimum_required(VERSION 3.20)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
project(PlatformSDL)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory("external/SDL")
add_subdirectory("external/SDL_ttf")

set(SOURCES 
    src/main.cpp
)

set(HEADERS 
    include/game.h
)

set(FONTS_FOLDER ${ROOT_DIR}fonts)
set(IMAGES_FOLDER ${ROOT_DIR}images)

add_executable(PlatformSDL ${SOURCES} "src/GameEngine.cpp" "include/GameEngine.h" "src/Window.cpp" "include/Window.h")

include_directories(${CMAKE_SOURCE_DIR}/include)
target_include_directories(PlatformSDL PUBLIC "${CMAKE_SOURCE_DIR}/external/SDL/include/")
target_link_libraries(PlatformSDL PRIVATE SDL3::SDL3)
target_include_directories(PlatformSDL PUBLIC "${CMAKE_SOURCE_DIR}/external/SDL_ttf/include/")
target_link_libraries(PlatformSDL PRIVATE SDL3_ttf::SDL3_ttf)


set(RELEASE_BUILD_DIR ${CMAKE_BINARY_DIR}/Release)
file(COPY ${FONTS_FOLDER} DESTINATION ${RELEASE_BUILD_DIR})
file(COPY ${IMAGES_FOLDER} DESTINATION ${RELEASE_BUILD_DIR})


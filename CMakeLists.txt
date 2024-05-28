cmake_minimum_required(VERSION 3.20)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
project(PlatformSDL)
set(CMAKE_CXX_STANDARD 17)


set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)


add_subdirectory("external/SDL")
add_subdirectory("external/SDL_ttf")

set(FONTS_FOLDER ${ROOT_DIR}fonts)
set(IMAGES_FOLDER ${ROOT_DIR}images)

add_executable(PlatformSDL "src/main.cpp" "src/Game.cpp" "include/Game.h" "src/Window.cpp" "include/Window.h" "include/MenuEngine.h" "src/MenuEngine.cpp" "src/MenuButton.cpp" "include/MenuButton.h" "include/Fonts.h")

set(BOOST_ROOT "C:/Program Files/boost/boost_1_82_0")
set(BOOST_LIBRARYDIR "C:/Program Files/boost/boost_1_82_0/stage/lib")

find_package(Boost 1.82 REQUIRED COMPONENTS thread)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(PlatformSDL ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Could not find Boost libraries!")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
target_include_directories(PlatformSDL PUBLIC "${CMAKE_SOURCE_DIR}/external/SDL/include/")
target_link_libraries(PlatformSDL SDL3::SDL3)
target_include_directories(PlatformSDL PUBLIC "${CMAKE_SOURCE_DIR}/external/SDL_ttf/include/")
target_link_libraries(PlatformSDL SDL3_ttf::SDL3_ttf)


set(RELEASE_BUILD_DIR ${CMAKE_BINARY_DIR})
file(COPY ${FONTS_FOLDER} DESTINATION ${RELEASE_BUILD_DIR})
file(COPY ${IMAGES_FOLDER} DESTINATION ${RELEASE_BUILD_DIR})


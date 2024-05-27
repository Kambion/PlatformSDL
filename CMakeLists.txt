cmake_minimum_required(VERSION 3.20)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
project(PlatformSDL)
set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Program Files/boost/boost_1_82_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Program Files/boost/boost_1_82_0/stage/lib")

set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.82 REQUIRED)

add_subdirectory("external/SDL")
add_subdirectory("external/SDL_ttf")

set(FONTS_FOLDER ${ROOT_DIR}fonts)
set(IMAGES_FOLDER ${ROOT_DIR}images)

add_executable(PlatformSDL "src/main.cpp" "src/GameEngine.cpp" "include/GameEngine.h" "src/Window.cpp" "include/Window.h")

if(Boost_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    message(STATUS "Found BOOST ${Boost_VERSION_STRING}")
else()
    message(STATUS "WEBSOCKET BOOST Not Found")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
target_include_directories(PlatformSDL PUBLIC "${CMAKE_SOURCE_DIR}/external/SDL/include/")
target_link_libraries(PlatformSDL PRIVATE SDL3::SDL3)
target_include_directories(PlatformSDL PUBLIC "${CMAKE_SOURCE_DIR}/external/SDL_ttf/include/")
target_link_libraries(PlatformSDL PRIVATE SDL3_ttf::SDL3_ttf)


set(RELEASE_BUILD_DIR ${CMAKE_BINARY_DIR})
file(COPY ${FONTS_FOLDER} DESTINATION ${RELEASE_BUILD_DIR})
file(COPY ${IMAGES_FOLDER} DESTINATION ${RELEASE_BUILD_DIR})


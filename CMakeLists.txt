cmake_minimum_required(VERSION 3.10)

project(arcade)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LOCAL_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/)
set(LOCAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(LOCAL_GAMES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/games/)
set(LOCAL_GRAPHICS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/)
set(LOCAL_CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/core/)
set(LOCAL_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)

# Adding games library
# -> nibbler
# add_subdirectory(${LOCAL_GAMES_DIR}/nibbler/)
# -> pacman
add_subdirectory(${LOCAL_GAMES_DIR}/pacman/)

# Adding graphics library
# -> ncurses
add_subdirectory(${LOCAL_GRAPHICS_DIR}/ncurses/)
# -> sdl2
# add_subdirectory(${LOCAL_GRAPHICS_DIR}/sdl2/)
# # -> sfml
# add_subdirectory(${LOCAL_GRAPHICS_DIR}/sfml/)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
# Adding core program
add_executable(${PROJECT_NAME}
    ${LOCAL_SRC_DIR}/main.cpp
    ${LOCAL_SRC_DIR}/utils.cpp
    ${LOCAL_CORE_DIR}/Core.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
                            "${LOCAL_INCLUDE_DIR}"
                            "${PROJECT_BINARY_DIR}"
                            "${LOCAL_CORE_DIR}"
                          )

target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
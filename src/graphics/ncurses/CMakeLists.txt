cmake_minimum_required(VERSION 3.10)

project(arcade_ncurses)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} SHARED
    Ncurses.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
                            "${LOCAL_INCLUDE_DIR}"
                            "${PROJECT_BINARY_DIR}"
                          )

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       $<TARGET_FILE:${PROJECT_NAME}>
                       ${LOCAL_LIB_DIR}
                   COMMENT "Copying '${PROJECT_NAME}' library to '${LOCAL_LIB_DIR}'")
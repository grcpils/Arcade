cmake_minimum_required(VERSION 3.10)

project(arcade)

set(LOCAL_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/)
set(LOCAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)


add_subdirectory(lib_bar)
add_subdirectory(lib_baz)
add_subdirectory(lib_foo)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
                            "${LOCAL_INCLUDE_DIR}"
                            "${PROJECT_BINARY_DIR}"
                          )

target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
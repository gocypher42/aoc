set(OG_CMAKE_PATH ../../cmake)

include(${OG_CMAKE_PATH}/cmake_min_ver.cmake)

include(${OG_CMAKE_PATH}/compiler_options.cmake)
include(${OG_CMAKE_PATH}/get_target_name.cmake)

cmake_minimum_required(VERSION ${OG_MIN_CMAKE_VER})

get_target_name()

project(${TARGET}
        LANGUAGES CXX
        VERSION 1.0)

set(UTILS_PATH ../../utils)

add_subdirectory(${UTILS_PATH} utils)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${UTILS_PATH})
target_link_libraries(${PROJECT_NAME} utils)


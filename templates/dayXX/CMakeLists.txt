cmake_minimum_required(VERSION 3.16.3)

get_filename_component(DIR_ONE_ABOVE ./ ABSOLUTE)
cmake_path(GET DIR_ONE_ABOVE FILENAME TARGET)

project(${TARGET}
        LANGUAGES CXX
        VERSION 1.0)

include(../../cmake/compile_flags.cmake)

set(UTILS_PATH ../../utils)

add_subdirectory(${UTILS_PATH} utils)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${UTILS_PATH})
target_link_libraries(${PROJECT_NAME} utils)


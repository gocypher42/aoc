add_executable(day1 main.cpp
                    ../utils/utils.cpp
)
target_include_directories(day1 PRIVATE ../utils)
target_link_libraries(day1 PRIVATE fmt)

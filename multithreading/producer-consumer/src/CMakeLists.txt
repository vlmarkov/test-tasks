cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED on)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(producer-consumer main.c)

add_subdirectory(producer)
add_subdirectory(consumer)
add_subdirectory(scheduler)
add_subdirectory(signal)

target_link_libraries(producer-consumer
                      producer-lib
                      consumer-lib
                      scheduler-lib
                      signal-lib
                      pthread)

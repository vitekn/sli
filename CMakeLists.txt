cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type")
set(CMAKE_CXX_FLAGS "-std=gnu++11")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

project(sli)

file(GLOB SLI_SRC
    "src/*.cpp"
)

add_executable(sli ${SLI_SRC})

install(TARGETS sli RUNTIME DESTINATION bin)

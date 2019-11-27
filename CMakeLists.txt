cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type")
set(CMAKE_CXX_FLAGS "-std=gnu++11")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

project(sli)

file(GLOB LIB_SRC
    "src/lib/*.cpp"
)

add_library(${PROJECT_NAME}_lib STATIC ${LIB_SRC})

add_executable(${PROJECT_NAME} src/main.cpp)

include_directories(src/tests)

target_link_libraries(${PROJECT_NAME}
                      ${PROJECT_NAME}_lib)


link_directories(src/tests/lib)
enable_testing()

add_executable(SegmentUtil_test src/tests/SegmentUtil_test.cpp)
target_link_libraries(SegmentUtil_test ${PROJECT_SOURCE_DIR}/src/tests/lib/libgtest.a ${PROJECT_SOURCE_DIR}/src/tests/lib/libgtest_main.a ${PROJECT_NAME}_lib pthread)
add_test(NAME SegmentUtil
         COMMAND SegmentUtil_test)
    
    
install(TARGETS sli RUNTIME DESTINATION bin)

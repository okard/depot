

project(libmpt)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


include_directories(include)
file(GLOB_RECURSE LIBMPT_SOURCES src/*.cpp)
add_library(libmpt ${LIBMPT_SOURCES})
target_link_libraries(libmpt "portaudio")

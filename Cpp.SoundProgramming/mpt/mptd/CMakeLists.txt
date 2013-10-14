
project(mptd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../libmpt/include)
file(GLOB_RECURSE MPTD_SOURCES src/*.cpp)
add_executable(mptd ${MPTD_SOURCES})
target_link_libraries(mptd libmpt)

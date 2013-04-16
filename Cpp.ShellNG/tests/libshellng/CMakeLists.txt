

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")
include_directories(${CMAKE_SOURCE_DIR}/libshellng/include)

# tests
add_executable(lexer_test "lexer.cpp")
target_link_libraries(lexer_test libshellng)

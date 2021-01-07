set(target tests)

set(CATCH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/catch2)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

FILE(GLOB hdrs "*.h")
FILE(GLOB srcs "*.cc")

add_executable(${target} ${hdrs} ${srcs})
target_link_libraries(${target} Catch)

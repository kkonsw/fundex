set(target ${FUNDEX_CLI_LIBRARY})

include_directories(${SOURCE_DIR} ${3RD_PARTY_SOURCE_DIR})

# cli11 lib
set(CLI11_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/CLI11)
add_library(CLI11 INTERFACE)
target_include_directories(CLI11 INTERFACE ${CLI11_INCLUDE_DIR})

FILE(GLOB hdrs "*.h")
FILE(GLOB srcs "*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} PRIVATE ${FUNDEX_DB_ORM_LIBRARY} CLI11 fort)

set(target ${FUNDEX_CLI_LIBRARY})

include_directories(${SOURCE_DIR} ${3RD_PARTY_SOURCE_DIR})

FILE(GLOB hdrs "*.h")
FILE(GLOB srcs "*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} CLI11)

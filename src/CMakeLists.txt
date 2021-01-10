set(target ${PROJECT_NAME})

include_directories(${SOURCE_DIR} ${3RD_PARTY_SOURCE_DIR})

FILE(GLOB hdrs "*.h")
FILE(GLOB srcs "*.cpp")

add_executable(${target} ${hdrs} ${srcs})
target_link_libraries(${target} ${FUNDEX_DB_ORM_LIBRARY} ${FUNDEX_CLI_LIBRARY} CLI11)

set(target ${FUNDEX_DB_ORM_LIBRARY})

include_directories(${SOURCE_DIR} ${3RD_PARTY_SOURCE_DIR})

set(SQLITE_ORM_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/sqlite_orm)
add_library(sqlite_orm INTERFACE)
target_include_directories(sqlite_orm INTERFACE ${SQLITE_ORM_INCLUDE_DIR})

FILE(GLOB hdrs "*.h")
FILE(GLOB srcs "*.cpp")

# for libsqlite3
include_directories(/usr/include)
link_directories(/usr/lib)

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} PRIVATE sqlite_orm sqlite3 fort)

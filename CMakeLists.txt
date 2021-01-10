cmake_minimum_required(VERSION 3.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

set(PROJECT_NAME fundex)
project(${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(3RD_PARTY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/3rdparty)

# fundex db orm
set(FUNDEX_DB_ORM_LIBRARY "fundex-db-orm-lib")
set(FUNDEX_DB_ORM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/db)
add_subdirectory(src/db)

# cli11 lib
set(CLI11_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/CLI11)
add_library(CLI11 INTERFACE)
target_include_directories(CLI11 INTERFACE ${CLI11_INCLUDE_DIR})

# fundex cli
set(FUNDEX_CLI_LIBRARY "fundex-cli-lib")
set(FUNDEX_CLI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/cli)
add_subdirectory(src/cli)

add_subdirectory(src)
add_subdirectory(tests)

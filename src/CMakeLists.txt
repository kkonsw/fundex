set(target fundex)

FILE(GLOB hdrs "*.h")
FILE(GLOB srcs "*.cc")

add_executable(${target} ${hdrs} ${srcs})

set(target fort)

FILE(GLOB hdrs "*.h")
FILE(GLOB srcs "*.c")

add_library(${target} STATIC ${srcs} ${hdrs})

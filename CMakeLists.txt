cmake_minimum_required(VERSION 3.10)
project(arcfour_project C)

set(SOURCES
    src/main.c
    src/arcfour.c
)

add_executable(arcfour ${SOURCES})

# Inclui o diretório com os headers
target_include_directories(arcfour PRIVATE src)

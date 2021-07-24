include(FindPkgConfig)
cmake_minimum_required(VERSION 3.10)
project(Master VERSION 1.0)

add_executable(Master Master.c)
pkg_search_module(MODBUS REQUIRED libmodbus)

target_sources(Master
    PRIVATE
    "src/Decoder.c"
    "src/Modbus.c")

target_include_directories(Master
    PUBLIC
    ${MODBUS_INCLUDE_DIRS}
    inc)

target_link_libraries(Master ${MODBUS_LIBRARIES})


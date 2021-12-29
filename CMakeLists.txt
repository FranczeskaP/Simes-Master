include(FindPkgConfig)
cmake_minimum_required(VERSION 3.10)
project(Master VERSION 1.0)

add_executable(Master Master.c)
pkg_search_module(MODBUS REQUIRED libmodbus)
pkg_search_module(MQTT REQUIRED libmosquitto)

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

target_sources(Master
    PRIVATE
    "Common/Configuration/Configuration.c"
    "Common/CsvParser/csvparser.c"
    "Common/Curl/PostData.c"
    "Common/DataTypes/DataTypes.c"
    "Common/Json/cJSON.c"
    "Modbus/Decoder/Decoder.c"
    "Modbus/ModbusMaster/Modbus.c"
    "Mqtt/MqttMaster.c")

target_include_directories(Master
    PUBLIC
    ${MODBUS_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
    ${MQTT_INCLUDE_DIRS}
    Common/Configuration
    Common/CsvParser
    Common/Curl
    Common/DataTypes
    Common/Json
    Modbus/Decoder
    Modbus/ModbusMaster
    Mqtt)

target_link_libraries(Master 
    m #math lib
    ${MODBUS_LIBRARIES}
    ${MQTT_LIBRARIES}
    ${CURL_LIBRARIES})


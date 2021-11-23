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
    "Modbus/Decoder/Decoder.c"
    "Modbus/ModbusMaster/Modbus.c"
    "Common/Curl/PostData.c"
    "Common/Json/cJSON.c"
    "Common/Configuration/Configuration.c"
    "Common/CsvParser/csvparser.c"
    "Mqtt/MqttMaster/MqttMaster.c"
    "Mqtt/MqttDefinitions/MqttDefinitions.c")

target_include_directories(Master
    PUBLIC
    ${MODBUS_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
    ${MQTT_INCLUDE_DIRS}
    Modbus/Decoder
    Modbus/ModbusMaster
    Common/Curl
    Common/Json
    Common/Configuration
    Common/CsvParser
    Mqtt/MqttMaster
    Mqtt/MqttDefinitions)

target_link_libraries(Master 
    ${MODBUS_LIBRARIES}
    ${MQTT_LIBRARIES}
    ${CURL_LIBRARIES})


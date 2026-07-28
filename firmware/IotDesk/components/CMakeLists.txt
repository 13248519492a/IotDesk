file(GLOB UI_SOURCES ui/*.c)
file(GLOB PROTOCLOS_SOURCES protocols/*.c)
file(GLOB APP_SOURCES app/*.c)
file(GLOB TEST_SOURCES test/*.c)

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/ui"
    "${CMAKE_CURRENT_SOURCE_DIR}/protocols"
    "${CMAKE_CURRENT_SOURCE_DIR}/app")

list(APPEND SOURCES ${UI_SOURCES})
list(APPEND SOURCES ${PROTOCLOS_SOURCES})
list(APPEND SOURCES ${APP_SOURCES})

set(INCLUDE_DIRS "." "ui" "protocols" "app")

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS ${INCLUDE_DIRS}
    PRIV_REQUIRES freertos nvs_flash esp_wifi
)
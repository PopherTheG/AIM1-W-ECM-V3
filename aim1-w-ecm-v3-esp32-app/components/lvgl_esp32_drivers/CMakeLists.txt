if(ESP_PLATFORM)

file(GLOB SOURCES *.c)

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS .
                       REQUIRES lvgl io_task TCA6416A)

endif()


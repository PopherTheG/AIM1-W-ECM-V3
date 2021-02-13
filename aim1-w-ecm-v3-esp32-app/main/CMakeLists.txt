#set(COMPONENT_SRCS "main.c" )
#set(COMPONENT_ADD_INCLUDEDIRS ".")

#register_component()

set(SOURCES main.c)
idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS .)

target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_LVGL_H_INCLUDE_SIMPLE")

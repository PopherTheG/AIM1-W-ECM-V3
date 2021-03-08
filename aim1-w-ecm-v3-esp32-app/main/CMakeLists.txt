set(COMPONENT_SRCS "main.c" )
set(COMPONENT_ADD_INCLUDEDIRS ".")

register_component()

target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_LVGL_H_INCLUDE_SIMPLE")



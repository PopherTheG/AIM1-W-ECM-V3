set(COMPONENT_SRCS "gui.c" "voc_img_src.c" "dust_img_src.c" "temp_img_src.c" "hum_img_src.c" "logo_img_src.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_REQUIRES "lvgl" "lvgl_esp32_drivers")

register_component()
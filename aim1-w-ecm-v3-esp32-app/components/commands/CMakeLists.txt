idf_component_register( SRCS "commands_list.c" "commands_parser.c" "commands_nvs.c" "commands.c"
                       INCLUDE_DIRS "."
                       REQUIRES ""
                       PRIV_REQUIRES "nvs_flash" "io_task" "ota" "cloud" "esp32-wifi-manager" "irtransmitter" )
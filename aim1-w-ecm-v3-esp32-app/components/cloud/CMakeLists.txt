set(COMPONENT_SRCS "cloud_api.c" "cloud_mqtt.c" "cloud_tcp.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_PRIV_REQUIRES "mqtt")

register_component()
set(COMPONENT_SRCS "telemetry_decoder.c" "telemetry_encoder.c" "telemetry.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_PRIV_REQUIRES "cloud" "sgp_40_voc_index" "sensirion-embedded-common")

register_component()
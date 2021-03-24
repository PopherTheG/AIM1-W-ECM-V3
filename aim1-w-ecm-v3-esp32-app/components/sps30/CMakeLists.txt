set(COMPONENT_SRCS "sps_git_version.c" "sps30.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_PRIV_REQUIRES "sensirion-embedded-common" "cloud" "telemetry")

register_component()
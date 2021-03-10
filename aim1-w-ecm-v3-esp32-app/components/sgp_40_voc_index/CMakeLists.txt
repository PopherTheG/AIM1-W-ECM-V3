set(COMPONENT_SRCS "sgp40_voc_index_task.c" "sensirion_voc_algorithm.c" "sgp_git_version.c" "sgp40_voc_index.c" "sgp40.c" "sht_git_version.c" "sht4x.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_PRIV_REQUIRES "sensirion-embedded-common")

register_component()
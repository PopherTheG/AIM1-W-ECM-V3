#ifndef COMPONENTS_COMMANDS_COMMANDS_PARSER
#define COMPONENTS_COMMANDS_COMMANDS_PARSER

#include <stdint.h>

size_t command_parser_relay(char* param, char* out, void* arg);

size_t command_parser_restart(char* param, char* out, void* arg);

size_t command_parser_wifi_ap_config(char* param, char* out, void* arg);

size_t command_parser_ota_start(char* param, char* out, void* arg);

size_t command_parser_ota_url(char* param, char* out, void* arg);

size_t command_parser_cloud(char* param, char* out, void* arg);

size_t command_parser_samsung(char* param, char* out, void* args);

size_t command_parser_stoggle(char* param, char* out, void* args);

size_t command_parser_soff(char* param, char* out, void* args);

size_t command_parser_ctrl(char* param, char* out, void* args);

#endif /* COMPONENTS_COMMANDS_COMMANDS_PARSER */

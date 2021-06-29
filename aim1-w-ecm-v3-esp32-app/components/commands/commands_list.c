#include <string.h>
#include <ctype.h>

#include "esp_log.h"
#include "esp_err.h"
#include "commands_parser.h"
#include "commands_list.h"

#define AT_STORAGE_SIZE 40

typedef struct
{
    uint32_t hash;
    commands_parser_cb parser;
} at_cmd_t;

static at_cmd_t at_db[AT_STORAGE_SIZE];
static uint32_t at_db_cnt = 0;

static uint32_t at_hash(const char *cmd)
{
    uint16_t ch = 0;
    uint32_t hash = 4321;

    while ((ch = *(cmd++)))
        hash = ((hash << 2) + hash) + tolower(ch);

    return hash;
}

static int16_t at_search(const char *cmd)
{
    uint16_t i;
    uint32_t tmp_hash = at_hash(cmd);

    for (i = 0; i < at_db_cnt; i++)
        if (at_db[i].hash == tmp_hash)
            return i;

    return -1;
}

static int at_add_to_db(char *command, commands_parser_cb parser)
{
    at_cmd_t cmd;
    cmd.hash = at_hash(command);
    cmd.parser = parser;

    if (strlen(command) >= 15)
        return -1;

    if (at_db_cnt == AT_STORAGE_SIZE)
        return -2;

    // if (at_search(command))
    //     return -3;

    at_db[at_db_cnt] = cmd;
    at_db_cnt++;

    return 0;
}

void commands_list_init(void)
{
    esp_err_t err;
    memset(at_db, 0, sizeof(at_db));

    at_add_to_db("+RELAY", command_parser_relay);
    at_add_to_db("+RESTART", command_parser_restart);
    at_add_to_db("+OTA", command_parser_ota_start);
    at_add_to_db("+OTAURL", command_parser_ota_url);
    at_add_to_db("+CLOUD", command_parser_cloud);
    at_add_to_db("+SAMSUNG", command_parser_samsung );
    at_add_to_db("+STOGGLE", command_parser_stoggle);
    at_add_to_db("+SOFF", command_parser_soff);
    at_add_to_db("+CTRL", command_parser_ctrl);
}

commands_parser_cb commands_list_search(const char *command)
{
    int16_t index = at_search(command);
    if (index < 0)
    {
        return NULL;
    }

    return at_db[index].parser;
}
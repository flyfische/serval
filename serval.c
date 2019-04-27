#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "serval.h"

int serval_init(serval_t *serval) {
    LOG_DEBUG("Initializing new serval instance");
    if (serval->_valid) {
        LOG_ERROR("Serval instance is already initialized!");
        return 1;
    }
    serval->_valid = true;
    serval->_running = false;
    return 0;
}

int serval_setopt(serval_t *serval, serval_opt_t opt, void *arg) {
    switch(opt) {
        case SERVAL_OPT_PORT: {
            if (arg == NULL) {
                LOG_ERROR("Received NULL argument for OPT_PORT");
                return 1;
            }
            strncpy(serval->_port, (char*)arg, SERVAL_MAX_PORT_LEN);
            LOG_INFO("Set OPT_PORT to <%s>", (char*)arg);
            return 0;
            break;
        }
        case SERVAL_OPT_IFACE: {
            break;
        }
        case SERVAL_OPT_CONNECT_FUNC: {
            serval->connect_func = arg;
            break;
        }
        case SERVAL_OPT_CONNECT_PRIV: {
            serval->connect_priv = arg;
            break;
        }
        case SERVAL_OPT_MESSAGE_FUNC: {
            serval->message_func = arg;
            break;
        }
        case SERVAL_OPT_MESSAGE_PRIV: {
            serval->message_priv = arg;
            break;
        }
        case SERVAL_OPT_INVALID:
        default: {
            LOG_ERROR("Invalid setopt parameter: <%d>", opt);
        }
    }
}

int serval_start(serval_t *serval) {
    serval->_running = true;
}

int serval_stop(serval_t *serval) {
    serval->_running = false;
}

int main(int argc, char **argv) {
    serval_t serval;
    memset((void*)&serval, 0, sizeof(serval));
    if (serval_init(&serval) != 0) {
        LOG_INFO("Error creating serval instance");
        return 1;
    }
    LOG_INFO("Successfully created serval instance");
    serval_setopt(&serval, SERVAL_OPT_PORT, "8080");
}
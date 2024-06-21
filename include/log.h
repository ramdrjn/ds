#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>

enum LOG_LEVELS
{
    DEBUG,
    INFO,
    ERROR,
};

static enum LOG_LEVELS log_level = INFO;

#define dbgval(...) {                           \
        if (log_level <= DEBUG)                 \
            printf(__VA_ARGS__);                \
    }

#define dbg(...) {                              \
        if (log_level <= DEBUG)                 \
            printf("\nDBG: "__VA_ARGS__);       \
    }

#define info(...) {                             \
        if (log_level <= INFO)                  \
            printf("\nINFO: "__VA_ARGS__);      \
    }

#define err(...) {                              \
        if (log_level <= ERROR)                 \
            printf("\nerr: "__VA_ARGS__);       \
    }

#endif /*_LOG_H_*/

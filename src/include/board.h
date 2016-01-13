#pragma once

#define BOARD_NAME_LEN 32
#define BOARD_FULLNAME_LEN 96

#include "thread.h"

static const int MAX_THREADS_DEFAULT = 150;

typedef struct {
    char name[BOARD_NAME_LEN];
    char fullname[BOARD_FULLNAME_LEN];
    short max_threads;
    /* Queue of threads */
    Thread *threads;
    short first_thread; /* Used in queue implementation */
    short last_thread;  /* same as above */
} Board;


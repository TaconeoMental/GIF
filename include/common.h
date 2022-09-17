#ifndef GIF_COMMON_H
#define GIF_COMMON_H

#include <inttypes.h>
#include "mini_log.h"

// Semver
#define GIF_PATCH_LEVEL 0
#define GIF_MINOR_VERSION 1
#define GIF_MAJOR_VERSION 0

#define GIF_SEMVER_STRING\
    STR(GIF_MAJOR_VERSION) "." STR(GIF_MINOR_VERSION) "." STR(GIF_PATCH_LEVEL)

// Transforma a A en un literal str sin expandirlo antes
#define STRNX(A) #A

// Transforma a A en un literal str después de expandirlo
#define STR(A) STRNX(A)

// Paja
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// Char pointer cast
#define CPC(str) (char *)str

#define COUNT_OF(x) (sizeof(x) / sizeof(x[0]))

// máxima cantidad de subdirectorios a los que se puede acceder, sin contar
// root.
#define MAX_DIRECTORY_LEVELS 3
#define MAX_FILENAME_LENGTH 15
// +1 para los '/' y +1 para el '/' del root
#define MAX_PATH_LENGTH (1 + MAX_DIRECTORY_LEVELS * (MAX_FILENAME_LENGTH + 1))

// FUNA FUNA FUNA FUNA...
#define SIMPLE_ALLOC(x) (x *)pvPortMalloc(sizeof(x))

// Autofuna
#define _assert(condition, msg) \
    do { \
        if (!(condition)) { \
            MLOG_E(msg); \
            exit(0);} \
    } while(0)

#define assert_c(condition) _assert(condition, "Assert error: '" STRNX(condition) "'")
#define assert_ptr(ptr) _assert(ptr != NULL, "'" STRNX(ptr) "' is a null pointer!")

#endif

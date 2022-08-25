#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "text.hpp"


void freeText(text *t) {


    for (size_t i = 0; i < t->linesNumber; i++) {
        free(t->lines[i]);
    }

    free(t->lines);
}

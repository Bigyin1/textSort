#include <assert.h>
#include <errno.h>
#include <string.h>
#include "text.hpp"



void writeTextToStream(text *t, FILE *s) {
    assert(t != NULL && s != NULL);

    for (size_t i = 0; i < t->linesNumber; i++) {
        if (fputs(t->lines[i], s) == EOF) {
            fprintf(stderr, "something went wrong: %s\n", strerror(errno));
        }
    }
    fflush(s);

}

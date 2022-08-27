#include <assert.h>
#include <errno.h>
#include <string.h>
#include "text.hpp"


textError writeTextToStream(text *t, FILE *s) {
    assert(t != NULL && s != NULL);

    for (size_t i = 0; i < t->linesCount; i++) {
        if (fputs(t->textLines[i].originalLine, s) == EOF) {
            return E_WRITE;
        }
    }

    fflush(s);
    return E_OK;
}

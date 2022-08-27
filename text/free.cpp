#include <assert.h>
#include <stdlib.h>
#include "text.hpp"


void freeText(text *t) {
    assert(t != NULL);

    for (size_t i = 0; i < t->linesCount; i++) {
        line ll = t->textLines[i];
        free(ll.originalLine);
    }

    free(t->textLines);
}

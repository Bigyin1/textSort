#include <assert.h>
#include <stdlib.h>
#include "text.hpp"


void freeText(text *t) {
    assert(t != NULL);

    free(t->text);
    free(t->textLines);
}

#include <assert.h>
#include <errno.h>
#include <string.h>
#include "text.hpp"


textError writeTextToStream(text *t, FILE *s) {
    assert(t != NULL && s != NULL);

    for (size_t i = 0; i < t->textSize; i++) {
        if (t->text[i] == '\n')
            t->text[i] = '\0';
    }

    for (size_t i = 0; i < t->linesCount; i++) {
        if (t->textLines[i].originalLine == NULL)
            continue;
        if (fputs(t->textLines[i].originalLine, s) == EOF) {
            return E_WRITE;
        }
        if (fputc('\n', s) == EOF)
            return E_WRITE;
    }
    fflush(s);
    return E_OK;
}

textError writeInitialTextToStream(text *t, FILE *s) {
    assert(t != NULL && s != NULL);

    for (size_t i = 0; i < t->textSize; i++) {
        if (t->text[i] == '\0')
            t->text[i] = '\n';
    }

    if (fputs(t->text, s) == EOF)
        return E_WRITE;

    return E_OK;
}

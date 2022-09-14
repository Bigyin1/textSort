#include <assert.h>
#include <errno.h>
#include <string.h>
#include "text.hpp"


static int fputsNL(const char *s, FILE *stream) {
    assert(s != NULL && stream != NULL);

    for (size_t i = 0; s[i] != '\n'; i++) {
        if (fputc(s[i], stream) == EOF)
            return EOF;
    }

    if (fputc('\n', stream) == EOF)
        return EOF;

    return 1;
}


textError writeTextLinesToStream(const text *t, FILE *s) {
    assert(t != NULL && s != NULL);

    for (size_t i = 0; i < t->linesCount; i++) {
        if (t->textLines[i].originalLine == NULL)
            continue;
        if (fputsNL(t->textLines[i].originalLine, s) == EOF) {
            return E_WRITE;
        }
    }
    fflush(s);
    return E_OK;
}

textError writeInitialTextToStream(text *t, FILE *s) {
    assert(t != NULL && s != NULL);

    if (fputs(t->text, s) == EOF)
        return E_WRITE;

    return E_OK;
}

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "text.hpp"



/**
 *  @brief Reads line from stream, using getline std function
 *  @param [out] retLine Pointer to line
 *  @param s File stream to read from
 *  @return  0 on success, E_ALLOC
 */
static textError readLineFromStream(char **retLine, FILE *s) {
    assert(retLine != NULL && s != NULL);

    char *line = NULL;
    size_t n = 0;

    errno = 0;

    ssize_t c = getline(&line, &n, s);
    if (c == -1) {
        assert(errno != EINVAL);

        if (errno == ENOMEM)
            return E_ALLOC;
    }

    *retLine = line;

    return E_OK;
}


textError readTextFromStream(text *t, FILE *s) {
    assert(t != NULL && s != NULL);

    const size_t initCapacity = 16;
    const size_t capMultFactor = 2;


    t->linesNumber = 0;
    t->linesCapacity = initCapacity;
    t->lines = (char **)realloc(NULL, sizeof(char*) * t->linesCapacity);

    while (!feof(s)) {
        textError readErr = readLineFromStream(t->lines + t->linesNumber, s);
        if (readErr != E_OK)
            return readErr;

        ++t->linesNumber;

        if (t->linesNumber == t->linesCapacity) {
            t->linesCapacity *= capMultFactor;
            t->lines = (char **)realloc(t->lines, sizeof(char*) * t->linesCapacity);
        }
    }

    return E_OK;
}

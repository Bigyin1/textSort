#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "text.hpp"


/**
 *  @brief Reads line from stream, using getline std function
 *  @param [out] retLine Pointer to line
 *  @param [in] s File stream to read from
 *  @return  E_OK on success, E_NO_DATA on E_ALLOC
 */
static textError readLineFromStream(line *retLine, FILE *s) {
    assert(retLine != NULL && s != NULL);

    char *rawLine = NULL;
    size_t n = 0;

    ssize_t c = getline(&rawLine, &n, s);
    if (c == -1) {
        free(rawLine);
        retLine->originalLine = NULL;

        if (errno == ENOMEM)
            return E_ALLOC;
        if (errno == EINVAL)
            return E_READ;

        return E_OK;
    }

    retLine->originalLine = rawLine;
    return E_OK;
}


/**
 *  @brief Trims spaces from start of line
 *  Sets trimmed line to l->processedLine
 *  @param  line Pointer to line
 */
static void processLine(line *l) {

    char *lineStart = l->originalLine;

    while(isspace(*lineStart))
        ++lineStart;

    if (*lineStart  == '\0') {
        free(l->originalLine);
        l->originalLine = NULL;
        return;
    }

    l->processedLine = lineStart;

}


static textError growLines(text *t) {
    assert(t != NULL);

    const size_t capMultFactor = 2;

    t->linesCapacity *= capMultFactor;
    line *newLines = (line *)reallocarray(t->textLines,
            sizeof(line), t->linesCapacity);
    if (newLines == NULL)
        return E_ALLOC;

    if (newLines != t->textLines)
        memset(newLines + t->linesCount, 0,
         sizeof(line) * (t->linesCapacity - t->linesCount));

    t->textLines = newLines;
    return E_OK;
}


textError readTextFromStream(text *t, FILE *s) {
    assert(t != NULL && s != NULL);

    const size_t initCapacity = 16;

    t->linesCount = 0;
    t->linesCapacity = initCapacity;
    t->textLines = (line *)calloc(sizeof(line), t->linesCapacity);
    if (t->textLines == NULL)
        return E_ALLOC;

    while (!feof(s)) {
        textError readErr = readLineFromStream(&t->textLines[t->linesCount], s);
        if (readErr != E_OK)
            return readErr;

        if (t->textLines[t->linesCount].originalLine == NULL)
            break;

        processLine(&t->textLines[t->linesCount]);
        if (t->textLines[t->linesCount].originalLine != NULL)
            ++t->linesCount;

        if (t->linesCount == t->linesCapacity) {
            textError err = growLines(t);
            if (err != E_OK)
                return err;
        }
    }

    return E_OK;
}

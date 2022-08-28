#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/stat.h>
#include "text.hpp"



/**
 *  @brief Trims spaces and punctuation from start and end of line
 *  Sets trimmed line to l->processedLineStart and l->processedLineEnd
 *  @param  l Pointer to line
 */
static void processLine(line *l) {
    assert(l != NULL);

    char *lineStart = l->originalLine;

    while(isspace(*lineStart) || ispunct(*lineStart)) {
        if (*lineStart == '\n')
            break;
        ++lineStart;

    }

    if (*lineStart  == '\n') {
        l->originalLine = NULL;
        return;
    }
    l->processedLineStart = lineStart;

    char *lineEnd = strchr(lineStart, '\n');
    while (isspace(*lineEnd) || ispunct(*lineEnd))
        --lineEnd;

    ++lineEnd;

    l->processedLineEnd = lineEnd;
}


static textError setupLines(text *t) {

    char *currLineStart = t->text;
    for (size_t i = 0; i < t->linesCount; ++i) {
        line *currLine = &t->textLines[i];
        currLine->originalLine = currLineStart;

        processLine(currLine);

        currLineStart = (strchr(currLineStart, '\n') + 1);
    }
    return E_OK;
}

static size_t getLinesCount(text *t) {
    assert(t != NULL);

    size_t linesCount = 0;
    for (size_t i = 0; i < t->textSize; ++i)  {
        if (t->text[i] == '\n')
            linesCount++;
    }

    return linesCount;
}

static textError getFileSize(text *t, FILE *f) {
    assert(t != NULL && f != NULL);

    if (fseek(f, 0, SEEK_END) != 0)
        return E_READ;
    long fSize = ftell(f);
    if (fSize == -1)
        return E_READ;
    if (fseek(f, 0, SEEK_SET) != 0)
        return E_READ;

    t->textSize = (size_t)fSize;

    return E_OK;
}

static void insertFinalNewline(text *t) {
    t->text[t->textSize + 1] = '\0';
    if (t->text[t->textSize - 1] != '\n')
        t->text[t->textSize] = '\n';
    else
        t->text[t->textSize] = '\0';
}

textError readTextFromFile(text *t, FILE *f) {
    assert(t != NULL && f!= NULL);

    textError err = E_OK;

    if ((err = getFileSize(t, f)) != E_OK)
        return err;

    t->text = (char *)calloc(t->textSize + 2, sizeof(*t->text));
    if (t->text == NULL)
        return E_ALLOC;

    if (fread(t->text, sizeof(*t->text), t->textSize, f) != t->textSize)
        return E_READ;

    insertFinalNewline(t);

    t->linesCount = getLinesCount(t);
    t->textLines = (line *)calloc(t->linesCount, sizeof(*t->textLines));
    if (t->textLines == NULL)
        return E_ALLOC;

    err = setupLines(t);
    if (err != NULL)
        return err;

    return E_OK;
}

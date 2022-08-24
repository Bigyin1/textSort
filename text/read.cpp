#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "text.hpp"


static int readLineFromStream(char **retLine, FILE *s) {
    assert(retLine != NULL && s != NULL);

    char *line = NULL;
    size_t n = 0;
    ssize_t c = getline(&line, &n, s);
    if (feof(s))
        return EOF;
    if (c == -1) {
        fprintf(stderr, "something went wrong: %s\n", strerror(errno));
    }
    *retLine = line;
    return 0;
}


void readTextFromStream(text *t, FILE *s) {
    assert(t != NULL && s != NULL);

    const size_t initCapacity = 16;

    t->lines = (char**)realloc(NULL, sizeof(char*) * initCapacity);

    t->linesNumber = 0;
    t->linesCapacity = initCapacity;

    while (readLineFromStream(t->lines + t->linesNumber, s) != EOF) {

        ++t->linesNumber;

        if (t->linesNumber == t->linesCapacity) {
            t->linesCapacity *= 2;
            t->lines = (char**)realloc(t->lines, sizeof(char*) * t->linesCapacity);
        }

    }

}

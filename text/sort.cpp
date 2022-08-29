#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "text.hpp"


static int cmpLines(const void *l1, const void *l2) {
    assert(l1 != NULL && l2 != NULL);

    const char *line1Start = ((const line *)l1)->processedLineStart;
    const char *line2Start = ((const line *)l2)->processedLineStart;

    const char *line1End = ((const line *)l1)->processedLineEnd;
    const char *line2End = ((const line *)l2)->processedLineEnd;

    while (line1Start != line1End && line2Start != line2End) {

        if (*line1Start == *line2Start) {
            ++line1Start;
            ++line2Start;
            continue;
        }
        break;
    }

    return (*line1Start - *line2Start);
}

static int cmpLinesReverse(const void *l1, const void *l2) {
    assert(l1 != NULL && l2 != NULL);

    const char *line1Start = ((const line *)l1)->processedLineStart;
    const char *line2Start = ((const line *)l2)->processedLineStart;

    const char *line1End = ((const line *)l1)->processedLineEnd;
    const char *line2End = ((const line *)l2)->processedLineEnd;

    while (line1End != line1Start && line2End != line2Start) {

        if (*line1End == *line2End) {
            --line1End;
            --line2End;
            continue;
        }

        break;
    }

    return (*line1End - *line2End);
}


void sortTextDirect(text *t) {

    qsort(t->textLines, t->linesCount, sizeof(line), cmpLines);

}

void sortTextReverse(text *t) {

    qsort(t->textLines, t->linesCount, sizeof(line), cmpLinesReverse);

}

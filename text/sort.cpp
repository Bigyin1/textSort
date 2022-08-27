#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "text.hpp"


static int cmpLines(const void *l1, const void *l2) {
    assert(l1 != NULL && l2 != NULL);

    const char *line1 = ((const line *)l1)->processedLineStart;
    const char *line2 = ((const line *)l2)->processedLineStart;

    while (*line1 && *line2) {

        if (*line1 == *line2) {
            ++line1;
            ++line2;
            continue;
        }

        return (*line1 - *line2);
    }

    return (*line1 - *line2);
}

static int cmpLinesReverse(const void *l1, const void *l2) {
    assert(l1 != NULL && l2 != NULL);

    const char *line1Start = ((const line *)l1)->processedLineStart;
    const char *line2Start = ((const line *)l2)->processedLineStart;

    const char *line1End = ((const line *)l1)->processedLineEnd;
    const char *line2End = ((const line *)l2)->processedLineEnd;

    do {
        --line1End;
        --line2End;

        if (*line1End == *line2End)
            continue;

        return (*line1End - *line2End);

    } while (line1End != line1Start && line2End != line2Start);

    if (line1End == line1Start && line2End == line2Start) {
        return 0;
    } else if (line1End == line1Start)  {
        return ('\0' - *line2End);
    } else {
        return (*line1End - '\0');
    }
}

static int cmpLineIdx(const void *l1, const void *l2) {
    assert(l1 != NULL && l2 != NULL);

    size_t line1Idx = ((const line *)l1)->lineIdx;
    size_t line2Idx = ((const line *)l2)->lineIdx;

    assert(line1Idx != line2Idx);

    if (line1Idx > line2Idx)
        return 1;
    else
        return -1;
}


void sortText(text *t) {

    qsort(t->textLines, t->linesCount, sizeof(line), cmpLines);

}

void sortTextReverse(text *t) {

    qsort(t->textLines, t->linesCount, sizeof(line), cmpLinesReverse);

}

void sortTextByLineOrder(text *t) {

    qsort(t->textLines, t->linesCount, sizeof(line), cmpLineIdx);

}

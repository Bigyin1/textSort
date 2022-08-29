#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "text.hpp"

static void swap(line *m1, line *m2, line *buf, size_t width) {
    memcpy(buf, m2, width);
    memcpy(m2,  m1, width);
    memcpy(m1, buf, width);
}

static line buf[1] = {0};

static void my_qsort(line *base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
    assert(base != NULL && compar != NULL && width != 0);

    if (nel <= 1)
        return;

    line *baseB = base;

    line *pivot = base;
    size_t i = 0;
    size_t j = nel - 1;

    while (i < j) {
        while (compar(pivot, &baseB[i]) >= 0 && i < j)
            ++i;
        while (compar(&baseB[j], pivot) >= 0 && i < j)
            --j;

        swap(&baseB[j--], &baseB[i++], buf, width);
    }

    swap(pivot, &baseB[j], buf, width);
    qsort(baseB, j, width, compar);
    qsort(baseB + j + 1, nel - j - 1 , width, compar);
}



static int cmpLines(const void *l1, const void *l2) {
    assert(l1 != NULL && l2 != NULL);

    const char *line1Start = ((const line *)l1)->processedLineStart;
    const char *line2Start = ((const line *)l2)->processedLineStart;

    const char *line1End = ((const line *)l1)->processedLineEnd;
    const char *line2End = ((const line *)l2)->processedLineEnd;

    while (line1Start != line1End + 1 && line2Start != line2End + 1) {

        if (*line1Start == *line2Start) {
            ++line1Start;
            ++line2Start;
            continue;
        }
        break;
    }

    if (line1End + 1 == line1Start && line2End + 1 == line2Start) {
        return 0;
    } else if (line1End + 1 == line1Start)  {
        return ('\0' - *line2Start);
    } else if (line2End + 1 == line2Start) {
        return (*line1Start - '\0');
    } else {
        return (*line1Start - *line2Start);
    }
}

static int cmpLinesReverse(const void *l1, const void *l2) {
    assert(l1 != NULL && l2 != NULL);

    const char *line1Start = ((const line *)l1)->processedLineStart;
    const char *line2Start = ((const line *)l2)->processedLineStart;

    const char *line1End = ((const line *)l1)->processedLineEnd;
    const char *line2End = ((const line *)l2)->processedLineEnd;

    while (line1End != line1Start - 1 && line2End != line2Start - 1) {

        if (*line1End == *line2End) {
            --line1End;
            --line2End;
            continue;
        }

        break;
    }

    if (line1End == line1Start - 1 && line2End == line2Start - 1) {
        return 0;
    } else if (line1End == line1Start - 1)  {
        return ('\0' - *line2End);
    } else if (line2End == line2Start - 1) {
        return (*line1End - '\0');
    } else {
        return (*line1End - *line2End);
    }
}


void sortTextDirect(text *t) {

     my_qsort(t->textLines, t->linesCount, sizeof(line), cmpLines);

}

void sortTextReverse(text *t) {

    my_qsort(t->textLines, t->linesCount, sizeof(line), cmpLinesReverse);

}

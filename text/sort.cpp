#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "text.hpp"

static void swap(void *m1, void *m2, size_t width) {
    assert(m1 != NULL && m2 != NULL);

    int64_t bufqw = 0;
    int64_t *m1qw = (int64_t *)m1;
    int64_t *m2qw = (int64_t *)m2;

    while (width >= 8) {
        bufqw = *m2qw;
        *m2qw = *m1qw;
        *m1qw = bufqw;
        ++m1qw;
        ++m2qw;
        width -= sizeof(bufqw);
    }

    char bufb = 0;
    char *m1b = (char *)m1qw;
    char *m2b = (char *)m2qw;

    while (width > 0) {
        bufb = *m2b;
        *m2b = *m1b;
        *m1b = bufb;
        ++m1b;
        ++m2b;
        width -= sizeof(bufb);
    }
}

static void my_qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
    assert(base != NULL && compar != NULL && width != 0);

    if (nel <= 1)
        return;

    char *baseB = (char *)base;

    void *pivot = &baseB[(nel >> 1) * width];

    size_t i = 0;
    size_t j = nel - 1;
    while (i < j) {
        while (i <= j && compar(pivot, &baseB[width * i]) >= 0)
            ++i;
        while (i <= j && compar(&baseB[width * j], pivot) > 0)
            --j;

        if (i < j)
            swap(&baseB[width * j--], &baseB[width * i++], width);
    }
    swap(pivot, &baseB[width * j], width);

    qsort(baseB, j, width, compar);
    qsort(baseB + width * (j + 1), nel - j - 1 , width, compar);
}



static int cmpLines(const void *l1, const void *l2) {
    assert(l1 != NULL && l2 != NULL);

    const char *line1Start = ((const line *)l1)->processedLineStart;
    const char *line2Start = ((const line *)l2)->processedLineStart;

    const char *line1End = ((const line *)l1)->processedLineEnd + 1;
    const char *line2End = ((const line *)l2)->processedLineEnd + 1;

    while (line1Start != line1End && line2Start != line2End) {

        line1Start = skipSpPunctStart(line1Start);
        line2Start = skipSpPunctStart(line2Start);

        if (*line1Start != *line2Start)
            return (*line1Start - *line2Start);

        ++line1Start;
        ++line2Start;
    }

    if (line1Start == line1End && line2Start == line2End) {
        return 0;
    } else if (line1Start == line1End)  {
        return ('\0' - *line2Start);
    } else {
        return (*line1Start - '\0');
    }
}

static int cmpLinesReverse(const void *l1, const void *l2) {
    assert(l1 != NULL && l2 != NULL);

    const char *line1Start = ((const line *)l1)->processedLineStart - 1;
    const char *line2Start = ((const line *)l2)->processedLineStart - 1;

    const char *line1End = ((const line *)l1)->processedLineEnd;
    const char *line2End = ((const line *)l2)->processedLineEnd;

    while (line1End != line1Start && line2End != line2Start) {

        line1End = skipSpPunctEnd(line1End);
        line2End = skipSpPunctEnd(line2End);

        if (*line1End != *line2End)
            return (*line1End - *line2End);

        --line1End;
        --line2End;
    }

    if (line1End == line1Start && line2End == line2Start) {
        return 0;
    } else if (line1End == line1Start)  {
        return ('\0' - *line2End);
    } else {
        return (*line1End - '\0');
    }
}


void sortTextDirect(text *t) {

     my_qsort(t->textLines, t->linesCount, sizeof(line), cmpLines);

}

void sortTextReverse(text *t) {

    my_qsort(t->textLines, t->linesCount, sizeof(line), cmpLinesReverse);

}

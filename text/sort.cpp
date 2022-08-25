#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "text.hpp"


static int cmpLines(const void *l1, const void *l2) {
    assert(l1 != NULL && l2 != NULL);

    const line *line1 = (const line *)l1;
    const line *line2 = (const line *)l2;


    return strcmp(line1->processedLine, line2->processedLine);
}


void sortText(text *t) {

    qsort(t->textLines, t->linesCount, sizeof(line), cmpLines);

}

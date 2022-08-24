#include <stdlib.h>
#include <string.h>
#include "text.hpp"


static int cmpLines(const void *l1, const void *l2) {

    return strcmp((const char*)l2, (const char*)l1);
}


void sortText(text *t) {

    qsort(t->lines, t->linesNumber, sizeof(*t->lines), cmpLines);

}

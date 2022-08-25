#include <stdlib.h>
#include <string.h>
#include "text.hpp"


static int cmpLines(const void *l1, const void *l2) {
    const char *str_p1 = *(const char **)l1;
    const char *str_p2 = *(const char **)l2;


    return strcmp(str_p1, str_p2);
}


void sortText(text *t) {

    qsort(t->lines, t->linesNumber, sizeof(*t->lines), cmpLines);

}

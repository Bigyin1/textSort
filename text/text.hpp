/** @file */
#ifndef TEXT_HPP
#define TEXT_HPP

#include <stdio.h>


/**
 * @brief Holds text data.
 */
struct text
{
    char **lines;
    size_t linesNumber;
    size_t linesCapacity;
};

typedef struct text text;



void readTextFromStream(text *t, FILE *s);

void sortText(text *t);

void writeTextToStream(text *t, FILE *s);


#endif

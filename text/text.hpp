/** @file */
#ifndef TEXT_HPP
#define TEXT_HPP

#include <stdio.h>


/**
 * @brief Holds error number.
 */
enum textError
{
    E_OK,
    E_ALLOC,
    E_NO_DATA,
};

typedef enum textError textError;


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



textError readTextFromStream(text *t, FILE *s);

void sortText(text *t);

void writeTextToStream(text *t, FILE *s);

void freeText(text *t);


#endif

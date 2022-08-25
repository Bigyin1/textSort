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
    E_READ,
    E_WRITE,
};

typedef enum textError textError;


/**
 * @brief Holds text line w/ metadata.
 */
struct line
{
    char *processedLine;
    char *originalLine;

};

typedef struct line line;

/**
 * @brief Holds text data.
 */
struct text
{
    line *textLines;
    size_t linesCount;
    size_t linesCapacity;
};

typedef struct text text;



textError readTextFromStream(text *t, FILE *s);

void sortText(text *t);

textError writeTextToStream(text *t, FILE *s);

void freeText(text *t);


#endif

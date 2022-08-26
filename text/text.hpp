/** @file */
#ifndef TEXT_HPP
#define TEXT_HPP

#include <stdio.h>


/**
 * @brief Holds error number.
 */
enum textError
{
    E_OK,       // No error occured
    E_ALLOC,    // Memory allocation error
    E_READ,     // File read error
    E_WRITE,    // File write error
};

typedef enum textError textError;


/**
 * @brief Holds text line w/ metadata.
 */
struct line
{
    char *processedLine;    // Line with trmmed trailing spaces.
    char *originalLine;     // Line that was read from file. free() should be called on this one.

};

typedef struct line line;

/**
 * @brief Holds text data.
 */
struct text
{
    line    *textLines;
    size_t  linesCount;
    size_t  linesCapacity;
};

typedef struct text text;


/**
 * @brief Reads text from stream line by line.
 * Stream can be regular file, pipe, tty.
 */
textError readTextFromStream(text *t, FILE *s);

/**
 * @brief Sorts text's lines using qsort() in ascending order by line.processedLine .
 */
void sortText(text *t);

/**
 * @brief Writes text to stream, using line.originalLine .
 */
textError writeTextToStream(text *t, FILE *s);

void freeText(text *t);


#endif

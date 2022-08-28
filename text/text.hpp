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
    char    *processedLineStart;   // Line with trmmed trailing spaces.
    char    *processedLineEnd;     // Pointer to last char of processed line
    char    *originalLine;         // Line that was read from file. free() should be called on this one.
};

typedef struct line line;

/**
 * @brief Holds text data.
 */
struct text
{
    line            *textLines;
    size_t          linesCount;
    char            *text;
    size_t          textSize;
};

typedef struct text text;


/**
 * @brief Reads text from file.
 *
 */
textError readTextFromFile(text *t, FILE *s);

/**
 * @brief Sorts text's lines using qsort() in ascending order by line.processedLineStart .
 */
void sortTextDirect(text *t);

/**
 * @brief Sorts text's lines using qsort() in ascending order by line.processedLineEnd .
 */
void sortTextReverse(text *t);


/**
 * @brief Writes text to stream, using line.originalLine.
 */
textError writeTextToStream(text *t, FILE *s);

/**
 * @brief Writes initial t.text to stream.
 */
textError writeInitialTextToStream(text *t, FILE *s);

void printError(textError err);

void freeText(text *t);


#endif

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
    const char      *processedLineStart;   // Line with trmmed trailing spaces and punctuation.
    const char      *processedLineEnd;     // Pointer to last char of processed line
    char            *originalLine;         // Line that was read from file. free() should be called on this one.
};

typedef struct line line;

/**
 * @brief Holds text data.
 */
struct text
{
    line            *textLines; // Pointer to array of lines
    size_t          linesCount; // len of lines array

    char            *text; // pointer to raw file text
    size_t          textSize; // len of raw file text
};

typedef struct text text;


/**
 * @brief Reads text from file.
 */
textError readTextFromFile(text *t, FILE *s);


/**
 * @brief Sorts text's lines using qsort() in ascending order by line.processedLineStart.
 */
void sortTextDirect(text *t);


/**
 * @brief Sorts text's lines using qsort() in ascending order by line.processedLineEnd.
 */
void sortTextReverse(text *t);


/**
 * @brief Writes sorted text lines to stream, using line.originalLine.
 */
textError writeTextLinesToStream(text *t, FILE *s);

/**
 * @brief Writes raw file text to stream.
 */
textError writeInitialTextToStream(text *t, FILE *s);

/**
 * @brief Prints error message to stderror
 */
void printError(textError err);


/**
 * @brief Frees used memory
 */
void freeText(text *t);


const char *skipSpPunctStart(const char *lineStart);

const char *skipSpPunctEnd(const char *lineEnd);


#endif

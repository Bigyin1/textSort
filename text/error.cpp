#include <stdio.h>
#include "text.hpp"

void printError(textError err) {
    switch (err)
    {
    case E_OK:
        fprintf(stderr, "No error\n");
        break;
    case E_ALLOC:
        fprintf(stderr, "Memory allocation error\n");
        break;
    case E_READ:
        fprintf(stderr, "Failed to read from file\n");
        break;
    case E_WRITE:
        fprintf(stderr, "Failed to write to file\n");
        break;
    default:
        break;
    }
}

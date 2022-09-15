#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text/text.hpp"
#include "test/test.hpp"


const char *textDelimiter = "\n\n-------------\n\n";


static void freeResources(text *t, FILE *fi, FILE *fo) {
    freeText(t);
    fclose(fi);
    fclose(fo);
}


int main(int argc, char **argv)
{
  FILE *fi = NULL;
  FILE *fo = NULL;

  if (argc != 3) {
    puts("Wrong arguments count");
    return EXIT_FAILURE;
  }

  fi = fopen(argv[1], "r");
  if (fi == NULL) {
    fprintf(stderr, "Failed to open: %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  fo = fopen(argv[2], "w");
  if (fo == NULL) {
    fprintf(stderr, "Failed to open: %s\n", argv[2]);
    fclose(fi);
    return EXIT_FAILURE;
  }

  text t = {.textLines = NULL, .linesCount = 0, .text = NULL, .textSize = 0};
  textError err = readTextFromFile(&t, fi);
  if (err != E_OK) {
    printError(err);
    freeResources(&t, fi, fo);
    return EXIT_FAILURE;
  }

  sortTextDirect(&t);

  err = writeTextLinesToStream(&t, fo);
  if (err != E_OK) {
    printError(err);
    freeResources(&t, fi, fo);
    return EXIT_FAILURE;
  }

  fputs(textDelimiter, fo);
  sortTextReverse(&t);

  err = writeTextLinesToStream(&t, fo);
  if (err != E_OK) {
    printError(err);
    freeResources(&t, fi, fo);
    return EXIT_FAILURE;
  }

  fputs(textDelimiter, fo);
  err = writeInitialTextToStream(&t, fo);
  if (err != E_OK) {
    printError(err);
    freeResources(&t, fi, fo);
    return EXIT_FAILURE;
  }

  freeResources(&t, fi, fo);
  return EXIT_SUCCESS;
}

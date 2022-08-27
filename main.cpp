#include <stdio.h>
#include "text/text.hpp"

int main(int argc, char **argv)
{
  FILE *fi = NULL;
  FILE *fo = NULL;

  if (argc == 1) {
    fi = stdin;
    fo = stdout;
  } else if (argc == 3) {
    fi =  fopen(argv[1], "r");
    if (fi == NULL) {
      fprintf(stderr, "Failed to open: %s\n", argv[1]);
      return 1;
    }
    fo =  fopen(argv[2], "w");
    if (fo == NULL) {
      fprintf(stderr, "Failed to open: %s\n", argv[2]);
      return 1;
    }
  }

  text t = {.textLines = NULL, .linesCount = 0, .linesCapacity = 0};
  textError err = readTextFromStream(&t, fi);
  if (err != E_OK) {
    freeText(&t);
    fclose(fi);
    fclose(fo);
    return 1;
  }



  sortTextReverse(&t);

  err = writeTextToStream(&t, fo);
  if (err != E_OK) {
    freeText(&t);
    return 1;
  }

  freeText(&t);
  return 0;
}

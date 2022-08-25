#include <stdio.h>
#include "text/text.hpp"

int main(int argc, char **)
{
  text t = {.textLines = NULL, .linesCount = 0, .linesCapacity = 0};

  FILE *fi =  fopen("testdata/test", "r");
  FILE *fo =  fopen("testOut", "w");
  textError err = readTextFromStream(&t, fi);
  if (err != E_OK) {
    //print err;
    freeText(&t);
    return 1;
  }

  sortText(&t);

  err = writeTextToStream(&t, fo);
  if (err != E_OK) {
    //print err;
    freeText(&t);
    return 1;
  }

  freeText(&t);

  fclose(fi);
  fclose(fo);

  return 0;
}

#include <stdio.h>
#include "text/text.hpp"

int main(int argc, char **)
{
  text t = {.lines = NULL, .linesNumber = 0, .linesCapacity = 0};

  FILE *f = fopen("test", "r");
  FILE *fo = fopen("testOut", "w");
  readTextFromStream(&t, f);

  sortText(&t);

  writeTextToStream(&t, fo);

  freeText(&t);

}

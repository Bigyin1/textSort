#include <stdio.h>
#include "text/text.hpp"

int main(int argc, char **)
{
  text t = {.lines = NULL, .linesNumber = 0, .linesCapacity = 0};

  readTextFromStream(&t, stdin);
  sortText(&t);
  writeTextToStream(&t, stdout);

}

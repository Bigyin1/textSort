#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "test.hpp"

const char *testdataDirName = "./testdata";

typedef struct testData {
    text    textInital;
    text    textSortedDirect;
    text    textSortedReverse;
    text    textSortedLineOrder;
} testData;


static bool cmpTexts(text *t1, text *t2) {
    assert(t1 != NULL && t2 != NULL);

    if (t1->linesCount != t2->linesCount) {
        fprintf(stderr, "lines count are not identical\n");
        return false;
    }

    for (size_t i = 0; i < t1->linesCount; ++i) {
        if (strcmp( t1->textLines[i].originalLine,
                    t2->textLines[i].originalLine) != 0) {

            printf("line %ld is not identical\n", i + 1);
            printf("\nGot:\n%s\nShould be:\n%s", t1->textLines[i].originalLine,
             t2->textLines[i].originalLine);
            return false;
        }
    }
    return true;
}

static void processTestData(testData *td) {
    assert(td != NULL);

    if (td->textInital.textLines == NULL) {
        fprintf(stderr, "no textInitial provided\n");
        return;
    }

    if (td->textSortedDirect.textLines != NULL) {
        printf("\nTesting direct sorting\n");
        sortTextDirect(&td->textInital);
        if (cmpTexts(&td->textInital, &td->textSortedDirect))
            puts("OK\n");
        else
            puts("FAILED\n");
    }

    if (td->textSortedReverse.textLines != NULL) {
        printf("\nTesting reverse sorting\n");
        sortTextByLineOrder(&td->textInital);
        sortTextReverse(&td->textInital);
        if (cmpTexts(&td->textInital, &td->textSortedReverse))
            puts("OK\n");
        else
            puts("FAILED\n");
    }

    if (td->textSortedLineOrder.textLines != NULL) {
        printf("\nTesting line order sorting\n");
        sortTextByLineOrder(&td->textInital);
        if (cmpTexts(&td->textInital, &td->textSortedLineOrder))
            puts("OK\n");
        else
            puts("FAILED\n");
    }

}

static void readTestTexts(testData *td, char *fName) {
    text *textCurrent = NULL;

    if (strcmp(fName, "textInitial") == 0)
        textCurrent = &td->textInital;
    else if (strcmp(fName, "textSortedDirect") == 0)
        textCurrent = &td->textSortedDirect;
    else if (strcmp(fName, "textSortedReverse") == 0)
        textCurrent = &td->textSortedReverse;
    else if (strcmp(fName, "textSortedLineOrder") == 0)
        textCurrent = &td->textSortedLineOrder;

    if (textCurrent == NULL) {
        fprintf(stderr, "unsupported test file name: %s\n", fName);
    }

    FILE *f = fopen(fName, "r");
    if (f == NULL) {
        fprintf(stderr, "failed to open file: %s\n", fName);
        return;
    }

    readTextFromFile(textCurrent, f);
    fclose(f);
}

static void getTestDataFromDir(testData *td, DIR *dir) {
    assert(td != NULL && dir != NULL);

    struct dirent *de = NULL;
    while ((de = readdir(dir)) != NULL) {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
            continue;
        if (de->d_type != DT_REG)
            continue;
        readTestTexts(td, de->d_name);
    }
}

static void runTest(struct dirent *de) {
    printf("Start testing: %s\n", de->d_name);

    DIR *textDir = opendir(de->d_name);
    if (textDir == NULL) {
        fprintf(stderr, "Failed to oped dir: %s\n", de->d_name);
        return;
    }
    if (chdir(de->d_name) != 0){
        fprintf(stderr, "Chdir to %s failed\n", de->d_name);
        return;
    }

    testData td = {0};
    getTestDataFromDir(&td, textDir);
    closedir(textDir);

    processTestData(&td);

    freeText(&td.textInital);
    freeText(&td.textSortedDirect);
    freeText(&td.textSortedLineOrder);
    freeText(&td.textSortedReverse);

    chdir("..");
}

void runTests() {

    DIR *tesdataDir = opendir(testdataDirName);
    if (tesdataDir == NULL) {
        fprintf(stderr, "Failed to oped dir: %s\n", testdataDirName);
        return;
    }
    if (chdir(testdataDirName) != 0) {
        fprintf(stderr, "Chdir to %s failed\n", testdataDirName);
        return;
    }

    struct dirent *de = NULL;

    while ((de = readdir(tesdataDir)) != NULL) {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
            continue;
        if (de->d_type != DT_DIR)
            continue;
        runTest(de);
    }
    closedir(tesdataDir);
    chdir("..");
}

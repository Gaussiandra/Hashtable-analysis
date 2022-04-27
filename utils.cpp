#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "vector.hpp"
#include "string_list.hpp"
#include "hashtable.hpp"
#include "utils.hpp"

void readDataset(const char path[], char allWords[],
                   vector *wordsPtr,
                   const char delimiters[]) {
    assert(path);
    assert(wordsPtr);
    assert(delimiters);

    FILE *inpFile = fopen(path, "r");
    fseek(inpFile, 0, SEEK_END);
    size_t szFile = (size_t) ftell(inpFile);
    rewind(inpFile);

    allWords = (char*) calloc(szFile + 1, sizeof(char));

    fread(allWords, sizeof(char), szFile, inpFile);
    fclose(inpFile);

    char *lexemePtr = strtok(allWords, delimiters);
    while (lexemePtr) {
        // strlen > 1
        if (lexemePtr[0] != '\0' && lexemePtr[1] != '\0') {
            vector_push(wordsPtr, &lexemePtr);
        }
        lexemePtr = strtok(NULL, delimiters);
    }
}


void dumpListLengths(const char path[], hashtable_t *ht, bool createNew) {
    assert(path);
    assert(ht);

    FILE *file = fopen(path, createNew ? "w" : "a");

    fprintf(file, "%s:", ht->name);
    for (size_t i = 0; i < ht->capacity; ++i) {
        fprintf(file, "%zu ", list_length_slow(ht->addrs[i]));
    }
    fprintf(file, "\n");

    fclose(file);
}
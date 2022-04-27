#include <cassert>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include "vector.hpp"
#include "string_list.hpp"
#include "hashtable.hpp"
#include "utils.hpp"

const size_t SZ_HASHTABLE    = 50000;
const size_t N_INSERTS       = 3 * SZ_HASHTABLE;
const size_t N_SEARCHES      = 150 * N_INSERTS;

int main() {
    char *allWords = nullptr;
    vector *wordsPtr = vector_new(0, sizeof(char*));
    readDataset("/home/ilya/code/ded/2sem/hashtable/data/AtlasShrugged.txt", allWords, wordsPtr);

    hashtable_t *ht = htCreate(SZ_HASHTABLE, SET_HASH_FN(hashPoly));

    clock_t start = clock();

    size_t nWordsToInsert = (size_t) fmin(vector_size(wordsPtr), N_INSERTS);
    for (size_t wordIdx = 0; wordIdx < nWordsToInsert; ++wordIdx) {
        char *curPtr = nullptr;
        vector_get(wordsPtr, wordIdx, &curPtr);
        htInsert(ht, curPtr);
    }

    size_t nFound = 0, searchIdx = 0;
    while (searchIdx < N_SEARCHES) {
        size_t nWordsToFind = (size_t) fmin(vector_size(wordsPtr), N_SEARCHES - searchIdx);
        for (size_t wordIdx = 0; wordIdx < nWordsToFind; ++wordIdx) {
            char *curPtr = nullptr;
            vector_get(wordsPtr, wordIdx, &curPtr);
            if (htFind(ht, curPtr)) {
                ++nFound;
            }
        }

        searchIdx += nWordsToFind;
    }
    printf("Successful searches %zu/%zu (%.2f%%)\n", 
            nFound, N_SEARCHES, (float)nFound / N_SEARCHES * 100);

    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    printf("Time measured: %.3f seconds.\n", elapsed);

    vector_delete(wordsPtr);
    free(allWords);
    htDelete(ht);

    return 0;
}
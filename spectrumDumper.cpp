#include <cassert>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include "vector.hpp"
#include "string_list.hpp"
#include "hashtable.hpp"
#include "utils.hpp"

#define SET_HASH_FN(name) (name), (#name)
#define PUSH_NEW_HASHTABLE(...) {               \
    hashtable_t *curHt = htCreate(__VA_ARGS__); \
    vector_push(hashtables, &curHt);            \
}

const size_t SZ_HASHTABLE = 97;
const size_t N_INSERTS    = 300 * SZ_HASHTABLE;

int main() {
    vector *hashtables = vector_new(0, sizeof(hashtable_t*));
    PUSH_NEW_HASHTABLE(SZ_HASHTABLE, SET_HASH_FN(hashConst));
    PUSH_NEW_HASHTABLE(SZ_HASHTABLE, SET_HASH_FN(hashFirstChar));
    PUSH_NEW_HASHTABLE(SZ_HASHTABLE, SET_HASH_FN(hashCharSum));
    PUSH_NEW_HASHTABLE(SZ_HASHTABLE, SET_HASH_FN(hashStrlen));
    PUSH_NEW_HASHTABLE(SZ_HASHTABLE, SET_HASH_FN(hashRoll));
    PUSH_NEW_HASHTABLE(SZ_HASHTABLE, SET_HASH_FN(hashPoly));

    char *allWords = nullptr;
    vector *wordsPtr = vector_new(0, sizeof(char*));
    readDataset("/home/ilya/code/ded/2sem/hashtable/data/AtlasShrugged.txt", allWords, wordsPtr);

    size_t nHashtables = vector_size(hashtables);
    size_t nWords = vector_size(wordsPtr);
    for (size_t htIdx = 0; htIdx < nHashtables; ++htIdx) {
        hashtable_t *curHt = nullptr;
        vector_get(hashtables, htIdx, &curHt);

        for (size_t wordIdx = 0; wordIdx < fmin(nWords, N_INSERTS); ++wordIdx) {
            char *curPtr = nullptr;
            vector_get(wordsPtr, wordIdx, &curPtr);

            htInsert(curHt, curPtr);
        }
        dumpListLengths("/home/ilya/code/ded/2sem/hashtable/data/dump.txt", curHt, htIdx == 0);
        
        htDelete(curHt);
    }

    vector_delete(wordsPtr);
    free(allWords);
    vector_delete(hashtables);

    return 0;
}
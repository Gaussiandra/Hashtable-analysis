#define SET_HASH_FN(name) (name), (#name)
#define PUSH_NEW_HASHTABLE(...) {               \
    hashtable_t *curHt = htCreate(__VA_ARGS__); \
    vector_push(hashtables, &curHt);            \
}

void readDataset(const char path[], char allWords[],
                   vector *wordsPtr,
                   const char delimiters[] = " \n!\"#$%&\'()*+,-./:;<=>?@[]^_`{|}~");
void dumpListLengths(const char path[], hashtable_t *ht, bool createNew);
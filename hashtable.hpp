#include <stdlib.h>

struct hashtable_t {
    size_t capacity;
    struct list **addrs;
    size_t (*hashFn) (const char*);
    char *name;
};

size_t hashPoly(const char *str);
size_t hashConst(const char *str);
size_t hashFirstChar(const char *str);
size_t hashCharSum(const char *str);
size_t hashStrlen(const char *str);
size_t hashRoll(const char *str);
struct hashtable_t *htCreate(size_t capacity, size_t (*hashFn) (const char*), const char name[]);
void htInsert(struct hashtable_t *ht, const char *value);
bool htErase(struct hashtable_t *ht, const char *value);
const char *htFind(struct hashtable_t *ht, const char *value);
void htDelete(struct hashtable_t *ht);
void htPrint(struct hashtable_t *ht);
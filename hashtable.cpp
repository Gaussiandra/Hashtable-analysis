#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "string_list.hpp"
#include "hashtable.hpp"

size_t hashPoly(const char *str) {
    assert(str);

    size_t ret = 0, strLen = strlen(str);
    for (size_t i = 0; i < strLen; i++) {
        ret *= 7;
        ret += (size_t) str[i];
    }
    return ret;
}

size_t hashConst(const char *str) {
    assert(str);

    return 1;
}

size_t hashFirstChar(const char *str) {
    assert(str);

    return (size_t) str[0];
}

size_t hashCharSum(const char *str) {
    assert(str);
    
    size_t ret = 0, strLen = strlen(str);
    for (size_t i = 0; i < strLen; ++i) {
        ret += (size_t) str[i];
    }

    return ret;
}

size_t hashStrlen(const char *str) {
    assert(str);

    return strlen(str);
}

size_t hashRoll(const char *str) {
    assert(str);
    
    size_t ret = (size_t) str[0];
    while (*str) {
        ret = ((ret << 1) + (ret >> 63)) ^ (size_t) *str;
        ++str;
    }

    return ret;
}

struct hashtable_t *htCreate(size_t capacity, size_t (*hashFn) (const char*), const char name[]) {
    struct hashtable_t *newHt = (struct hashtable_t*) calloc(1, sizeof(struct hashtable_t));
    newHt->capacity = capacity;
    newHt->addrs = (struct list**) calloc(newHt->capacity, sizeof(struct list*));
    newHt->hashFn = hashFn;

    newHt->name = (char*) calloc(strlen(name) + 1, sizeof(char));
    strcpy(newHt->name, name);

    return newHt;
}

void htInsert(struct hashtable_t *ht, const char *value) {
    assert(ht);
    assert(value);

    size_t idx = ht->hashFn(value) % ht->capacity;
    if (ht->addrs[idx]) {
        struct list *nodeToChange = list_find(ht->addrs[idx], value);
        if (nodeToChange) {
            nodeToChange->value = (char*) realloc(
                nodeToChange->value, (strlen(value) + 1) * sizeof(char));
            strcpy(nodeToChange->value, value);
        }
        else {
            list_insert(ht->addrs[idx], value);
        }
    }
    else {
        ht->addrs[idx] = list_new(value);
    }
}

bool htErase(struct hashtable_t *ht, const char *value) {
    assert(ht);
    assert(value);

    size_t idx = ht->hashFn(value) % ht->capacity;
    if (ht->addrs[idx]) {
        ht->addrs[idx] = list_erase(ht->addrs[idx], value);
        return true;
    }
    return false;
}

const char *htFind(struct hashtable_t *ht, const char *value) {
    assert(ht);
    assert(value);

    size_t idx = ht->hashFn(value) % ht->capacity;
    if (ht->addrs[idx]) {
        struct list *found = list_find(ht->addrs[idx], value);
        if (found) {
            return found->value;
        }
    }
    return NULL;
}

void htDelete(struct hashtable_t *ht) {
    assert(ht);
    
    for (size_t i = 0; i < ht->capacity; ++i) {
        if (ht->addrs[i]) {
            list_delete(ht->addrs[i]);
        }
    }
    free(ht->name);
    free(ht->addrs);
    free(ht);
}

void htPrint(struct hashtable_t *ht) {
    assert(ht);

    for (size_t i = 0; i < ht->capacity; ++i) {
        if (ht->addrs[i]) {
            printf("%zu: ", i);
            list_print(ht->addrs[i]);
        }
    }
}
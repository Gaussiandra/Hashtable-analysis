#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "string_list.hpp"

struct list *list_new(const char *value) {
    struct list *head = (struct list*) calloc(1, sizeof(struct list));

    head->value = (char*) calloc(strlen(value) + 1, sizeof(char));
    strcpy(head->value, value);

    head->next = NULL;

    return head;
}

struct list *list_insert(struct list *head, const char *value) {
    if (head == NULL) {
        return list_new(value);
    }
    
    struct list* curNode = head;
    while (curNode->next) {
        curNode = curNode->next;
    }
    curNode->next = list_new(value);
    return head;
}

struct list *list_find(struct list *head, const char *elem) {
    assert(head);

    while (strcmp(head->value, elem) && head->next) {
        head = head->next;
    }

    if (strcmp(head->value, elem) == 0) {
        return head;
    }
    return NULL;
}

void freeNode(struct list *node) {
    free(node->value);
    free(node);
}

struct list *list_erase(struct list *head, const char *elem) {
    assert(head);

    struct list* curNode = head;

    if (strcmp(head->value, elem) == 0) {
        curNode = head->next;
        freeNode(head);
        return curNode;
    }

    while (curNode->next && strcmp(curNode->next->value, elem)) {
        curNode = curNode->next;
    }
    if (curNode->next) {
        struct list* curNodeNext = curNode->next;
        curNode->next = curNode->next->next;
        freeNode(curNodeNext);
    } 

    return head;
}

struct list *list_delete(struct list *head) {
    assert(head);

    struct list *curNode = head;

    while (head->next) {
        curNode = head;
        head = head->next;
        freeNode(curNode);
    }
    freeNode(head);

    return NULL;
}

struct list *list_next(struct list *curr) {
    if (curr) {
        return curr->next;
    }
    return NULL;
}

size_t list_length_slow(struct list *head) {
    size_t len = 0;
    if (head) {
        len = 1;

        while (head->next) {
            head = head->next;
            ++len;
        }
    }

    return len;
}

void list_print(struct list const *head) {
    if (head) {
        printf("[");
        while (head->next)  {
            printf("%s, ", head->value);
            head = head->next;
        }
        printf("%s]\n", head->value);
    }
    else {
        printf("[]\n");
    }
}
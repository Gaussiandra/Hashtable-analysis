struct list {
    char *value;
    struct list *next;
};

struct list *list_new(const char *value);
struct list *list_insert(struct list *head, const char *value);
struct list *list_find(struct list *head, const char *elem);
void freeNode(struct list *node);
struct list *list_erase(struct list *head, const char *elem);
struct list *list_delete(struct list *head);
struct list *list_next(struct list *curr);
size_t list_length_slow(struct list *head);
void list_print(struct list const *head);
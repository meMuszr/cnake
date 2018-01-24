#include <stddef.h>
struct node
{
    struct node *next;
    void *data;
    struct node *prev;
} node;
struct linked_list
{
    struct node *head;
    struct node *tail;
    unsigned int length;
} linked_list;
struct linked_list linkedlist_init(struct node *head);
int linkedlist_get_length(struct linked_list *list);
void linkedlist_add_end(struct linked_list *list, struct node *newNode);
void linkedlist_add_beginning(struct linked_list *list, struct node *newNode);
void linkedlist_add_at(struct linked_list *list, struct node *newNode, unsigned int index);
void enumerate(struct linked_list *list, struct node nodes[], size_t arraySize);
void iterate(struct linked_list *list, void (*cb)(struct node *));
struct node *linkedlist_remove_head(struct linked_list *list);
struct node *linkedlist_remove_tail(struct linked_list *list);
struct node *linkedlist_remove_node_at(struct linked_list *list, unsigned int index);

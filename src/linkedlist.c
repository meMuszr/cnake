#include <stdlib.h>
#include <stdio.h>
#include "includes/linkedlist.h"
int hasNextNode(struct node *node)
{
    return node->next ? 1 : 0;
}
int linkedlist_get_length(struct linked_list *list)
{
    return list->length;
}
struct linked_list linkedlist_init(struct node *head)
{
    struct linked_list list = {
        .head = head,
        .tail = head,
        .length = 1};
    return list;
}
void linkedlist_add_end(struct linked_list *list, struct node *newNode)
{
    struct node *pCurrent = list->tail;
    pCurrent->next = newNode;
    newNode->prev = pCurrent;
    list->tail = newNode;
    list->length++;
}
void linkedlist_add_beginning(struct linked_list *list, struct node *newNode)
{
    struct node *pCurrent = list->head;
    pCurrent->prev = newNode;
    newNode->next = pCurrent;
    list->head = newNode;
    list->length++;
}
void linkedlist_add_at(struct linked_list *list, struct node *newNode, unsigned int index)
{
    struct node *pNode = list->head;
    struct node *pPrevNode = pNode;
    while (index-- > 0)
    {
        pPrevNode = pNode;
        pNode = pNode->next;
    }
    if (!pNode)
    {
        linkedlist_add_end(list, newNode);
        return;
    }
    else if (!pNode->prev)
    {
        linkedlist_add_beginning(list, newNode);
        return;
    }

    pPrevNode->next = newNode;
    pNode->prev = newNode;
    newNode->prev = pPrevNode;
    newNode->next = pNode;
    list->length++;
}

void iterate(struct linked_list *list, void (*cb)(struct node *))
{
    struct node *pNode = list->head;
    if (!cb)
        return;
    do
    {
        cb(pNode);
        pNode = pNode->next;
        // printf("Previous node: %p\nCurrent node:  %p\nNext node:     %p\n\n", pPrevNode->prev, pPrevNode, pNode);
    } while (pNode);
}
struct node *linkedlist_remove_head(struct linked_list *list)
{
    struct node *pHead = list->head, *newHead = pHead->next;
    if (!newHead)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        pHead->next = newHead->prev = NULL;
        list->head = newHead;
    }
    list->length--;
    return pHead;
}
struct node *linkedlist_remove_tail(struct linked_list *list)
{
    struct node *pTail = list->tail, *newTail = pTail->prev;
    if (!newTail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        pTail->prev = newTail->next = NULL;
        list->tail = newTail;
    }
    list->length--;
    return pTail;
}
void enumerate(struct linked_list *list, struct node nodes[], size_t arraySize)
{
    struct node *pNode = list->tail;
    while (arraySize > 0)
    {
        nodes[--arraySize] = *pNode;
        pNode = pNode->prev;
    }
}

struct node *linkedlist_remove_node_at(struct linked_list *list, unsigned int index)
{
    if (index == 0)
        return linkedlist_remove_head(list);
    else if (index == list->length - 1)
        return linkedlist_remove_tail(list);
    else
    {
        struct node *pNode = list->head;
        while (index--)
            pNode = pNode->next;
        struct node *pBefore = pNode->prev;
        struct node *pAfter = pNode->next;
        pBefore->next = pAfter;
        pAfter->prev = pBefore;
        pNode->next = NULL;
        pNode->prev = NULL;
        list->length--;
        return pNode;
    }
}
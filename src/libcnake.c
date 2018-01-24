#include <stdlib.h>
#include "includes/libcnake.h"
#include "includes/linkedlist.h"
struct coordinate create_coordinate(int x, int y)
{
    struct coordinate cord = {x = x, y = y};
    return cord;
}
struct node *create_coordinate_node(struct coordinate coord)
{
    struct node *pNode = malloc(sizeof(node));
    struct coordinate *pCoord = malloc(sizeof(coord));
    pCoord->x = coord.x;
    pCoord->y = coord.y;
    pNode->data = pCoord;
    pNode->next = NULL;
    pNode->prev = NULL;
    return pNode;
}

struct coordinate create_food_piece(struct coordinate *windowSize)
{
    return create_coordinate(rand() % windowSize->x, rand() % windowSize->y);
}
static int hit(struct coordinate *first, struct coordinate *second)
{
    return first->x == second->x && first->y == second->y;
}
static int snake_hit_wall(struct coordinate *head, struct coordinate *windowSize)
{
    return head->x == -1 || head->x == windowSize->x || head->y == -1 || head->y == windowSize->y;
}
static int snake_hit_self(struct linked_list *list)
{
    struct coordinate *coordHead = list->head->data;
    unsigned int length = linkedlist_get_length(list);
    struct node nodes[length];
    enumerate(list, nodes, length);
    struct coordinate coordSnake;
    for (int i = 3; i < length; i++)
    {
        coordSnake = *(struct coordinate *)nodes[i].data;
        if (hit(&coordSnake, coordHead))
            return 1;
    }
    return 0;
}
void free_snake(struct linked_list *list) {
    struct node *removed;
    while(linkedlist_get_length(list)) {
        removed = linkedlist_remove_head(list);
        free(removed->data);
        free(removed);
    }
}

enum gamestate move_snake(struct linked_list *list, struct coordinate *windowSize, struct coordinate *foodPiece, enum direction *prevDirection, enum direction newDirection)
{
    struct coordinate *snakeHead = list->head->data;
    struct coordinate originalHead = *snakeHead;
    enum direction prevDir = *prevDirection;
    if (newDirection == null)
        newDirection = prevDir;
    else if (!(prevDir + newDirection))
        newDirection = prevDir;
    else *prevDirection = newDirection;
    switch (newDirection)
    {
    case north:
        snakeHead->y--;
        break;
    case south:
        snakeHead->y++;
        break;
    case west:
        snakeHead->x--;
        break;
    case east:
        snakeHead->x++;
        break;
    }
    if (hit(snakeHead, foodPiece))
    {
        linkedlist_add_at(list, create_coordinate_node(create_coordinate(originalHead.x, originalHead.y)), 1);
        return makefood;
    }
    else if (list->length > 3 && snake_hit_self(list))
        return restart;
    else if (snake_hit_wall(snakeHead, windowSize))
        return restart;
    else
    {
        struct node *replacePiece = linkedlist_remove_tail(list);
        struct coordinate *replacePieceData = replacePiece->data;
        replacePieceData->x = originalHead.x;
        replacePieceData->y = originalHead.y;
        linkedlist_add_at(list, replacePiece, 1);
    }
    return playing;
}
struct linked_list init_snake(struct coordinate *windowSize)
{
    int x = windowSize->x / 2, y = windowSize->y / 2;
    struct linked_list list = linkedlist_init(create_coordinate_node(create_coordinate(x, y)));
    for (int i = 0; i < 2; i++)
        linkedlist_add_end(&list, create_coordinate_node(create_coordinate(x, y)));
    return list;
}
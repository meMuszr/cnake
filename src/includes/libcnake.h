#ifndef LIBCNAKE_H
#define LINCNAKE_H
#include "./linkedlist.h"
struct coordinate
{
    int x;
    int y;
} coordinate;
enum direction
{
    null = 0,
    north = 1,
    east = 2,
    south = -1,
    west = -2
};
struct game
{
    unsigned int score;
    struct coordinate foodPiece;
    enum direction direction;
    struct linked_list snake;

} game;
enum gamestate
{
    playing,
    makefood,
    restart
};
struct coordinate create_coordinate(int x, int y);
struct node *create_coordinate_node(struct coordinate coord);
struct coordinate create_food_piece(struct coordinate *windowSize);
void free_snake(struct linked_list *list);
void make_food(struct coordinate *foodPiece, struct coordinate *windowSize);
enum gamestate update(struct game *game, struct coordinate *windowSize, enum direction newDirection);
struct game init_game(struct coordinate *windowSize);
#endif
struct coordinate
{
    int x;
    int y;
} coordinate;
enum direction {
    null = 0,
    north = 1,
    east = 2,
    south = -1,
    west = -2
};
enum gamestate {
    playing,
    makefood,
    restart
};
struct linked_list *list;
struct coordinate create_coordinate(int x, int y);
struct node *create_coordinate_node(struct coordinate coord);
struct coordinate create_food_piece(struct coordinate *windowSize);
void free_snake(struct linked_list *list);
void make_food(struct coordinate *foodPiece, struct coordinate *windowSize);
enum gamestate move_snake(struct linked_list *list, struct coordinate *windowSize, int *score, struct coordinate *foodPiece,enum direction *prevDirection, enum direction newDirection);
struct linked_list init_snake(struct coordinate *windowSize);

#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include "includes/libcnake.h"
#include "includes/linkedlist.h"
void display(struct coordinate coord, const chtype ch)
{
    attron(COLOR_PAIR(2));
    mvaddch(coord.y, coord.x, ch);
}
void draw_snake(struct linked_list *list)
{
    int length = linkedlist_get_length(list);
    struct node snakeNodes[length];
    enumerate(list, snakeNodes, length);
    while (length > 0)
        display(*(struct coordinate *)snakeNodes[--length].data, ACS_BLOCK);
}
void draw_score(int score)
{
    int scoreLength = snprintf(NULL, 0, "%d", score) + 1;
    char *chScore = malloc(scoreLength);
    snprintf(chScore, scoreLength, "%d", score);
    attron(COLOR_PAIR(1));
    mvprintw(0, 0, chScore);
    free(chScore);
}
void SIGHandler(int sig)
{
    endwin();
    switch (sig)
    {
    case SIGINT:
        puts("Sad to see you go ~\n");
        exit(0);
    }
}
enum direction get_direction(int keyCode)
{
    switch (keyCode)
    {
    case KEY_UP:
        return north;
        break;
    case KEY_DOWN:
        return south;
    case KEY_LEFT:
        return west;
    case KEY_RIGHT:
        return east;
    default:
        return null;
    }
}
void init_ncurses(WINDOW **win, int *pY, int *pX)
{
    *win = initscr();
    keypad(*win, 1);
    nodelay(*win, true);
    curs_set(0);
    timeout(0);
    cbreak();
    noecho();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    int y = 0;
    int x = 0;
    getmaxyx(*win, y, x);
    *pY = y;
    *pX = x;
}
int main(void)
{
    signal(SIGINT, SIGHandler);
    srand(time(NULL));
    WINDOW *win = NULL;
    struct coordinate foodPiece, windowSize;
    struct coordinate *pFoodPiece = &foodPiece, *pWindowSize = &windowSize;
    init_ncurses(&win, &windowSize.y, &windowSize.x);
    struct linked_list snake = init_snake(&windowSize);
    struct linked_list *pSnake = &snake;
    make_food(pFoodPiece, pWindowSize);
    int ch = 0, score = 0;
    enum direction dir = east;
    while (true)
    {
        getmaxyx(win, windowSize.y, windowSize.x);
        erase();
        draw_snake(pSnake);
        display(foodPiece, ACS_LANTERN);
        draw_score(score);
        refresh();
        ch = getch();
        move_snake(pSnake, pWindowSize, &score, pFoodPiece, &dir, ch != 0 && ch != 1 ? get_direction(ch) : null);
        usleep(100000);
    }
    return 0;
}

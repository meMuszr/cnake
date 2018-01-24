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
int main(void)
{
    signal(SIGINT, SIGHandler);
    srand(time(NULL));
    WINDOW *win = initscr();
    keypad(win, 1);
    nodelay(win, true);
    start_color();
    curs_set(0);
    timeout(0);
    init_pair(1, COLOR_GREEN, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    cbreak();
    noecho();
    struct coordinate foodPiece, windowSize;
    getmaxyx(win, windowSize.y, windowSize.x);
    struct linked_list list = init_snake(&windowSize);
    int ch = 0;
    enum gamestate status = makefood;
    enum direction dir = east;
    while (true)
    {
        getmaxyx(win, windowSize.y, windowSize.x);
        erase();
        switch (status)
        {
        case makefood:
            foodPiece = create_food_piece(&windowSize);
            break;
        case restart:
            free_snake(&list);
            list = init_snake(&windowSize);
            break;
        }
        status = playing;
        draw_snake(&list);
        display(foodPiece, ACS_LANTERN);
        refresh();
        ch = getch();
        status = move_snake(&list, &windowSize, &foodPiece, &dir, ch != 0 && ch != 1 ? get_direction(ch) : null);
        usleep(100000);
    }

    return 0;
}

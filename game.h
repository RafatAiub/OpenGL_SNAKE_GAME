#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define up 1
#define down -1
#define right 2
#define left -2
#define MAX 69

void initGrid(int,int);
void drawGrid();
void drawSnake();
void drawFood();
void random(int&,int&);
void sound();
#endif // GAME_H_INCLUDED

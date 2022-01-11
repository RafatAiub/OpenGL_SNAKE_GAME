#include<windows.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<ctime>
#include<stdlib.h>
#include "game.h"
#include<MMSystem.h>
//The extern keyword tells the compiler that a variable is declared in another source module (outside of the current scope)
extern int score;
int gridX,gridY;
int snake_length = 5;
bool food=true;
int foodX,foodY;
short sDirection=right;//initially the snake is moving in the right direction
int posX[60]={20,20,20,20,20},posY[60]={20,19,18,17,16};
extern bool gameOver;
//just passing x and y values.........
void initGrid(int x,int y)
{
    gridX=x;
    gridY=y;

}
void unit(int,int);
void drawGrid()
{
 for(int x=0;x<gridX;x++)
 {
    for(int y=0;y<gridY;y++)
    {
        unit(x,y);
    }
 }
}

void unit(int x,int y)
{
    if(x==0 || y==0 || x==gridX-1 || y==gridX-1)
    {
        glLineWidth(3.0);
        glColor3f(1.0,0.0,0.0);
    }
    else{
        glLineWidth(1.0);
        glColor3f(1.0,0.0,1.0);
    }
//to draw continuous number of line
    glBegin(GL_LINE_LOOP);
           glVertex2f(x,y);
           glVertex2f(x+1,y);
           glVertex2f(x+1,y+1);
           glVertex2f(x,y+1);
    glEnd();

}
void drawFood()
{
   if(food)
    random(foodX,foodY);
   food=false;
   glColor3f(1.0,0.00,0.0);
   glRectf(foodX,foodY,foodX+1,foodY+1);
}
void drawSnake()
{

    for(int i=snake_length-1;i>0;i--)
    {
        posX[i]=posX[i-1];        //drawing initial views of snakes
        posY[i]=posY[i-1];
    }
    if(sDirection==up)            //movement of the snake
        posY[0]++;
    else if(sDirection==down)
        posY[0]--;
    else if(sDirection==right)
        posX[0]++;
    else if(sDirection==left)
        posX[0]--;
        for(int i=0;i<snake_length;i++)
        {
          if(i==0)
                glColor3f(0.0,1.0,0.0); //define head color
          else
            glColor3f(1.0,1.0,1.0);     //define body color
            glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);//draw per unit of body

        }
        //if the head touch the side line then  game is over
        if(posX[0]==0 ||  posX[0]==gridX-1 || posY[0]== 0 ||  posY[0]==gridY-1)
    {
         gameOver=true;
    }
    //else if the head touch his own body then also game is over
        for(int j=1;j<snake_length;j++)
     {
        if(posX[j]==posX[0] && posY[j]==posY[0])
            gameOver=true;
     }

     // collision of snake head with the food

        if(posX[0]==foodX && posY[0]==foodY)
            {//if the head touch the side line then then game is over
                //each successful bite the sound occur
                sndPlaySound("snakehit.wav",SND_ASYNC);
                score=score+10;
                snake_length++;
                if(snake_length>MAX)
                snake_length=MAX;
                food=true;
            }
}
void random(int &x,int &y)//confirm random position of foods
{
    int _maxX=gridX-2;
    int _maxY=gridY-2;

    int _min =1;
    srand(time(NULL));
    x=_min+rand()%(_maxX-_min);
    y=_min+rand()%(_maxY-_min);
}

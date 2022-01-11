#include<windows.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include"game.h"
#include<stdlib.h>
#define COLUMNS 40
#define ROWS 40
#define FPS 7
#include<MMSystem.h>
extern short sDirection;
bool gameOver=false;
void sound();
void sound_on();
int  score =0;
void timer_callback(int);
void display_callback();
void reshape_callback(int,int );
void keyboard_callback(int ,int ,int );
void init()
{
    //back ground of the gaming window here we use black
    glClearColor(0.0,0.0,0.0,1.0);
    initGrid(COLUMNS,ROWS);

}
int main(int argc,char ** argv)
{
    glutInit(&argc,argv);
    //creating gaming window
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600,600);
    glutCreateWindow("SNAKE");
    glutDisplayFunc(display_callback );
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0,timer_callback,0);
    glutSpecialFunc(keyboard_callback);
    init();
    glutMainLoop();
    return 0;
}
int index=0;
void display_callback()
{
    if(gameOver)
     {
         char _score[10];
         itoa(score,_score,10);//indicate score must be a 10 base integer
         char text[50]="Your score:";
         strcat(text,_score);//which concatenate the two string
         MessageBoxA(NULL,text,"GAME OVER",0);
         exit(0);

     }
      glClear(GL_COLOR_BUFFER_BIT);
      drawGrid();
      drawSnake();
      drawFood();
      //swap the buffer and draw next string on the buffer
      glutSwapBuffers();//it works on snake movement directly

}
//After reshape the width and the hight of the window
void reshape_callback(int w,int h)
{
    //sets the view port on the window
    //it gives the flexibility to resize the window
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);//change the matrix mode
    glLoadIdentity();
    //glOrtho(leftmost,rightmost,bottommost,topmost,z axes)
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);//here -1&1 is for depth
    glMatrixMode(GL_MODELVIEW);
}
void timer_callback(int)//it maintain the speed of the snake
{
    glutPostRedisplay();
    //if increase FPS value then the speed will increase else decrease
    glutTimerFunc(1000/FPS,timer_callback,0);
}

void keyboard_callback(int  key,int,int)
{
   switch(key)
   {
   case GLUT_KEY_UP:
    if(sDirection!=down)
    sDirection=up;
    break;
    case GLUT_KEY_DOWN:
    if(sDirection!=up)
    sDirection=down;
    break;
    case GLUT_KEY_RIGHT:
    if(sDirection!=left)
    sDirection=right;
    break;
    case GLUT_KEY_LEFT:
    if(sDirection!=right)
    sDirection=left;
    break;
    }
}

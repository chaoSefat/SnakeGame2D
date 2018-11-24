#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define MAX 60
#include <GL/gl.h>
#include <GL/glut.h>
//#include "game.h"
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define COLUMNS 40
#define ROWS 40
#define FPS 10

#endif
void initGrid(int,int);
void drawGrid();
void drawSnake();
void drawFood();
void random(int&,int&);

int gridX,gridY;
int snake_length = 5;
bool food = true;
short sDirection = RIGHT;
extern bool gameOver;
extern int score;

int posX[60]={20,20,20,20,20},posY[60]={20,19,18,17,16,15};
int foodX , foodY;

void initGrid(int x, int y){
    gridX=x;
    gridY=y;
}

void unit(int x,int y)
{

    if(x==0||y==0||x==gridX-1||y==gridY-1)
    {
        glLineWidth(3.0);
        glColor3f(1.0,0.0,0.0);
    }else
    {
        glLineWidth(1.0);
        glColor3f(1.0,1.0,1.0);
    }


    glBegin(GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
    glEnd();
}

void drawGrid()
{
    for(int x = 0 ; x<gridX;x++)
    {
        for(int y = 0 ; y < gridY; y++)
        {
            unit(x,y);
        }
    }
}

void random(int &x, int &y)
{
    int _maxX = gridX-2 ;
    int _maxY = gridY-2 ;
    int _min = 1 ;
    srand(time(NULL));
    x = _min + rand()% (_maxX-_min);
    y = _min + rand()% (_maxY-_min);

}

void drawFood()
{
    if(food)
        random(foodX,foodY);
    food = false;
    glColor3f(0.0,0.0,1.0);
    glRectf(foodX,foodY,foodX+1,foodY+1);
}


void drawSnake()
{
    for(int i = snake_length-1; i > 0; i--)
    {
        posX[i] = posX[i-1];
        posY[i] = posY[i-1];
    }
    if(sDirection==UP)
    {
        posY[0]++;
    }
    if(sDirection==DOWN)
    {
        posY[0]--;
    }if(sDirection==LEFT)
    {
        posX[0]--;
    }if(sDirection==RIGHT)
    {
        posX[0]++;
    }
    for(int i = 0 ; i < snake_length ; i++)
    {
        if(i == 0)
            {glColor3f(0.0,0.7,0.9);}
        else{glColor3f(1.0,0.1,0.5);
        }
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);
    }

    if(posX[0]==0||posX[0]==gridX-1||posY[0]==0||posY[0]==gridY-1)
    {
        gameOver = true;
    }
    for(int i = 1; i < snake_length-1; i++){
        if(posX[0]==posX[i]&&posY[0]==posY[i])
        {
            gameOver = true;
        }
    }
    if(posX[0]==foodX&&posY[0]==foodY){
        food=true;
        snake_length++;
        if(snake_length>MAX)
        {
            snake_length=MAX;
        }
        score++;
    }
}

extern short sDirection;
bool gameOver = false;

void timer_callback(int);
void display_callback();
void reshape_callback(int,int);
void keyboard_callback(int,int,int);
int score=0;

void init(){
    glClearColor(0.0,0.0,0.0,1.0);
    initGrid(COLUMNS,ROWS);

}

void display_callback(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawSnake();
    drawFood();
    glutSwapBuffers();
    if(gameOver)
    {
        char _score[10];
        itoa(score,_score,10);
        char text[50] = "Your score : ";
        strcat(text,_score);
        MessageBox(NULL,text,"GAME OVER!",0);
        exit(0);
    }
}

void reshape_callback(int w, int h){
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer_callback,0);
}

void keyboard_callback(int key,int,int)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(sDirection!=DOWN)
        {
            sDirection = UP;
        }
        break;
    case GLUT_KEY_DOWN:
        if(sDirection!=UP)
        {
            sDirection = DOWN;
        }
        break;
    case GLUT_KEY_RIGHT:
        if(sDirection!=LEFT)
        {
            sDirection = RIGHT;
        }
        break;
    case GLUT_KEY_LEFT:
        if(sDirection!=RIGHT)
        {
            sDirection = LEFT;
        }
        break;
    }
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    //glutInitWindowPosition();
    glutInitWindowSize(500,500);
    glutCreateWindow("snake");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0,timer_callback,0);
    glutSpecialFunc(keyboard_callback);
    init();
    glutMainLoop();
    return 0;
}


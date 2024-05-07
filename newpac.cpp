#include <GL/glut.h>
#include <math.h>
#include <cstring>
#include <cstdio>
#include "newpac.h"
#include <pthread.h>
#include <unistd.h>

#define COLUMNS 19
#define ROWS 22

pthread_t ghostThreads[4], gameEngineThread, uiThread; 

void* updateGhost(void* arg) 
{
    Ghost* ghost = (Ghost*)arg;
    while (1) 
    {
        moveGhost1(*ghost); 
        usleep(800000); 
    }
    return NULL;
}

void startGhostThreads() 
{
    pthread_create(&ghostThreads[0], NULL, updateGhost, (void*)&g1);
    pthread_create(&ghostThreads[1], NULL, updateGhost, (void*)&g2);
    pthread_create(&ghostThreads[2], NULL, updateGhost, (void*)&g3);
    pthread_create(&ghostThreads[3], NULL, updateGhost, (void*)&g4);
}

void stopGhostThreads() 
{
    for (int i = 0; i < 4; ++i) 
    {
        pthread_cancel(ghostThreads[i]);
    }
}

void updatePacman(int dummy) 
{
    movement(); 
    glutTimerFunc(200, updatePacman, 0);
}

void ui_function() 
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawPacdots();
    drawTitle();
    drawHomescreenghost();
    otherui();
    drawPacman();
    drawGhost();
    glutSwapBuffers();
}

void keyboard_callback(unsigned char key, int x, int y) 
{
    currentmove = key;
}

void* uifunc(void* arg) 
{
    while (1) 
    {
        ui_function(); 
        usleep(800000); 
    }
    return NULL;
}
void startuiThread()
{
    pthread_create(&uiThread, NULL, uifunc, NULL);
}
void stopuiThread()
{
    pthread_cancel(uiThread);
}

void* gameEngine(void* arg) 
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(1400, 800);
    glutCreateWindow("Pacman");

    glutDisplayFunc(ui_function);
    glutReshapeFunc(reshape_callback);//callback func in header file
    glutKeyboardFunc(keyboard_callback);
    
    glutTimerFunc(200, updatePacman, 0);
    
    init();
    startuiThread();
    startGhostThreads();

    glutMainLoop();

    stopGhostThreads();
    stopuiThread();
    return NULL;
}

void startGameEngineThread() 
{
    pthread_create(&gameEngineThread, NULL, gameEngine, NULL);
}

void stopGameEngineThread() 
{
    pthread_cancel(gameEngineThread);
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);

    startGameEngineThread();

    pthread_join(gameEngineThread, NULL);

    return 0;
}

#include <GL/glut.h>
#include <math.h>
#include <cstring>
#include <cstdio>
#include "newpac.h"
#include <pthread.h>

#define COLUMNS 19
#define ROWS 22

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex to synchronize access to OpenGL context

void* ui_function(void*)
{
    while (true) {
        pthread_mutex_lock(&mutex); // Lock the mutex

        glClear(GL_COLOR_BUFFER_BIT);
        drawGrid();
        glutSwapBuffers();

        pthread_mutex_unlock(&mutex); // Unlock the mutex
    }
    return NULL;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);    // initialise glut when program called
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(1400, 800);
    glutCreateWindow("Pacman");

    pthread_t ui_thread;
    pthread_create(&ui_thread, NULL, ui_function, NULL); // Create a thread for UI function

    glutDisplayFunc([]() {
        // Empty display function, as rendering will be done in the separate thread
    });

    glutReshapeFunc(reshape_callback);
    //glutKeyboardFunc(keyboard_callback);
    //init();

    //glutTimerFunc(100, update, 0); // start the movement update loop
    //^ too fast. sorta can maybe be used for ghost boost?

    //glutTimerFunc(200, updatePacman, 0);
    //glutTimerFunc(800, updateGhosts, 0);  

    glutMainLoop(); //window will be displayed + processing will start

    pthread_join(ui_thread, NULL); // Wait for the UI thread to finish
    return 0;
}


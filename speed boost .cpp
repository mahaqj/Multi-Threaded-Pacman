#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include <cstdio>
#include "newpac.h"
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;

#define COLUMNS 19
#define ROWS 22

pthread_t ghostThreads[4], gameEngineThread, uiThread, pacmanThread;
pthread_mutex_t coutmutex;
sem_t gameEngineSemaphore, pacmanSemaphore, ghostSemaphore;//new
sem_t speedBoostSemaphore;//new

const int FAST_DURATION_SECONDS = 5;//new
const int RESET_FAST_INTERVAL = 10;//new
const int NORMAL_SLEEP_DURATION = 555000;//new
const int BOOSTED_SLEEP_DURATION = 200000;//new

std::chrono::high_resolution_clock::time_point fastStartTime[4];//new
int completedSpeedBoosts = 0;//new
pthread_mutex_t boostCountMutex;//new

int calculateManhattanDistance(int x1, int y1, int x2, int y2)//new
{
    return abs(x1 - x2) + abs(y1 - y2);
}

void selectClosestFastGhosts() {//new
    g1.isFast = g2.isFast = g3.isFast = g4.isFast = false;

    struct GhostDistance {
        Ghost* ghost;
        int distance;
        int index;
    };

    GhostDistance ghostDistances[] = {//new
        {&g1, calculateManhattanDistance(g1.x, g1.y, pacmanX, pacmanY), 0},
        {&g2, calculateManhattanDistance(g2.x, g2.y, pacmanX, pacmanY), 1},
        {&g3, calculateManhattanDistance(g3.x, g3.y, pacmanX, pacmanY), 2},
        {&g4, calculateManhattanDistance(g4.x, g4.y, pacmanX, pacmanY), 3}
    };

    std::sort(ghostDistances, ghostDistances + 4, [](const GhostDistance& a, const GhostDistance& b) {
        return a.distance < b.distance;
    });

    ghostDistances[0].ghost->isFast = true;
    ghostDistances[1].ghost->isFast = true;

    pthread_mutex_lock(&coutmutex);
    cout << "---------closest ghost index selected----" << ghostDistances[0].index << endl;
    cout << "---------closest ghost index selected----" << ghostDistances[1].index << endl;
    pthread_mutex_unlock(&coutmutex);
}

void boostGhostSpeed(Ghost& ghost, int index) {//new
    pthread_mutex_lock(&coutmutex);
    cout << "---------------------------ghost getting speed BOOST--------------" << index << endl;
    pthread_mutex_unlock(&coutmutex);
    ghost.speedBoosted = true;
    fastStartTime[index] = std::chrono::high_resolution_clock::now();
}

void resetGhostSpeed(Ghost& ghost, int index) {//new
    pthread_mutex_lock(&coutmutex);
    cout << "---------------------------ghost ENDING speed BOOSt---------------" << index << endl;
    pthread_mutex_unlock(&coutmutex);
    ghost.speedBoosted = false;

    pthread_mutex_lock(&boostCountMutex);
    completedSpeedBoosts++;
    if (completedSpeedBoosts >= 2) {
        completedSpeedBoosts = 0;
        selectClosestFastGhosts();
        pthread_mutex_lock(&coutmutex);
        cout << "---------------------------Resetting FAST flags for all ghosts----------------" << endl;
        pthread_mutex_unlock(&coutmutex);
    }
    pthread_mutex_unlock(&boostCountMutex);
}

bool isFastDurationElapsed(int index) {//new
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - fastStartTime[index]);
    return elapsedTime.count() >= FAST_DURATION_SECONDS;
}

void* updateGhost(void* arg) {
    Ghost* ghost = (Ghost*)arg;//new
    int ghostIndex = -1;

    if (ghost == &g1) ghostIndex = 0;
    else if (ghost == &g2) ghostIndex = 1;
    else if (ghost == &g3) ghostIndex = 2;
    else if (ghost == &g4) ghostIndex = 3;

    while (1) {//new
        sem_wait(&ghostSemaphore);

        if (ghost->isFast && !ghost->speedBoosted) {
            pthread_mutex_lock(&coutmutex);
            cout << "---------------------------ghost WAITING for speed BOOST----------------" << ghostIndex << endl;
            pthread_mutex_unlock(&coutmutex);

            sem_wait(&speedBoostSemaphore);

            pthread_mutex_lock(&coutmutex);
            cout << "---------------------------ghost IN Critical section----------------" << ghostIndex << endl;
            pthread_mutex_unlock(&coutmutex);

            boostGhostSpeed(*ghost, ghostIndex);
        } else if (ghost->speedBoosted && isFastDurationElapsed(ghostIndex)) {
            resetGhostSpeed(*ghost, ghostIndex);
            sem_post(&speedBoostSemaphore);
        }

        switch (ghostIndex) {
            case 0: moveGhost1(*ghost); break;
            case 1: moveGhost2(*ghost); break;
            case 2: moveGhost3(*ghost); break;
            case 3: moveGhost4(*ghost); break;
        }

        glutPostRedisplay();

        if (ghost->speedBoosted) {//new
            usleep(BOOSTED_SLEEP_DURATION);
        } else {
            usleep(NORMAL_SLEEP_DURATION);
        }

        sem_post(&ghostSemaphore);
    }
    return NULL;
}

void* updatePacman(void* arg) {
    while (1) {
        sem_wait(&pacmanSemaphore);
        movement();
        sem_post(&pacmanSemaphore);
        usleep(99000);
    }
    return NULL;
}

void startGhostThreads() {
    srand(time(NULL));//new
    selectClosestFastGhosts();//new

    pthread_create(&ghostThreads[0], NULL, updateGhost, (void*)&g1);
    pthread_create(&ghostThreads[1], NULL, updateGhost, (void*)&g2);
    pthread_create(&ghostThreads[2], NULL, updateGhost, (void*)&g3);
    pthread_create(&ghostThreads[3], NULL, updateGhost, (void*)&g4);
}

void stopGhostThreads() {
    for (int i = 0; i < 4; ++i) {
        pthread_cancel(ghostThreads[i]);
    }
}

void startPacmanThread() {
    pthread_create(&pacmanThread, NULL, updatePacman, NULL);
}

void stopPacmanThread() {
    pthread_cancel(pacmanThread);
}

void keyboard_callback(unsigned char key, int x, int y) {
    currentmove = key;
}

void* uifunc(void* arg) {
    while (1) {
        ui_function();
        glutPostRedisplay();
        usleep(99000);
    }
    return NULL;
}

void startuiThread() {
    pthread_create(&uiThread, NULL, uifunc, NULL);
}

void stopuiThread() {
    pthread_cancel(uiThread);
}

void* gameEngine(void* arg) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(1400, 800);
    glutCreateWindow("Pacman");

    glutDisplayFunc(ui_function);
    glutReshapeFunc(reshape_callback);
    glutKeyboardFunc(keyboard_callback);

    init();
    startuiThread();
    startGhostThreads();
    startPacmanThread();

    glutMainLoop();

    stopGhostThreads();
    stopPacmanThread();
    stopuiThread();

    sem_post(&gameEngineSemaphore);
    return NULL;
}

void startGameEngineThread() {
    sem_init(&gameEngineSemaphore, 0, 0);//not sure new or not
    sem_init(&pacmanSemaphore, 0, 1);//new
    sem_init(&ghostSemaphore, 0, 4);//new
    sem_init(&speedBoostSemaphore, 0, 2);//new
    pthread_mutex_init(&boostCountMutex, NULL);//new
    pthread_create(&gameEngineThread, NULL, gameEngine, NULL);
}

void stopGameEngineThread() {
    pthread_cancel(gameEngineThread);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    startGameEngineThread();
    sem_wait(&gameEngineSemaphore);

    sem_destroy(&gameEngineSemaphore);//new
    sem_destroy(&pacmanSemaphore);//new
    sem_destroy(&ghostSemaphore);//new
    sem_destroy(&speedBoostSemaphore);//new
    pthread_mutex_destroy(&boostCountMutex);//new

    return 0;
}

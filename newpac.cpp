#include <GL/glut.h>
#include <math.h>
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
pthread_mutex_t mutex; 
sem_t gameEngineSemaphore, turnSemaphore; 
pthread_mutex_t coutmutex;

pthread_t pellet_respawn;

sem_t ghostSemaphore;//new
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

void* updateGhost(void* arg)
{
    Ghost* ghost = (Ghost*)arg;//new
    int ghostIndex = -1;

    if (ghost == &g1) ghostIndex = 0;
    else if (ghost == &g2) ghostIndex = 1;
    else if (ghost == &g3) ghostIndex = 2;
    else if (ghost == &g4) ghostIndex = 3;

    while (1)
    {
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

        sem_post(&ghostSemaphore); //yahan tak speed boost wala tha
    
    
        sem_wait(&turnSemaphore); // Wait for turn
        pthread_mutex_lock(&mutex); // Lock 
        pthread_mutex_lock(&coutmutex);
        cout << "ghost " << ghostIndex << endl;
        pthread_mutex_unlock(&coutmutex);
        if (ghost->x == g1.x && ghost->y == g1.y)
        {
            moveGhost1(*ghost); //glutPostRedisplay();
            if (g1.speedBoosted == 1)
            {
            	moveGhost1(*ghost);
            }
        }
        else if (ghost->x == g2.x && ghost->y == g2.y)
        {
            moveGhost2(*ghost); //glutPostRedisplay();
            if (g1.speedBoosted == 1)
            {
            	moveGhost1(*ghost);
            }
        }
        else if (ghost->x == g3.x && ghost->y == g3.y)
        {
            moveGhost3(*ghost); //glutPostRedisplay();
            if (g1.speedBoosted == 1)
            {
            	moveGhost1(*ghost);
            }
        }
        else if (ghost->x == g4.x && ghost->y == g4.y)
        {
            moveGhost4(*ghost); //glutPostRedisplay();
            if (g1.speedBoosted == 1)
            {
            	moveGhost1(*ghost);
            }
        }
        glutPostRedisplay();
        pthread_mutex_unlock(&mutex); // Unlock 
        sem_post(&turnSemaphore); // Release turn
        usleep(500000);
    }
    return NULL;
}

void* updatePacman(void* arg)
{
    while (1)
    {
        sem_wait(&turnSemaphore); // Wait for turn
        movement();
        //glutPostRedisplay();
        sem_post(&turnSemaphore); // Release turn
       // sem_post(&pacmanSemaphore); // Signal that Pacman movement is done
        usleep(100000);
    }
    return NULL;
}

void startGhostThreads()
{
    srand(time(NULL));//new
    selectClosestFastGhosts();//new
    
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

void startPacmanThread()
{
    pthread_create(&pacmanThread, NULL, updatePacman, NULL);
}

void stopPacmanThread()
{
    pthread_cancel(pacmanThread);
}

void keyboard_callback(unsigned char key, int x, int y)
{
    pthread_mutex_lock(&mutex); // Lock 
    pthread_mutex_lock(&coutmutex);
    cout << "pacman " << endl;
    pthread_mutex_unlock(&coutmutex);
    currentmove = key;
    pthread_mutex_unlock(&mutex); // Unlock
}

void* uifunc(void* arg)
{
    while (1)
    {
        ui_function();
        glutPostRedisplay();
        usleep(80000);
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

void* produce_pellet(void* arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);
		if (pelletmoves == 35)
		{
			pacdots[pellet_consumed_x][pellet_consumed_y] = 2;
		}
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void startPelletRespawn()
{
	pthread_create(&pellet_respawn, NULL, produce_pellet, NULL);
}

void stopPelletRespawn()
{
	pthread_cancel(pellet_respawn);
}

void* gameEngine(void* arg)
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(1400, 800);
    glutCreateWindow("Pacman");

    glutDisplayFunc(ui_function);
    glutReshapeFunc(reshape_callback); //callback func in header file
    glutKeyboardFunc(keyboard_callback);

    init();
    startuiThread();
    startGhostThreads();
    startPacmanThread();
    startPelletRespawn();

    glutMainLoop();

    stopPelletRespawn();
    stopGhostThreads();
    stopPacmanThread();
    stopuiThread();

    sem_post(&gameEngineSemaphore); // Release semaphore when game engine thread finishes
    return NULL;
}

void startGameEngineThread()
{
    sem_init(&gameEngineSemaphore, 0, 0); // Initialize semaphore
   // sem_init(&pacmanSemaphore, 0, 1); // Initialize pacman semaphore with 1 to allow movement at the beginning
   
    //sem_init(&pacmanSemaphore, 0, 1);//new
    sem_init(&ghostSemaphore, 0, 4);//new
    sem_init(&speedBoostSemaphore, 0, 2);//new
    pthread_mutex_init(&boostCountMutex, NULL);//new
   
    sem_init(&turnSemaphore, 0, 5); // Initialize turn semaphore with 5 to allow 5 turns initially
    pthread_create(&gameEngineThread, NULL, gameEngine, NULL);
}

void stopGameEngineThread()
{
    pthread_cancel(gameEngineThread);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
  
    pthread_mutex_init(&mutex, NULL); 

    startGameEngineThread();

    sem_wait(&gameEngineSemaphore); // Wait for game engine thread to finish

    pthread_mutex_destroy(&mutex);
    sem_destroy(&gameEngineSemaphore);
    //sem_destroy(&pacmanSemaphore);//new
    sem_destroy(&ghostSemaphore);//new
    sem_destroy(&speedBoostSemaphore);//new
    pthread_mutex_destroy(&boostCountMutex);//new
 //   sem_destroy(&pacmanSemaphore); 
    sem_destroy(&turnSemaphore); 

    return 0;
}

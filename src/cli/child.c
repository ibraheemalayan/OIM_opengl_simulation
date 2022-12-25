#include "local.h"

int randomIintegerInRange(int lower,int upper);
void childSensitiveSignals();
void signalCatcher_movingTimeForchangeIndexLocationForPersonInTheHostQueue(int the_sig);
void signalCatcher_movingTimeForchangeLocationForPersonFromQueueToAnotherQueue(int the_sig);

//Time for moving person insude the Queue in seconds
int minTimeForMovingPersonInsideHostQueue = 3;
int maxTimeForMovingPersonInsideHostQueue = 6;

//Time for moving person From Queue To Another Queue in seconds
int minTimeForMovingPersonFromQueueToAnotherQueue = 6;
int maxTimeForMovingPersonFromQueueToAnotherQueue = 9;

void main()
{
	childSensitiveSignals();
    while (1){
        //Pause until reseve signal from thread to move inside the host queue or
        //until reseve signal from thread to move from queue to anothr 
        pause(); 
    }
}

void childSensitiveSignals(){
    //every person should be sensitive to a signal from threads to update his location in the host queue
    if ( sigset(SIGUSR1, signalCatcher_movingTimeForchangeIndexLocationForPersonInTheHostQueue) == SIG_ERR ) {
    perror("Sigset can not set SIGUSR1");
    exit(SIGQUIT);
    }
    //every person should be sensitive to a signal from threads to change his location from queue to another queue
    if ( sigset(SIGUSR2, signalCatcher_movingTimeForchangeLocationForPersonFromQueueToAnotherQueue) == SIG_ERR ) {
    perror("Sigset can not set SIGUSR2");
    exit(SIGQUIT);
    }
}

void signalCatcher_movingTimeForchangeIndexLocationForPersonInTheHostQueue(int the_sig){
    int movingTime= randomIintegerInRange(minTimeForMovingPersonInsideHostQueue,maxTimeForMovingPersonInsideHostQueue);
    int i;
    //printf("\n\nProcess change his location in the host Queue\n\n");
    for(i=0;i<movingTime;i++){
        //movingTime
    }
}

void signalCatcher_movingTimeForchangeLocationForPersonFromQueueToAnotherQueue(int the_sig){
    int movingTime= randomIintegerInRange(minTimeForMovingPersonFromQueueToAnotherQueue,maxTimeForMovingPersonFromQueueToAnotherQueue);
    int i;
    //printf("\n\nProcess move From Queue To Another Queue\n\n");
    for(i=0;i<movingTime;i++){
        //movingTime
    }
}

int randomIintegerInRange(int lower,int upper)
{
	srand(time(NULL)); // randomize seed
	return (rand() % (upper - lower + 1)) + lower;

}

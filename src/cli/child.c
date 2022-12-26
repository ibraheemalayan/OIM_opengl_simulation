#include "local.h"

//............Functions..............
int randomIntegerInRange(int lower, int upper);
void childSensitiveSignals();
void signalCatcher_movingTimeForchangeIndexLocationForPersonInTheHostQueue(int the_sig);
void signalCatcher_movingTimeForchangeLocationForPersonFromQueueToAnotherQueue(int the_sig);
void printInfoForChildPerson(char *argv[]);

//..........Gloable Varibles...........
// Time for moving person insude the Queue in seconds
int minTimeForMovingPersonInsideHostQueue = 3;
int maxTimeForMovingPersonInsideHostQueue = 6;

// Time for moving person From Queue To Another Queue in seconds
int minTimeForMovingPersonFromQueueToAnotherQueue = 6;
int maxTimeForMovingPersonFromQueueToAnotherQueue = 9;

int ui_msgq_id;
int parent_msgq_id;

void setup_message_queue()
{

    key_t ui_q_key, parent_q_key;

    if ((ui_q_key = ftok("ui_queue.bin", 30)) == -1)
    {
        perror("ftok, queue not found");
        exit(1);
    }

    ui_msgq_id = msgget(ui_q_key, 0);
    if (ui_msgq_id == -1)
    {
        perror("msgget, error getting queue");
        exit(2);
    }

    if ((parent_q_key = ftok("children_queue.bin", 30)) == -1)
    {
        perror("ftok, queue not found");
        exit(1);
    }

    parent_msgq_id = msgget(parent_q_key, 0);
    if (ui_msgq_id == -1)
    {
        perror("msgget, error getting queue");
        exit(2);
    }
}

void main(int argc, char *argv[])
{
    printInfoForChildPerson(argv);
    childSensitiveSignals();
    setup_message_queue();

    while (1)
    {
        // Pause until reseve signal from thread to move inside the host queue or
        // until reseve signal from thread to move from queue to anothr
        pause();
    }
}

void childSensitiveSignals()
{
    // every person should be sensitive to a signal from threads to update his location in the host queue
    if (sigset(SIGUSR1, signalCatcher_movingTimeForchangeIndexLocationForPersonInTheHostQueue) == -1)
    {
        perror("Sigset can not set SIGUSR1");
        exit(SIGQUIT);
    }
    // every person should be sensitive to a signal from threads to change his location from queue to another queue
    if (sigset(SIGUSR2, signalCatcher_movingTimeForchangeLocationForPersonFromQueueToAnotherQueue) == -1)
    {
        perror("Sigset can not set SIGUSR2");
        exit(SIGQUIT);
    }
}

void signalCatcher_movingTimeForchangeIndexLocationForPersonInTheHostQueue(int the_sig)
{
    int movingTime = randomIntegerInRange(minTimeForMovingPersonInsideHostQueue, maxTimeForMovingPersonInsideHostQueue);
    int i;
    // printf("\n\nProcess change his location in the host Queue\n\n");
    // fflush(stdout);
    for (i = 0; i < movingTime; i++)
    {
        // movingTime
    }
}

void signalCatcher_movingTimeForchangeLocationForPersonFromQueueToAnotherQueue(int the_sig)
{
    int movingTime = randomIntegerInRange(minTimeForMovingPersonFromQueueToAnotherQueue, maxTimeForMovingPersonFromQueueToAnotherQueue);
    int i;
    // printf("\n\nProcess move From Queue To Another Queue\n\n");
    // fflush(stdout);
    for (i = 0; i < movingTime; i++)
    {
        // movingTime
    }
}

int randomIntegerInRange(int lower, int upper)
{
    srand(time(NULL)); // randomize seed
    return (rand() % (upper - lower + 1)) + lower;
}

void printInfoForChildPerson(char *argv[])
{
    printf("\n\nIn Child: Person %s ,Official Document Needed is %s, Gernder %s, timerForPatience %s,tiketNumberInGroupingArea %s, IndexOfTheProcessInsideTheHostQueue %s\n\n", argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
    fflush(stdout);
}
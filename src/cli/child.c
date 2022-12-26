#include "local.h"
#include "../include.h"

//............Functions..............
int randomIntegerInRange(int lower, int upper);
void childSensitiveSignals();
void signalCatcher_movingTimeForchangeIndexLocationForPersonInTheHostQueue(int the_sig);
void signalCatcher_movingTimeForchangeLocationForPersonFromQueueToAnotherQueue(int the_sig);
void printInfoForChildPerson(char *argv[]);
void setup_message_queue();

#define MAX_PATIENCE_TIME 1000
#define MIN_PATIENCE_TIME 100

int ui_msgq_id;
int parent_msgq_id;

int my_max_patience;
int waited_time = 0;

int index_in_queue; // index if inside a queue
Location current_location;
gender gen;
DocumentType doc_type;

void validate_args(int argc, char *argv[])
{
    if (argc != 4)
    {
        errno = EINVAL;
        red_stderr();
        printf("\nMust pass three arguments: gender, offical_document_needed, index, instead of %d", argc);
        reset_stderr();
        exit(-1);
    }

    // the first argument is -1 if last child
    if (!(gen = atoi(argv[1])) || (gen != Male && gen != Female))
    {
        errno = EINVAL;
        red_stdout();
        printf("\nThe first argument must be the gender which can be 1 or 2 not %s", argv[1]);
        fflush(stdout);
        reset_stdout();
        exit(-1);
    };

    doc_type = atoi(argv[2]);

    if (doc_type < 0 || doc_type > 3)
    {
        errno = EINVAL;
        red_stdout();
        printf("\nThe second argument must be the document type which can be in the range 0 and 3 instead of %s", argv[2]);
        fflush(stdout);
        reset_stdout();
        exit(-1);
    };

    if (!(index_in_queue = atoi(argv[3])))
    {
        errno = EINVAL;
        red_stdout();
        printf("\nThe third argument must be an integer, not %s", argv[3]);
        fflush(stdout);
        reset_stdout();
        exit(-1);
    };

    index_in_queue--;
}

void main(int argc, char *argv[])
{

    validate_args(argc, argv);

    my_max_patience = randomIntegerInRange(MIN_PATIENCE_TIME, MAX_PATIENCE_TIME);

    printInfoForChildPerson(argv);
    childSensitiveSignals();
    setup_message_queue();

    // while true
    // if there are index updates from parent, read them and tell ui
    // update patience
    // tell ui

    while (1)
    {
        // Pause until reseve signal from thread to move inside the host queue or
        // until reseve signal from thread to move from queue to anothr
        // pause();

        // parent_msgq_id
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

void signalCatcher_movingTimeForchangeIndexLocationForPersonInTheHostQueue(int the_sig)
{
    // int movingTime = randomIntegerInRange(minTimeForMovingPersonInsideHostQueue, maxTimeForMovingPersonInsideHostQueue);
    // int i;
    // // printf("\n\nProcess change his location in the host Queue\n\n");
    // // fflush(stdout);
    // for (i = 0; i < movingTime; i++)
    // {
    //     // movingTime
    // }
}

void signalCatcher_movingTimeForchangeLocationForPersonFromQueueToAnotherQueue(int the_sig)
{

    // int movingTime = randomIntegerInRange(minTimeForMovingPersonFromQueueToAnotherQueue, maxTimeForMovingPersonFromQueueToAnotherQueue);
    // int i;
    // // printf("\n\nProcess move From Queue To Another Queue\n\n");
    // // fflush(stdout);
    // for (i = 0; i < movingTime; i++)
    // {
    //     // movingTime
    // }
}

int randomIntegerInRange(int lower, int upper)
{
    srand(time(NULL)); // randomize seed
    return (rand() % (upper - lower + 1)) + lower;
}

void printInfoForChildPerson(char *argv[])
{
    printf(
        "person{pid:%d, gender:%d, index:%d, document:%d, patience:%d}\n", getpid(), gen, index_in_queue, doc_type, my_max_patience);
    fflush(stdout);
}
#include "local.h"
#include "../std.h"
#include "../include.h"

// TODOs
// 1. Fork & Exec UI
// 2. Rename symbols that has Typos
// 3. Color output & replace flush with reset_stdout

int ibraheem = -1;
//..........Fuctions........................
void readInputFile();
int randomIntegerInRange(int lower, int upper);
void printAccessQueues();
void printRollingGatesQueues();
void printInfoForArrivalPerson(struct personInformation person);
void start_simulation();
void displyGroupingAreaQueue();

// People creation
void creatPeople();

// Dequeue from Queues ->
struct personInformation dequeueNodeFromQueue(pthread_mutex_t *mutex, struct accessQueueNode **FrontQueue, int *numberOfPeopleInTheQueue);
void updateIndexOfQueue(struct accessQueueNode **FrontOfQueue);

// Enqueue To Queues ->
void enqueueToQueue(struct personInformation personInf, pthread_mutex_t *mutex, struct accessQueueNode **FrontQueue, struct accessQueueNode **RearQueue, int *numberOfPeopleInTheQueue);

// remove Node From Queue Because Of Impatience
void removeNodeFromQueueDueToImpatience(struct accessQueueNode **FrontQueue, pid_t personIDKey);

// Threads

// security officers threads
void insertToMalesRollingGateQueue();
void insertToFemalesRollingGateQueue();
void insertToFemalesMetalDetector();
void insertToMalesMetalDetector();
void insertToMetalDetectors();

// teller employees threads
void insertToTellersQueues();
void insertToBirthCertificatesTeller();
void insertToTravelDocumentsTeller();
void insertToFamilyReunionDocumentsTeller();
void insertToIDRelatedProblemsTeller();

//..........Gloable Variables................

// Number of Access people
int g_peopleUntil8am;
int g_peopleAfter8amUntil1pm;

// Gender Array
char g_gender[2] = {'F', 'M'};

// Pointers to The accessQueue for Males
struct accessQueueNode *FrontAccessQueueMales = NULL;
struct accessQueueNode *RearAccessQueueMales = NULL;

// Pointers to The accessQueue for Females
struct accessQueueNode *FrontAccessQueueFemales = NULL;
struct accessQueueNode *RearAccessQueueFemales = NULL;

// Pointers to the Queue of males path in the rolling gates
struct accessQueueNode *FrontRollingGateQueueMales = NULL;
struct accessQueueNode *RearRollingGateQueueMales = NULL;

// Pointers to the Queue of Females path in the rolling gates
struct accessQueueNode *FrontRollingGateQueueFemales = NULL;
struct accessQueueNode *RearRollingGateQueueFemales = NULL;

// Pointers to the grouping area Queue
struct accessQueueNode *FrontForGroupingAreaQueue = NULL;
struct accessQueueNode *RearForGroupingAreaQueue = NULL;

// Pointers to the birth certificates teller
struct accessQueueNode *FrontForBirthCertificatesTellerQueue = NULL;
struct accessQueueNode *RearForBirthCertificatesTellerQueue = NULL;

// Pointers to the travel documents teller
struct accessQueueNode *FrontForTravelDocumentsTellerQueue = NULL;
struct accessQueueNode *RearForTravelDocumentsTellerQueue = NULL;

// Pointers to the family reunion documents teller
struct accessQueueNode *FrontForFamilyReunionDocumentsTellerQueue = NULL;
struct accessQueueNode *RearForFamilyReunionDocumentsTellerQueue = NULL;

// Pointers to the ID-related problems  teller
struct accessQueueNode *FrontForIDRelatedProblemsTellerQueue = NULL;
struct accessQueueNode *RearForIDRelatedProblemsTellerQueue = NULL;

// Threshold
#define g_threshold 3

// shifting In arrival time
int minShiftingInArrivalTime = 1;
int maxShiftingInArrivalTime = 3;

// Number of Females and males in the Access queues
int g_numberOfMalesInAccessQueue = 0;
int g_numberOfFemalesInAccessQueue = 0;

// Number of Feamles and males in Rolling gate queue
int g_numberOfFemaelsInTheRollingGateQueue = 0;
int g_numberOfMaelsInTheRollingGateQueue = 0;

// Number of people in the grouping area
int g_numberOfpeopleInGroupingArea = 0;

// Number of people in the Birth Certificates Teller Queue
int g_numberOfpeopleInBirthCertificatesTellerQueue = 0;

// Number of people in the Travel Documents Teller Queue
int g_numberOfpeopleInTravelDocumentsTellerQueue = 0;

// Number of people in the Family Reunion Documents Teller Queue
int g_numberOfpeopleInFamilyReunionDocumentsTellerQueue = 0;

// Number of people in the ID Related Problems Teller Queue
int g_numberOfpeopleInIDRelatedProblemsTellerQueue = 0;

// Array of Official Document
char g_OfficialDocument[4][40] = {"Birth Certificates", "Travel Documents", "Family Reunion Documents", "ID-related Problems"};

// Array for status when leaving OIM either satisfied or unhappy
char g_leaving_OIM_Status[2][15] = {"Satisfied", "Unhappy"};

// Mutex on Queues
pthread_mutex_t malesAccessQueue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t femalesAccessQueue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t malesRollingGatQueue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t femalesRollingGatQueue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t groupingAreaQueue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t BirthCertificatesQueue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t TravelDocumentsQueue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t FamilyReunionDocumentsQueue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t IDRelatedProblemsQueue_mutex = PTHREAD_MUTEX_INITIALIZER;

// Index of the process inside the host Queue
// To pass it as argument when create the process
int IndexOfTheProcessInsideTheHostQueue = 0;

int main()
{
    start_simulation();
    return 0;
}

void start_simulation()
{
    printf("\n\n\n\n.......5:30 AM: People Start coming.......\n\n");
    fflush(stdout);

    // Read input file
    readInputFile();

    // Create the peocesses
    creatPeople();

    printf("\n\nIt's 8am:\n\n");
    fflush(stdout);

    sleep(randomIntegerInRange(3, 6)); // simulation for time delaying

    printAccessQueues();

    printf("\n\nNumber of People Arrive Untial 8am : %d \n\n", g_peopleUntil8am);
    fflush(stdout);

    // People Start Entering the Rolling Gate Dependent on their Gender
    sleep(randomIntegerInRange(3, 6)); // simulation for time delaying
    printf("\n\nPeople Start Entering the Rolling Gate Dependes on their Gender >>>>>>\n\n");

    /* create a new thread that will keep move nodes from males access queue to Rolling Gate Queue "Males" */
    pthread_t p_thread1;
    pthread_create(&p_thread1, NULL, (void *)insertToMalesRollingGateQueue, NULL);

    /* create a new thread that will keep move nodes from Females access queue to Rolling Gate Queue "Females" */
    pthread_t p_thread2;
    pthread_create(&p_thread2, NULL, (void *)insertToFemalesRollingGateQueue, NULL);

    /* create a new thread that will keep move nodes from Males and Females rolling gate queues to the metal detectors*/
    pthread_t p_thread3;
    pthread_create(&p_thread3, NULL, (void *)insertToMetalDetectors, NULL);

    /* create a new thread that will keep move nodes from  Grouping area queue to tellers Queues*/
    pthread_t p_thread4;
    pthread_create(&p_thread4, NULL, (void *)insertToTellersQueues, NULL);

    /* create a new thread that will keep move nodes from  Birth Certificates Teller Queue to the Birth Certificates Teller*/
    pthread_t p_thread5;
    pthread_create(&p_thread5, NULL, (void *)insertToBirthCertificatesTeller, NULL);

    /* create a new thread that will keep move nodes from  Travel Documents Teller Queue to the Travel Documents Teller*/
    pthread_t p_thread6;
    pthread_create(&p_thread6, NULL, (void *)insertToTravelDocumentsTeller, NULL);

    /* create a new thread that will keep move nodes from  Family Reunion Documents Teller Queue to the Family Reunion Documents Teller*/
    pthread_t p_thread7;
    pthread_create(&p_thread7, NULL, (void *)insertToFamilyReunionDocumentsTeller, NULL);

    /* create a new thread that will keep move nodes from  ID Related Problems Teller Queue to the ID Related Problems Teller*/
    pthread_t p_thread8;
    pthread_create(&p_thread8, NULL, (void *)insertToIDRelatedProblemsTeller, NULL);

    // printRollingGatesQueues();
    // printAccessQueues();
    // Number of Females and males
    // printf("g_numberOfMalesInAccessQueue: %d\n",g_numberOfMalesInAccessQueue);
    // printf("g_numberOfFemalesInAccessQueue: %d\n",g_numberOfFemalesInAccessQueue);
    // sleep(60);
    // printf("g_numberOfpeopleInGroupingArea :%d\n",g_numberOfpeopleInGroupingArea);
    // displyGroupingAreaQueue();

    pthread_join(p_thread1, NULL);
    pthread_join(p_thread2, NULL);
    pthread_join(p_thread3, NULL);
    pthread_join(p_thread4, NULL);
    pthread_join(p_thread5, NULL);
    pthread_join(p_thread6, NULL);
    pthread_join(p_thread7, NULL);
    pthread_join(p_thread8, NULL);
}

void readInputFile()
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("cli/inputfile.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int lineNumber = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        // printf("Retrieved line of length %zu:\n", read);

        lineNumber++;

        if (lineNumber == 1)
        { // read peopleUntil8am
            // printf("%s", line);

            // Splite the line
            char delim[] = " ";
            char *ptr = strtok(line, delim);

            ptr = strtok(NULL, delim);
            int l_range1 = atoi(ptr);

            ptr = strtok(NULL, delim);
            int l_range2 = atoi(ptr);

            // make a randome number of people within the range

            g_peopleUntil8am = randomIntegerInRange(l_range1, l_range2);
        }
    }

    fclose(fp);
}

int randomIntegerInRange(int lower, int upper)
{
    srand(time(NULL)); // randomize seed
    return (rand() % (upper - lower + 1)) + lower;
}

void enqueueToQueue(struct personInformation personInf, pthread_mutex_t *mutex, struct accessQueueNode **FrontQueue, struct accessQueueNode **RearQueue, int *numberOfPeopleInTheQueue)
{
    pthread_mutex_lock(mutex);
    struct personInformation person = personInf;
    struct accessQueueNode *ptr = (struct accessQueueNode *)malloc(sizeof(struct accessQueueNode));
    if (ptr == NULL)
    {
        printf("\nOVERFLOW \n");
        return;
    }
    else
    {
        person.indexLocationInTheHostQueue = (*numberOfPeopleInTheQueue); // update Index
        kill(person.personID, SIGUSR1);                                   // Signal the process to move inside the host Queue
        ptr->personInfo = person;
        if ((*FrontQueue) == NULL)
        {
            (*FrontQueue) = ptr;
            (*RearQueue) = ptr;
            (*FrontQueue)->nextPesron = NULL;
            (*RearQueue)->nextPesron = NULL;
        }
        else
        {
            (*RearQueue)->nextPesron = ptr;
            (*RearQueue) = ptr;
            (*RearQueue)->nextPesron = NULL;
        }
        sleep(randomIntegerInRange(3, 6)); // simulation for time delaying
        (*numberOfPeopleInTheQueue)++;
    }
    pthread_mutex_unlock(mutex);
}

struct personInformation dequeueNodeFromQueue(pthread_mutex_t *mutex, struct accessQueueNode **FrontQueue, int *numberOfPeopleInTheQueue)
{
    pthread_mutex_lock(mutex);
    struct accessQueueNode *temp = NULL;
    struct personInformation person = {0};
    person.indexLocationInTheHostQueue = -1; // update Index
    if ((*FrontQueue) == NULL)
    {
        printf("Underflow\n");
        return person;
    }
    else
    {
        temp = (*FrontQueue);
        person = temp->personInfo;
        person.indexLocationInTheHostQueue = -1; // update Index
        kill(person.personID, SIGUSR2);          // Signal to the process to move to the next Queue
        (*FrontQueue) = (*FrontQueue)->nextPesron;
        free(temp);
        (*numberOfPeopleInTheQueue)--;
    }
    pthread_mutex_unlock(mutex);
    return person;
}

void removeNodeFromQueueDueToImpatience(struct accessQueueNode **FrontQueue, pid_t personIDKey)
{

    // Store head node
    struct accessQueueNode *temp = *FrontQueue, *prev;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->personInfo.personID == personIDKey)
    {
        (*FrontQueue) = temp->nextPesron; // Changed head
        free(temp);                       // free old head
        return;
    }

    // Search for the personIDKey to be deleted, keep track of the
    // previous node as we need to change 'prev->nextPesron'
    while (temp != NULL && temp->personInfo.personID != personIDKey)
    {
        prev = temp;
        temp = temp->nextPesron;
    }

    // If personIDKey was not present in linked list
    if (temp == NULL)
        return;

    // Unlink the node from linked list
    prev->nextPesron = temp->nextPesron;

    free(temp); // Free memory
}

void updateIndexOfQueue(struct accessQueueNode **FrontOfQueue)
{
    struct accessQueueNode *tmp = *FrontOfQueue;
    while (tmp != NULL)
    {
        tmp->personInfo.indexLocationInTheHostQueue = tmp->personInfo.indexLocationInTheHostQueue - 1;
        kill(tmp->personInfo.personID, SIGUSR1); // Signal to the process to move inside the host Queue
        tmp = tmp->nextPesron;
    }
}

void displyGroupingAreaQueue()
{

    struct accessQueueNode *temp = NULL;
    if ((FrontForGroupingAreaQueue == NULL) && (RearForGroupingAreaQueue == NULL))
    {
        printf("\n\nMales Access Queue is Empty\n");
    }
    else
    {
        printf("\n\nThe Access queue for Males is :\n\n");
        temp = FrontForGroupingAreaQueue;
        while (temp)
        {
            printf("%d--%c--%d--%d\n", temp->personInfo.personID, temp->personInfo.gender, temp->personInfo.officialDocumentNeeded, temp->personInfo.timerForPatience);
            temp = temp->nextPesron;
        }
    }
}

void printAccessQueues()
{

    struct accessQueueNode *temp = NULL;
    if ((FrontAccessQueueMales == NULL) && (RearAccessQueueMales == NULL))
    {
        printf("\n\nMales Access Queue is Empty\n");
        fflush(stdout);
    }
    else
    {
        printf("\n\nThe Access queue for Males is :\n\n");
        temp = FrontAccessQueueMales;
        while (temp)
        {
            sleep(1); // simulation for time delaying
            printf("%d--%c--%d--%d\n", temp->personInfo.personID, temp->personInfo.gender, temp->personInfo.officialDocumentNeeded, temp->personInfo.timerForPatience);
            fflush(stdout);
            temp = temp->nextPesron;
        }
    }

    if ((FrontAccessQueueFemales == NULL) && (RearAccessQueueFemales == NULL))
    {
        printf("\n\nFemales Access Queue is Empty\n");
        fflush(stdout);
    }
    else
    {
        printf("\n\nThe Access queue for Females is :\n\n");
        temp = FrontAccessQueueFemales;
        while (temp)
        {
            sleep(1); // simulation for time delaying
            printf("%d--%c--%d--%d\n", temp->personInfo.personID, temp->personInfo.gender, temp->personInfo.officialDocumentNeeded, temp->personInfo.timerForPatience);
            fflush(stdout);
            temp = temp->nextPesron;
        }
    }
}

void printRollingGatesQueues()
{
    struct accessQueueNode *temp = NULL;
    if ((FrontRollingGateQueueMales == NULL) && (RearRollingGateQueueMales == NULL))
    {
        printf("\n\nMales Rolling Gate Queue is Empty\n");
    }
    else
    {
        printf("\n\nThe Rolling Gate Queue for Males is :\n\n");
        temp = FrontRollingGateQueueMales;
        while (temp)
        {
            printf("%d--%c--%d--%d\n", temp->personInfo.personID, temp->personInfo.gender, temp->personInfo.officialDocumentNeeded, temp->personInfo.timerForPatience);
            temp = temp->nextPesron;
        }
    }
    if ((FrontRollingGateQueueFemales == NULL) && (RearRollingGateQueueFemales == NULL))
    {
        printf("\n\nFemales Rolling Gate Queue is Empty\n");
    }
    else
    {
        printf("\n\nThe Rolling Gate Queue for Females is :\n\n");
        temp = FrontRollingGateQueueFemales;
        while (temp)
        {
            printf("%d--%c--%d--%d\n", temp->personInfo.personID, temp->personInfo.gender, temp->personInfo.officialDocumentNeeded, temp->personInfo.timerForPatience);
            temp = temp->nextPesron;
        }
    }
}

void creatPeople()
{

    int i, pid;
    struct personInformation person = {0};
    for (i = 0; i < g_peopleUntil8am; i++)
    {
        person.personID = 0;
        person.gender = g_gender[randomIntegerInRange(0, 1)];       // person.gender = g_gender[randomIntegerInRange(0,1)];
        person.officialDocumentNeeded = randomIntegerInRange(0, 3); // person.officialDocumentNeeded  = randomIntegerInRange(0,3);
        person.timerForPatience = randomIntegerInRange(20, 30);
        person.indexLocationInTheHostQueue = -1;
        person.tiketNumberInGroupingArea = -1;
        if (person.gender == 'M')
            IndexOfTheProcessInsideTheHostQueue = g_numberOfMalesInAccessQueue;
        else
            IndexOfTheProcessInsideTheHostQueue = g_numberOfFemalesInAccessQueue;
        pid = fork();
        if (pid == -1)
        {
            printf("fork failure\n");
            exit(-1);
        }
        else if (pid > 0)
        {
            // Print the info for the arrival person:
            person.personID = pid;
            printInfoForArrivalPerson(person);
            sleep(randomIntegerInRange(minShiftingInArrivalTime, maxShiftingInArrivalTime)); // simulation for time delaying for arrival time
            if (person.gender == 'M')
                enqueueToQueue(person, &malesAccessQueue_mutex, &FrontAccessQueueMales, &RearAccessQueueMales, &g_numberOfMalesInAccessQueue);
            else
                enqueueToQueue(person, &femalesAccessQueue_mutex, &FrontAccessQueueFemales, &RearAccessQueueFemales, &g_numberOfFemalesInAccessQueue);
        }
        else if (pid == 0)
        {

            // Passing argument
            char indexLocationInTheHostQueue[10];
            sprintf(indexLocationInTheHostQueue, "%d", IndexOfTheProcessInsideTheHostQueue);

            char pid[10];
            sprintf(pid, "%d", getpid());

            char officialDocumentNeeded[10];
            sprintf(officialDocumentNeeded, "%d", person.officialDocumentNeeded);

            char gender[2] = {person.gender, '\0'};

            char timerForPatience[10];
            sprintf(timerForPatience, "%d", person.timerForPatience);

            char tiketNumberInGroupingArea[10];
            sprintf(tiketNumberInGroupingArea, "%d", person.tiketNumberInGroupingArea);

            execlp("./bin/child.o", "child.o", pid, officialDocumentNeeded, gender, timerForPatience, tiketNumberInGroupingArea, indexLocationInTheHostQueue, "&", NULL);
            perror("\n> child: exec\n");
            exit(-2);
        }
    }
}

void insertToMalesRollingGateQueue()
{
    struct personInformation Person;
    while (1)
    {
        if (g_numberOfMaelsInTheRollingGateQueue < g_threshold && g_numberOfMalesInAccessQueue > 0)
        {

            sleep(randomIntegerInRange(3, 6)); // simulation for dealy time for  moving from Access queue to Rolling gate queue
            Person = dequeueNodeFromQueue(&malesAccessQueue_mutex, &FrontAccessQueueMales, &g_numberOfMalesInAccessQueue);
            enqueueToQueue(Person, &malesRollingGatQueue_mutex, &FrontRollingGateQueueMales, &RearRollingGateQueueMales, &g_numberOfMaelsInTheRollingGateQueue);
            updateIndexOfQueue(&FrontAccessQueueMales); // updateIndexOfQueue for AccessQueueMales
                                                        // printRollingGatesQueues();
                                                        // printAccessQueues();
        }
    }
}

void insertToFemalesRollingGateQueue()
{
    struct personInformation Person;
    while (1)
    {
        if (g_numberOfFemaelsInTheRollingGateQueue < g_threshold && g_numberOfFemalesInAccessQueue > 0)
        {
            sleep(randomIntegerInRange(3, 6)); // simulation for dealy time for  moving from Access queue to Rolling gate queue
            Person = dequeueNodeFromQueue(&femalesAccessQueue_mutex, &FrontAccessQueueFemales, &g_numberOfFemalesInAccessQueue);
            enqueueToQueue(Person, &femalesRollingGatQueue_mutex, &FrontRollingGateQueueFemales, &RearRollingGateQueueFemales, &g_numberOfFemaelsInTheRollingGateQueue);
            updateIndexOfQueue(&FrontAccessQueueFemales); // updateIndexOfQueue for AccessQueueFemales
            // printRollingGatesQueues();
            // printAccessQueues();
        }
    }
}

void insertToMalesMetalDetector()
{
    struct personInformation malePersonInMetalDetectorForMales;
    if (g_numberOfMaelsInTheRollingGateQueue > 0)
    {
        sleep(randomIntegerInRange(3, 6)); // simulation for delay

        malePersonInMetalDetectorForMales = dequeueNodeFromQueue(&malesRollingGatQueue_mutex, &FrontRollingGateQueueMales, &g_numberOfMaelsInTheRollingGateQueue);
        printf("\n\nPerson %d Enter the Metal Detector For Males, Gernder %c, Official Document Needed is %s\n\n", malePersonInMetalDetectorForMales.personID, malePersonInMetalDetectorForMales.gender, g_OfficialDocument[malePersonInMetalDetectorForMales.officialDocumentNeeded]);
        fflush(stdout);
        sleep(randomIntegerInRange(5, 8)); // simulation for delay in the Metal Detector as sleep between 5 to 8 seconds
        enqueueToQueue(malePersonInMetalDetectorForMales, &groupingAreaQueue_mutex, &FrontForGroupingAreaQueue, &RearForGroupingAreaQueue, &g_numberOfpeopleInGroupingArea);
        updateIndexOfQueue(&FrontRollingGateQueueMales); // updateIndexOfQueue for RollingGateQueueMales
                                                         // printf("Person %d leave the Metal Detector For Males and Enter the Grouping Area, Gernder %c, Official Document Needed is %s\n",malePersonInMetalDetectorForMales.personID, malePersonInMetalDetectorForMales.gender,g_OfficialDocument[malePersonInMetalDetectorForMales.officialDocumentNeeded]);
    }
}

void insertToFemalesMetalDetector()
{
    struct personInformation femalePersonInMetalDetectorForMales;
    if (g_numberOfFemaelsInTheRollingGateQueue > 0)
    {
        sleep(randomIntegerInRange(3, 6)); // simulation for delay

        femalePersonInMetalDetectorForMales = dequeueNodeFromQueue(&femalesRollingGatQueue_mutex, &FrontRollingGateQueueFemales, &g_numberOfFemaelsInTheRollingGateQueue);
        printf("\n\nPerson %d Enter the Metal Detector For Females, Gernder %c, Official Document Needed is %s\n\n", femalePersonInMetalDetectorForMales.personID, femalePersonInMetalDetectorForMales.gender, g_OfficialDocument[femalePersonInMetalDetectorForMales.officialDocumentNeeded]);
        fflush(stdout);
        sleep(randomIntegerInRange(5, 8)); // simulation for delay in the Metal Detector as sleep between 5 to 8 seconds
        enqueueToQueue(femalePersonInMetalDetectorForMales, &groupingAreaQueue_mutex, &FrontForGroupingAreaQueue, &RearForGroupingAreaQueue, &g_numberOfpeopleInGroupingArea);
        updateIndexOfQueue(&FrontRollingGateQueueFemales); // updateIndexOfQueue for RollingGateQueueFemales
                                                           // printf("Person %d leave the Metal Detector For Males and Enter the Grouping Area, Gernder %c, Official Document Needed is %s\n",malePersonInMetalDetectorForMales.personID, malePersonInMetalDetectorForMales.gender,g_OfficialDocument[malePersonInMetalDetectorForMales.officialDocumentNeeded]);
                                                           // fflush(stdout);
    }
}

void insertToMetalDetectors()
{

    int randomChoicFromRollingGates;
    int ToMalesMetalDetector = 0;
    int ToFemalesMetalDetector = 1;
    while (1)
    {
        randomChoicFromRollingGates = randomIntegerInRange(ToMalesMetalDetector, ToFemalesMetalDetector);
        if (randomChoicFromRollingGates == 0)
            insertToMalesMetalDetector();
        else
            insertToFemalesMetalDetector();
    }
}

void insertToTellersQueues()
{

    struct personInformation Person;
    while (1)
    {
        if (g_numberOfpeopleInGroupingArea > 0)
        {
            sleep(randomIntegerInRange(3, 6)); // simulation for delay
            Person = dequeueNodeFromQueue(&groupingAreaQueue_mutex, &FrontForGroupingAreaQueue, &g_numberOfpeopleInGroupingArea);
            printf("\n\nPerson %d leave the Grouping Area Queue, Gernder %c, Official Document Needed is %s\n\n", Person.personID, Person.gender, g_OfficialDocument[Person.officialDocumentNeeded]);
            fflush(stdout);
            sleep(randomIntegerInRange(4, 7)); // simulation for delaying while moving to Tellers Queuesas sleep between 5 to 8 seconds
            if (Person.officialDocumentNeeded == 0)
                enqueueToQueue(Person, &BirthCertificatesQueue_mutex, &FrontForBirthCertificatesTellerQueue, &RearForBirthCertificatesTellerQueue, &g_numberOfpeopleInBirthCertificatesTellerQueue);
            else if (Person.officialDocumentNeeded == 1)
                enqueueToQueue(Person, &TravelDocumentsQueue_mutex, &FrontForTravelDocumentsTellerQueue, &RearForTravelDocumentsTellerQueue, &g_numberOfpeopleInTravelDocumentsTellerQueue);
            else if (Person.officialDocumentNeeded == 2)
                enqueueToQueue(Person, &FamilyReunionDocumentsQueue_mutex, &FrontForFamilyReunionDocumentsTellerQueue, &RearForFamilyReunionDocumentsTellerQueue, &g_numberOfpeopleInFamilyReunionDocumentsTellerQueue);
            else if (Person.officialDocumentNeeded == 3)
                enqueueToQueue(Person, &IDRelatedProblemsQueue_mutex, &FrontForIDRelatedProblemsTellerQueue, &RearForIDRelatedProblemsTellerQueue, &g_numberOfpeopleInIDRelatedProblemsTellerQueue);

            updateIndexOfQueue(&FrontForGroupingAreaQueue); // updateIndexOfQueue for GroupingAreaQueue
        }
    }
}

void insertToBirthCertificatesTeller()
{

    struct personInformation Person;
    int leaving_OIM_Status; // 0:Satisfied ,  1:Unhappy
    while (1)
    {
        if (g_numberOfpeopleInBirthCertificatesTellerQueue > 0)
        {
            // sleep(randomIntegerInRange(3,6));//simulation for delay
            Person = dequeueNodeFromQueue(&BirthCertificatesQueue_mutex, &FrontForBirthCertificatesTellerQueue, &g_numberOfpeopleInBirthCertificatesTellerQueue);
            printf("\n\nPerson %d achieve the Birth Certificates Teller, Gernder %c, Official Document Needed is %s\n\n", Person.personID, Person.gender, g_OfficialDocument[Person.officialDocumentNeeded]);
            fflush(stdout);
            sleep(randomIntegerInRange(10, 15));             // simulation for delay in the Birth Certificates Teller as sleep between 10 to 15 seconds
            leaving_OIM_Status = randomIntegerInRange(0, 1); // 0:Satisfied ,  1:Unhappy
            printf("Person %d leave the Birth Certificates Teller, Gernder %c, Official Document Needed is %s, leaving OIM Status :%s\n", Person.personID, Person.gender, g_OfficialDocument[Person.officialDocumentNeeded], g_leaving_OIM_Status[leaving_OIM_Status]);
            fflush(stdout);
            updateIndexOfQueue(&FrontForBirthCertificatesTellerQueue); // updateIndexOfQueue for BirthCertificatesTellerQueue
        }
    }
}

void insertToTravelDocumentsTeller()
{

    struct personInformation Person;
    int leaving_OIM_Status; // 0:Satisfied ,  1:Unhappy
    while (1)
    {
        if (g_numberOfpeopleInTravelDocumentsTellerQueue > 0)
        {
            // sleep(randomIntegerInRange(3,6));//simulation for delay
            Person = dequeueNodeFromQueue(&TravelDocumentsQueue_mutex, &FrontForTravelDocumentsTellerQueue, &g_numberOfpeopleInTravelDocumentsTellerQueue);
            printf("\n\nPerson %d achieve the Travel Documents Teller, Gernder %c, Official Document Needed is %s\n\n", Person.personID, Person.gender, g_OfficialDocument[Person.officialDocumentNeeded]);
            fflush(stdout);
            sleep(randomIntegerInRange(10, 15));             // simulation for delay in the Travel Documents Teller as sleep between 10 to 15 seconds
            leaving_OIM_Status = randomIntegerInRange(0, 1); // 0:Satisfied ,  1:Unhappy
            printf("Person %d leave the Travel Documents Teller, Gernder %c, Official Document Needed is %s, leaving OIM Status :%s\n", Person.personID, Person.gender, g_OfficialDocument[Person.officialDocumentNeeded], g_leaving_OIM_Status[leaving_OIM_Status]);
            fflush(stdout);
            updateIndexOfQueue(&FrontForTravelDocumentsTellerQueue); // updateIndexOfQueue for TravelDocumentsTellerQueue
        }
    }
}

void insertToFamilyReunionDocumentsTeller()
{

    struct personInformation Person;
    int leaving_OIM_Status; // 0:Satisfied ,  1:Unhappy
    while (1)
    {
        if (g_numberOfpeopleInFamilyReunionDocumentsTellerQueue > 0)
        {
            // sleep(randomIntegerInRange(3,6));//simulation for delay
            Person = dequeueNodeFromQueue(&FamilyReunionDocumentsQueue_mutex, &FrontForFamilyReunionDocumentsTellerQueue, &g_numberOfpeopleInFamilyReunionDocumentsTellerQueue);
            printf("\n\nPerson %d achieve the Family Reunion Documents Teller, Gernder %c, Official Document Needed is %s\n\n", Person.personID, Person.gender, g_OfficialDocument[Person.officialDocumentNeeded]);
            fflush(stdout);
            sleep(randomIntegerInRange(10, 15));             // simulation for delay in the Family Reunion Documents Teller as sleep between 10 to 15 seconds
            leaving_OIM_Status = randomIntegerInRange(0, 1); // 0:Satisfied ,  1:Unhappy
            printf("Person %d leave the Family Reunion Documents Teller, Gernder %c, Official Document Needed is %s, leaving OIM Status :%s\n", Person.personID, Person.gender, g_OfficialDocument[Person.officialDocumentNeeded], g_leaving_OIM_Status[leaving_OIM_Status]);
            fflush(stdout);
            updateIndexOfQueue(&FrontForFamilyReunionDocumentsTellerQueue); // updateIndexOfQueue for FamilyReunionDocumentsTellerQueue
        }
    }
}

void insertToIDRelatedProblemsTeller()
{

    struct personInformation Person;
    int leaving_OIM_Status; // 0:Satisfied ,  1:Unhappy
    while (1)
    {
        if (g_numberOfpeopleInIDRelatedProblemsTellerQueue > 0)
        {
            // sleep(randomIntegerInRange(3,6));//simulation for delay
            Person = dequeueNodeFromQueue(&IDRelatedProblemsQueue_mutex, &FrontForIDRelatedProblemsTellerQueue, &g_numberOfpeopleInIDRelatedProblemsTellerQueue);
            printf("\n\nPerson %d achieve the ID Related Problems Teller, Gernder %c, Official Document Needed is %s\n\n", Person.personID, Person.gender, g_OfficialDocument[Person.officialDocumentNeeded]);
            fflush(stdout);
            sleep(randomIntegerInRange(10, 15));             // simulation for delay in the ID Related Problems Teller as sleep between 10 to 15 seconds
            leaving_OIM_Status = randomIntegerInRange(0, 1); // 0:Satisfied ,  1:Unhappy
            printf("Person %d leave the ID Related Problems Teller, Gernder %c, Official Document Needed is %s, leaving OIM Status :%s\n", Person.personID, Person.gender, g_OfficialDocument[Person.officialDocumentNeeded], g_leaving_OIM_Status[leaving_OIM_Status]);
            fflush(stdout);
            updateIndexOfQueue(&FrontForIDRelatedProblemsTellerQueue); // updateIndexOfQueue for IDRelatedProblemsTellerQueue
        }
    }
}

void printInfoForArrivalPerson(struct personInformation person)
{
    printf("\n\nPerson %d arrived, Gernder %c, Official Document Needed is %s\n\n", person.personID, person.gender, g_OfficialDocument[person.officialDocumentNeeded]);
    fflush(stdout);
}
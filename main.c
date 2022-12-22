#include "local.h"


//..........Fuctions........................

void readInputFile();
int randomIintegerInRange(int lower,int upper);

void enqueueToAccessQueues(pid_t personID, char gender, int officialDocumentNeeded, float timerForPatience);
struct personInformation dequeueNodeFromMalesAccessQueue();
struct personInformation dequeueNodeFromFemalesAccessQueue();

void enqueueToRollingGateQueueFemales();
void enqueueToRollingGateQueueMales();
struct personInformation dequeueNodeFromRollingGateQueueMales();
struct personInformation dequeueNodeFromRollingGateQueueFemales();


void creatPeople();
void displyAccessQueues();
void displyRollingGatesQueues();

void printInfoForArrivalPerson(pid_t personID, char gender, int officialDocumentNeeded);
void simulation();

void insertToMalesRollingGateQueue();
void insertToFemalesRollingGateQueue();

void insertToFemalesMetalDetector();
void insertToMalesMetalDetector();

void enqueueToGroupingAreaQueue(struct personInformation personInf);

void displyGroupingAreaQueue();


//..........Gloable Variables................

//Number of Access people
int g_peopleUntil8am;
int g_peopleAfter8amUntil1pm;

//Gender Array
char g_gender[2]={'F','M'};

//Pointers to The accessQueue for Males
struct accessQueueNode * FrontAccessQueueMales = NULL;
struct accessQueueNode * RearAccessQueueMales = NULL;

//Pointers to The accessQueue for Females
struct accessQueueNode * FrontAccessQueueFemales = NULL;
struct accessQueueNode * RearAccessQueueFemales = NULL;



//Pointers to the Queue of males path in the rolling gates
struct accessQueueNode * FrontRollingGateQueueMales = NULL;
struct accessQueueNode * RearRollingGateQueueMales = NULL;

//Pointers to the Queue of Females path in the rolling gates
struct accessQueueNode * FrontRollingGateQueueFemales = NULL;
struct accessQueueNode * RearRollingGateQueueFemales = NULL;

//Pointers to the grouping area Queue
struct accessQueueNode * FrontForGroupingAreaQueue = NULL;
struct accessQueueNode * RearForGroupingAreaQueue = NULL;



//Threshold
#define g_threshold 3

//shifting In arrival time
int minShiftingInArrivalTime = 4;
int maxShiftingInArrivalTime = 6;

//Number of Females and males in the Access queues
int g_numberOfMalesInAccessQueue = 0;
int g_numberOfFemalesInAccessQueue = 0;


//Number of Feamles and males in Rolling gate queue
int g_numberOfFemaelsInTheRollingGateQueue=0;
int g_numberOfMaelsInTheRollingGateQueue=0;

//Number of people in the grouping area
int g_numberOfpeopleInGroupingArea =0;

//Array of Official Document
char g_OfficialDocument[4][40] ={"Birth Certificates","Travel Documents","Family Reunion Documents","ID-related Problems"};

int main()
{
        simulation();
        return 0;
}

void simulation(){

        printf("\n\n.......5 AM: People Start coming.......\n\n");
        fflush(stdout);

        //Read input file
        readInputFile();

        //Create the peocesses
        creatPeople();

        printf("\n\nIt's 8am:\n\n");
        fflush(stdout);

        sleep(randomIintegerInRange(3,6));//simulation for time delaying


        displyAccessQueues();

        printf("\n\nNumber of People Arrive Untial 8am : %d \n\n",g_peopleUntil8am);
        fflush(stdout);




        //People Start Entering the Rolling Gate Dependent on their Gender
        sleep(randomIintegerInRange(3,6));//simulation for time delaying
        printf("\n\nPeople Start Entering the Rolling Gate Dependes on their Gender >>>>>>\n\n");
        fflush(stdout);
        sleep(randomIintegerInRange(3,6));//simulation for time delaying


        /* create a new thread that will keep move nodes from males access queue to Rolling Gate Queue "Males" */
        pthread_t p_thread1;
        pthread_create(&p_thread1, NULL, insertToMalesRollingGateQueue, NULL);


        /* create a new thread that will keep move nodes from Females access queue to Rolling Gate Queue "Females" */
        pthread_t p_thread2;
        pthread_create(&p_thread2, NULL, insertToFemalesRollingGateQueue, NULL);

        /* create a new thread that will keep move nodes from Males rolling gate queue to the Males metal detector*/
        pthread_t p_thread3;
        pthread_create(&p_thread3, NULL, insertToMalesMetalDetector, NULL);

        /* create a new thread that will keep move nodes from  Females rolling gate queue to the  Females metal detector*/
        pthread_t p_thread4;
        pthread_create(&p_thread4, NULL, insertToFemalesMetalDetector,  NULL);



        //enqueueToRollingGateQueueFemales();
        //enqueueToRollingGateQueueFemales();
        //enqueueToRollingGateQueueMales();
        //enqueueToRollingGateQueueMales();

        //displyRollingGatesQueues();


        //displyAccessQueues();

        //Number of Females and males
        //printf("g_numberOfMalesInAccessQueue: %d\n",g_numberOfMalesInAccessQueue);
        //printf("g_numberOfFemalesInAccessQueue: %d\n",g_numberOfFemalesInAccessQueue);

        //sleep(60);
        //printf("g_numberOfpeopleInGroupingArea :%d\n",g_numberOfpeopleInGroupingArea);
        //displyGroupingAreaQueue();

        pthread_join(p_thread1, NULL);
        pthread_join(p_thread2, NULL);
        pthread_join(p_thread3, NULL);
        pthread_join(p_thread4, NULL);
}

void readInputFile(){
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

        fp = fopen("inputfile.txt", "r");
        if (fp == NULL)
                exit(EXIT_FAILURE);
        int lineNumber = 0;
        while ((read = getline(&line, &len, fp)) != -1) {
                //printf("Retrieved line of length %zu:\n", read);

                lineNumber++;

                if (lineNumber == 1){ // read peopleUntil8am
                        //printf("%s", line);

                        //Splite the line
                        char delim[] = " ";
                        char *ptr = strtok(line, delim);

                        ptr = strtok(NULL, delim);
                        int l_range1= atoi(ptr);

                        ptr = strtok(NULL, delim);
                        int l_range2= atoi(ptr);

                        //make a randome number of people wiht in the range

                        g_peopleUntil8am = randomIintegerInRange(l_range1,l_range2);
                }
        }

        fclose(fp);
}

int randomIintegerInRange(int lower,int upper)
{
        srand(time(NULL)); // randomize seed
        return (rand() % (upper - lower + 1)) + lower;

}


void enqueueToRollingGateQueueMales(){
        struct personInformation person = dequeueNodeFromMalesAccessQueue();

        struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL ) {
        printf("\nOVERFLOW\n");
        return;
        } else {

                ptr->personInfo=person;
                //printf("Person %d Enter Males Rolling Gate Queue, Official Document Needed is \n", ptr->personInfo.personID);
                fflush(stdout);
                if (FrontRollingGateQueueMales == NULL) {
                FrontRollingGateQueueMales = ptr;
                RearRollingGateQueueMales = ptr;
                FrontRollingGateQueueMales->nextPesron = NULL;
                RearRollingGateQueueMales->nextPesron = NULL;
                } else {
                RearRollingGateQueueMales->nextPesron = ptr;
                RearRollingGateQueueMales = ptr;
                RearRollingGateQueueMales->nextPesron = NULL;
                }
                sleep(randomIintegerInRange(3,6));//simulation for time delaying
                g_numberOfMaelsInTheRollingGateQueue++;
                printf("\n\nPerson %d Enter Males Rolling Gate Queue, Official Document Needed is %s\n\n",person.personID,g_OfficialDocument[person.officialDocumentNeeded]);
                fflush(stdout);
        }

}

void enqueueToRollingGateQueueFemales(){
        struct personInformation person = dequeueNodeFromFemalesAccessQueue();

        struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL) {
        printf("\nOVERFLOW\n");
        return;
        } else {
                ptr->personInfo=person;
                if (FrontRollingGateQueueFemales == NULL) {
                FrontRollingGateQueueFemales = ptr;
                RearRollingGateQueueFemales = ptr;
                FrontRollingGateQueueFemales->nextPesron = NULL;
                RearRollingGateQueueFemales->nextPesron = NULL;
                } else {
                RearRollingGateQueueFemales->nextPesron = ptr;
                RearRollingGateQueueFemales = ptr;
                RearRollingGateQueueFemales->nextPesron = NULL;
                }
                sleep(randomIintegerInRange(3,6));//simulation for time delaying
                g_numberOfFemaelsInTheRollingGateQueue++;
                printf("\n\nPerson %d Enter Females Rolling Gate Queue, Official Document Needed is %s\n\n",person.personID,g_OfficialDocument[person.officialDocumentNeeded]);
                fflush(stdout);

          }

}

void enqueueToGroupingAreaQueue(struct personInformation personInf){
        struct personInformation person = personInf;

        struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL) {
        printf("\nOVERFLOW\n");
        return;
        } else {
                ptr->personInfo=person;
                if (FrontForGroupingAreaQueue == NULL) {
                FrontForGroupingAreaQueue = ptr;
                RearForGroupingAreaQueue = ptr;
                FrontForGroupingAreaQueue->nextPesron = NULL;
                RearForGroupingAreaQueue->nextPesron = NULL;
                } else {
                RearForGroupingAreaQueue->nextPesron = ptr;
                RearForGroupingAreaQueue = ptr;
                RearForGroupingAreaQueue->nextPesron = NULL;
                }
                sleep(randomIintegerInRange(3,6));//simulation for time delaying
                g_numberOfpeopleInGroupingArea++;
                printf("\n\nPerson %d Enter Grouping Area Queue, Gender %c,Official Document Needed is %s\n\n",person.personID,person.gender,g_OfficialDocument[person.officialDocumentNeeded]);
                fflush(stdout);

          }

}


void enqueueToAccessQueues(pid_t personID, char gender, int officialDocumentNeeded, float timerForPatience) {

    struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
    if (ptr == NULL) {
        printf("\nOVERFLOW\n");
        return;
    } else {

        if (gender == 'M'){
                ptr->personInfo.personID  = personID;
                ptr->personInfo.gender = gender;
                ptr->personInfo.officialDocumentNeeded= officialDocumentNeeded;
                ptr->personInfo.timerForPatience = timerForPatience;
                if (FrontAccessQueueMales == NULL) {
                FrontAccessQueueMales = ptr;
                RearAccessQueueMales = ptr;
                FrontAccessQueueMales->nextPesron = NULL;
                 RearAccessQueueMales->nextPesron = NULL;
                } else {
                RearAccessQueueMales->nextPesron = ptr;
                RearAccessQueueMales = ptr;
                RearAccessQueueMales->nextPesron = NULL;
                }
                g_numberOfMalesInAccessQueue++;

        } else {
                ptr->personInfo.personID  = personID;
                ptr->personInfo.gender = gender;
                ptr->personInfo.officialDocumentNeeded= officialDocumentNeeded;
                ptr->personInfo.timerForPatience = timerForPatience;
                if (FrontAccessQueueFemales == NULL) {
                FrontAccessQueueFemales = ptr;
                RearAccessQueueFemales = ptr;
                FrontAccessQueueFemales->nextPesron = NULL;
                 RearAccessQueueFemales->nextPesron = NULL;
                } else {
                RearAccessQueueFemales->nextPesron = ptr;
                RearAccessQueueFemales = ptr;
                RearAccessQueueFemales->nextPesron = NULL;
                }
                g_numberOfFemalesInAccessQueue++;

          }



    }
}


struct personInformation dequeueNodeFromMalesAccessQueue() {
    struct accessQueueNode * temp =NULL;
    struct personInformation person= {0};
    if (FrontAccessQueueMales == NULL) {
        printf("Underflow dequeueNodeFromMalesAccessQueue\n");
        return;
    } else {
        temp = FrontAccessQueueMales;
        person = temp->personInfo;
        FrontAccessQueueMales = FrontAccessQueueMales->nextPesron;
        g_numberOfMalesInAccessQueue--;
        free(temp);
    }
    return person;
}

struct personInformation dequeueNodeFromFemalesAccessQueue() {
    struct accessQueueNode * temp =NULL;
    struct personInformation person ={0};
    if (FrontAccessQueueFemales == NULL) {
        printf("Underflow dequeueNodeFromFemalesAccessQueue\n");
        return;
    } else {
        temp = FrontAccessQueueFemales;
        person = temp->personInfo;
        FrontAccessQueueFemales = FrontAccessQueueFemales->nextPesron;
         g_numberOfFemalesInAccessQueue--;
        free(temp);
    }
    return person;
}

struct personInformation dequeueNodeFromRollingGateQueueFemales() {
    struct accessQueueNode * temp =NULL;
    struct personInformation person;
    if (FrontRollingGateQueueFemales == NULL) {
        printf("Underflow dequeueNodeFromRollingGateQueueFemales\n");
        return;
    } else {
        temp = FrontRollingGateQueueFemales;
        person = temp->personInfo;
        FrontRollingGateQueueFemales = FrontRollingGateQueueFemales->nextPesron;
        free(temp);
        g_numberOfFemaelsInTheRollingGateQueue--;
    }
    return person;
}


struct personInformation dequeueNodeFromRollingGateQueueMales() {
    struct accessQueueNode * temp =NULL;
    struct personInformation person;
    if (FrontRollingGateQueueMales == NULL) {
        printf("Underflow dequeueNodeFromRollingGateQueueMales\n");
        return;
    } else {
        temp = FrontRollingGateQueueMales;
        person = temp->personInfo;
        FrontRollingGateQueueMales = FrontRollingGateQueueMales->nextPesron;
        free(temp);
        g_numberOfMaelsInTheRollingGateQueue--;
    }
    return person;
}



void displyGroupingAreaQueue(){

    struct accessQueueNode * temp = NULL;
    if ((FrontForGroupingAreaQueue  == NULL) && (RearForGroupingAreaQueue == NULL)) {
        printf("\n\nMales Access Queue is Empty\n");
    } else {
        printf("\n\nThe Access queue for Males is :\n\n");
        temp = FrontForGroupingAreaQueue ;
        while (temp) {
            printf("%d--%c--%d--%d\n",temp->personInfo.personID,temp->personInfo.gender,temp->personInfo.officialDocumentNeeded,temp->personInfo.timerForPatience);
            temp = temp->nextPesron;
        }
    }


}


void displyAccessQueues(){

    struct accessQueueNode * temp = NULL;
    if ((FrontAccessQueueMales == NULL) && (RearAccessQueueMales == NULL)) {
        printf("\n\nMales Access Queue is Empty\n");
        fflush(stdout);
    } else {
        printf("\n\nThe Access queue for Males is :\n\n");
        temp = FrontAccessQueueMales;
        while (temp) {
            sleep(1);//simulation for time delaying
            printf("%d--%c--%d--%d\n",temp->personInfo.personID,temp->personInfo.gender,temp->personInfo.officialDocumentNeeded,temp->personInfo.timerForPatience);
            fflush(stdout);
            temp = temp->nextPesron;
        }
    }


    if ((FrontAccessQueueFemales == NULL) && (RearAccessQueueFemales == NULL)) {
        printf("\n\nFemales Access Queue is Empty\n");
        fflush(stdout);
    } else {
        printf("\n\nThe Access queue for Females is :\n\n");
        temp = FrontAccessQueueFemales;
        while (temp) {
            sleep(1);//simulation for time delaying
            printf("%d--%c--%d--%d\n",temp->personInfo.personID,temp->personInfo.gender,temp->personInfo.officialDocumentNeeded,temp->personInfo.timerForPatience);
            fflush(stdout);
            temp = temp->nextPesron;
        }
    }



}


void displyRollingGatesQueues(){

    struct accessQueueNode * temp = NULL;
    if ((FrontRollingGateQueueMales == NULL) && (RearRollingGateQueueMales == NULL)) {
        printf("\n\nMales Rolling Gate Queue is Empty\n");
    } else {
        printf("\n\nThe Rolling Gate Queue for Males is :\n\n");
        temp = FrontRollingGateQueueMales;
        while (temp) {
            printf("%d--%c--%d--%d\n",temp->personInfo.personID,temp->personInfo.gender,temp->personInfo.officialDocumentNeeded,temp->personInfo.timerForPatience);
            temp = temp->nextPesron;
        }
    }


    if ((FrontRollingGateQueueFemales == NULL) && (RearRollingGateQueueFemales == NULL)) {
        printf("\n\nFemales Rolling Gate Queue is Empty\n");
    } else {
        printf("\n\nThe Rolling Gate Queue for Females is :\n\n");
        temp = FrontRollingGateQueueFemales;
        while (temp) {
            printf("%d--%c--%d--%d\n",temp->personInfo.personID,temp->personInfo.gender,temp->personInfo.officialDocumentNeeded,temp->personInfo.timerForPatience);
            temp = temp->nextPesron;
        }
    }



}




void creatPeople(){
        int i,pid;
        for(i =0;i<g_peopleUntil8am;i++){

                //Simulation for arrival time for the single persone as some dealy
                sleep(randomIintegerInRange(minShiftingInArrivalTime,maxShiftingInArrivalTime));

                if ((pid = fork()) == -1) {
                        printf("fork failure\n");
                        exit (-1);
                }
                if (pid != 0){
                            // Print the info for the arrival person:
                            char gender = g_gender[randomIintegerInRange(0,1)];
                            int officialDocumentNeeded  = randomIintegerInRange(0,3);
                            printInfoForArrivalPerson(pid,gender,officialDocumentNeeded);
                            sleep(randomIintegerInRange(3,6));//simulation for time delaying
                            enqueueToAccessQueues(pid,gender,officialDocumentNeeded,randomIintegerInRange(1,4));
                }
                else
                        exit(-1);//pause();
        }
}



void insertToMalesRollingGateQueue() {

   g_numberOfMaelsInTheRollingGateQueue=0;
   while(1){
        if (g_numberOfMaelsInTheRollingGateQueue < g_threshold && g_numberOfMalesInAccessQueue > 0){

                sleep(randomIintegerInRange(3,6));//simulation for dealy time for  moving from Access queue to Rolling gate queue
                enqueueToRollingGateQueueMales();
                //displyRollingGatesQueues();
                //displyAccessQueues();

        }

   }
}



void insertToFemalesRollingGateQueue() {

   g_numberOfFemaelsInTheRollingGateQueue=0;
   while(1){
        if (g_numberOfFemaelsInTheRollingGateQueue < g_threshold && g_numberOfFemalesInAccessQueue > 0){

                sleep(randomIintegerInRange(3,6));//simulation for dealy time for  moving from Access queue to Rolling gate queue
                enqueueToRollingGateQueueFemales();
                //displyRollingGatesQueues();
                //displyAccessQueues();

        }

   }
}


void insertToMalesMetalDetector(){
  struct personInformation malePersonInMetalDetectorForMales ;
  while(1){
        if(g_numberOfMaelsInTheRollingGateQueue > 0){
                 sleep(randomIintegerInRange(3,6));//simulation for delay
                malePersonInMetalDetectorForMales = dequeueNodeFromRollingGateQueueMales();
                printf("\n\nPerson %d Enter the Metal Detector For Males, Gernder %c, Official Document Needed is %s\n\n",malePersonInMetalDetectorForMales.personID, malePersonInMetalDetectorForMales.gender,g_OfficialDocument[malePersonInMetalDetectorForMales.officialDocumentNeeded]);
                fflush(stdout);
                sleep(randomIintegerInRange(5,8));//simulation for delay in the Metal Detector as sleep between 5 to 8 seconds
                enqueueToGroupingAreaQueue(malePersonInMetalDetectorForMales);
                //printf("Person %d leave the Metal Detector For Males and Enter the Grouping Area, Gernder %c, Official Document Needed is %s\n",malePersonInMetalDetectorForMales.personID, malePersonInMetalDetectorForMales.gender,g_OfficialDocument[malePersonInMetalDetectorForMales.officialDocumentNeeded]);

        }

  }
}


void insertToFemalesMetalDetector(){
  struct personInformation femalePersonInMetalDetectorForMales ;
  while(1){
        if(g_numberOfFemaelsInTheRollingGateQueue > 0){
                sleep(randomIintegerInRange(3,6));//simulation for delay
                femalePersonInMetalDetectorForMales = dequeueNodeFromRollingGateQueueFemales();
                printf("\n\nPerson %d Enter the Metal Detector For Females, Gernder %c, Official Document Needed is %s\n\n",femalePersonInMetalDetectorForMales.personID, femalePersonInMetalDetectorForMales.gender,g_OfficialDocument[femalePersonInMetalDetectorForMales.officialDocumentNeeded]);
                fflush(stdout);
                sleep(randomIintegerInRange(5,8));//simulation for delay in the Metal Detector as sleep between 5 to 8 seconds
                enqueueToGroupingAreaQueue(femalePersonInMetalDetectorForMales);
                //printf("Person %d leave the Metal Detector For Males and Enter the Grouping Area, Gernder %c, Official Document Needed is %s\n",malePersonInMetalDetectorForMales.personID, malePersonInMetalDetectorForMales.gender,g_OfficialDocument[malePersonInMetalDetectorForMales.officialDocumentNeeded]);
                //fflush(stdout);
        }

  }
}


void printInfoForArrivalPerson(pid_t personID, char gender, int officialDocumentNeeded){

        printf("\n\nPerson %d arrived, Gernder %c, Official Document Needed is %s\n\n",personID, gender,g_OfficialDocument[officialDocumentNeeded]);
        fflush(stdout);
}

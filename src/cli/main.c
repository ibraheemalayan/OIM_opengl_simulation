#include "local.h"


//..........Fuctions........................

void readInputFile();
int randomIintegerInRange(int lower,int upper);
void displyAccessQueues();
void displyRollingGatesQueues();
void printInfoForArrivalPerson(struct personInformation person);
void simulation();
void displyGroupingAreaQueue();

//People creation 
void creatPeople();
void childSensitiveSignals();
void signalCatcher_movingTimeForchangeIndexLocationForPersonInTheHostQueue(int the_sig);
void signalCatcher_movingTimeForchangeLocationForPersonFromQueueToAnotherQueue(int the_sig);



//Dequeue from Queues -> 
struct personInformation dequeueNodeFromMalesAccessQueue();
struct personInformation dequeueNodeFromFemalesAccessQueue();
struct personInformation dequeueNodeFromRollingGateQueueMales();
struct personInformation dequeueNodeFromRollingGateQueueFemales();
struct personInformation dequeueNodeFromGroupingAreaQueue();
struct personInformation dequeueNodeFromBirthCertificatesTellerQueue();
struct personInformation dequeueNodeFromTravelDocumentsTellerQueue();
struct personInformation dequeueNodeFromFamilyReunionDocumentsTellerQueue();
struct personInformation dequeueNodeFromIDRelatedProblemsTellerQueue();

void updateIndexOfQueue(struct accessQueueNode * FrontOfQueue);

//Enqueue To Queues ->
void enqueueToAccessQueues(struct personInformation person);
void enqueueToRollingGateQueueFemales();
void enqueueToRollingGateQueueMales();
void enqueueToGroupingAreaQueue(struct personInformation personInf);
void enqueueToBirthCertificatesTelleQueue(struct personInformation personInf);
void enqueueToTravelDocumentsTelleQueue(struct personInformation personInf);
void enqueueToFamilyReunionDocumentsTelleQueue(struct personInformation personInf);
void enqueueToIDRelatedProblemsTelleQueue(struct personInformation personInf);


//Threads
void insertToMalesRollingGateQueue();
void insertToFemalesRollingGateQueue();
void insertToFemalesMetalDetector();
void insertToMalesMetalDetector();
void insertToTellersQueues();
void insertToBirthCertificatesTeller();
void insertToTravelDocumentsTeller();
void insertToFamilyReunionDocumentsTeller();
void insertToIDRelatedProblemsTeller();




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


//Pointers to the birth certificates teller
struct accessQueueNode * FrontForBirthCertificatesTellerQueue = NULL;
struct accessQueueNode * RearForBirthCertificatesTellerQueue = NULL;


//Pointers to the travel documents teller
struct accessQueueNode * FrontForTravelDocumentsTellerQueue = NULL;
struct accessQueueNode * RearForTravelDocumentsTellerQueue = NULL;



//Pointers to the family reunion documents teller
struct accessQueueNode * FrontForFamilyReunionDocumentsTellerQueue = NULL;
struct accessQueueNode * RearForFamilyReunionDocumentsTellerQueue = NULL;


//Pointers to the ID-related problems  teller
struct accessQueueNode * FrontForIDRelatedProblemsTellerQueue = NULL;
struct accessQueueNode * RearForIDRelatedProblemsTellerQueue = NULL;



//Threshold
#define g_threshold 3

//shifting In arrival time
int minShiftingInArrivalTime = 1;
int maxShiftingInArrivalTime = 3;

//Time for moving person insude the Queue in seconds
int minTimeForMovingPersonInsideHostQueue = 3;
int maxTimeForMovingPersonInsideHostQueue = 6;

//Time for moving person From Queue To Another Queue in seconds
int minTimeForMovingPersonFromQueueToAnotherQueue = 6;
int maxTimeForMovingPersonFromQueueToAnotherQueue = 9;

//Number of Females and males in the Access queues
int g_numberOfMalesInAccessQueue = 0;
int g_numberOfFemalesInAccessQueue = 0;


//Number of Feamles and males in Rolling gate queue
int g_numberOfFemaelsInTheRollingGateQueue=0;
int g_numberOfMaelsInTheRollingGateQueue=0;

//Number of people in the grouping area
int g_numberOfpeopleInGroupingArea =0;

//Number of people in the Birth Certificates Teller Queue
int g_numberOfpeopleInBirthCertificatesTellerQueue =0;

//Number of people in the Travel Documents Teller Queue
int g_numberOfpeopleInTravelDocumentsTellerQueue =0;

//Number of people in the Family Reunion Documents Teller Queue
int g_numberOfpeopleInFamilyReunionDocumentsTellerQueue =0;

//Number of people in the ID Related Problems Teller Queue
int g_numberOfpeopleInIDRelatedProblemsTellerQueue =0;


//Array of Official Document
char g_OfficialDocument[4][40] ={"Birth Certificates","Travel Documents","Family Reunion Documents","ID-related Problems"};

//Array for status when leaving OIM either satisfied or unhappy
char g_leaving_OIM_Status[2][15]={"Satisfied","Unhappy"};

//Mutex on Queues
pthread_mutex_t malesAccessQueue_mutex=PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t femalesAccessQueue_mutex=PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t malesRollingGatQueue_mutex=PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t femalesRollingGatQueue_mutex=PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t groupingAreaQueue_mutex=PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t BirthCertificatesQueue_mutex=PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t TravelDocumentsQueue_mutex=PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t FamilyReunionDocumentsQueue_mutex=PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t IDRelatedProblemsQueue_mutex=PTHREAD_MUTEX_INITIALIZER;  

int main()
{
	simulation();
	return 0;
}

void simulation(){

	printf("\n\n\n\n.......4:30 AM: People Start coming.......\n\n");
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
	pthread_create(&p_thread1, NULL,  (void *)insertToMalesRollingGateQueue, NULL);
  	

	/* create a new thread that will keep move nodes from Females access queue to Rolling Gate Queue "Females" */
        pthread_t p_thread2;
        pthread_create(&p_thread2, NULL,  (void *)insertToFemalesRollingGateQueue, NULL);

	/* create a new thread that will keep move nodes from Males rolling gate queue to the Males metal detector*/
	pthread_t p_thread3;
	pthread_create(&p_thread3, NULL,  (void *)insertToMalesMetalDetector, NULL);

	/* create a new thread that will keep move nodes from  Females rolling gate queue to the  Females metal detector*/
        pthread_t p_thread4;
        pthread_create(&p_thread4, NULL,  (void *)insertToFemalesMetalDetector,  NULL);


	/* create a new thread that will keep move nodes from  Grouping area queue to tellers Queues*/
        pthread_t p_thread5;
        pthread_create(&p_thread5, NULL,  (void *)insertToTellersQueues,  NULL);


	/* create a new thread that will keep move nodes from  Birth Certificates Teller Queue to the Birth Certificates Teller*/
        pthread_t p_thread6;
        pthread_create(&p_thread6, NULL,  (void *)insertToBirthCertificatesTeller,  NULL);
	

	/* create a new thread that will keep move nodes from  Travel Documents Teller Queue to the Travel Documents Teller*/
        pthread_t p_thread7;
        pthread_create(&p_thread7, NULL,  (void *)insertToTravelDocumentsTeller,  NULL);


	/* create a new thread that will keep move nodes from  Family Reunion Documents Teller Queue to the Family Reunion Documents Teller*/
        pthread_t p_thread8;
        pthread_create(&p_thread8, NULL,  (void *)insertToFamilyReunionDocumentsTeller,  NULL);


	/* create a new thread that will keep move nodes from  ID Related Problems Teller Queue to the ID Related Problems Teller*/
        pthread_t p_thread9;
        pthread_create(&p_thread9, NULL,  (void *)insertToIDRelatedProblemsTeller,  NULL);


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
	pthread_join(p_thread5, NULL);
	pthread_join(p_thread6, NULL);
	pthread_join(p_thread7, NULL);
	pthread_join(p_thread8, NULL);
	pthread_join(p_thread9, NULL);	

}

void readInputFile(){
	FILE * fp;
	char * line = NULL;
    	size_t len = 0;
    	ssize_t read;

    	fp = fopen("cli/inputfile.txt", "r");
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
        pthread_mutex_lock(&malesRollingGatQueue_mutex);
	    struct personInformation person = dequeueNodeFromMalesAccessQueue();
	    struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL ) {
            printf("\nOVERFLOW\n");
            return;
        } else {
                person.indexLocationInTheHostQueue=g_numberOfMaelsInTheRollingGateQueue;//update Index
                kill(person.personID,SIGUSR1);//Signal to the process to move inside the host Queue
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
        pthread_mutex_unlock(&malesRollingGatQueue_mutex);

}

void enqueueToRollingGateQueueFemales(){
        pthread_mutex_lock(&femalesRollingGatQueue_mutex);
	    struct personInformation person = dequeueNodeFromFemalesAccessQueue();
        struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL) {
        printf("\nOVERFLOW\n");
        return;
        } else {
                person.indexLocationInTheHostQueue=g_numberOfFemaelsInTheRollingGateQueue;//update Index
                kill(person.personID,SIGUSR1);//Signal to the process to move inside the host Queue
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
          pthread_mutex_unlock(&femalesRollingGatQueue_mutex);

}

void enqueueToGroupingAreaQueue(struct personInformation personInf){
        pthread_mutex_lock(&groupingAreaQueue_mutex);
      	struct personInformation person = personInf;
        struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL) {
            printf("\nOVERFLOW\n");
            return;
        } else {
                person.indexLocationInTheHostQueue=g_numberOfpeopleInGroupingArea;//update Index
                kill(person.personID,SIGUSR1);//Signal to the process to move inside the host Queue
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
          pthread_mutex_unlock(&groupingAreaQueue_mutex);

}

void enqueueToBirthCertificatesTelleQueue(struct personInformation personInf){

        pthread_mutex_lock(&BirthCertificatesQueue_mutex);
	    struct personInformation person = personInf;

        struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL) {
            printf("\nOVERFLOW enqueueToBirthCertificatesTelleQueue\n");
            return;
        } else {
                person.indexLocationInTheHostQueue=g_numberOfpeopleInBirthCertificatesTellerQueue;//update Index
                kill(person.personID,SIGUSR1);//Signal to the process to move inside the host Queue
                ptr->personInfo=person;
                if (FrontForBirthCertificatesTellerQueue == NULL) {
                    FrontForBirthCertificatesTellerQueue = ptr;
                    RearForBirthCertificatesTellerQueue = ptr;
                    FrontForBirthCertificatesTellerQueue->nextPesron = NULL;
                    RearForBirthCertificatesTellerQueue->nextPesron = NULL;
                } else {
                    RearForBirthCertificatesTellerQueue->nextPesron = ptr;
                    RearForBirthCertificatesTellerQueue = ptr;
                    RearForBirthCertificatesTellerQueue->nextPesron = NULL;
                }
                sleep(randomIintegerInRange(3,6));//simulation for time delaying
                g_numberOfpeopleInBirthCertificatesTellerQueue++;
                printf("\n\nPerson %d Enter Birth Certificates Teller Queue, Gender %c,Official Document Needed is %s\n\n",person.personID,person.gender,g_OfficialDocument[person.officialDocumentNeeded]);
                fflush(stdout);

          }
          pthread_mutex_unlock(&BirthCertificatesQueue_mutex);

}

void enqueueToTravelDocumentsTelleQueue(struct personInformation personInf){
        pthread_mutex_lock(&TravelDocumentsQueue_mutex);
        struct personInformation person = personInf;
        struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL) {
            printf("\nOVERFLOW enqueueToTravelDocumentsTelleQueue\n");
            return;
        } else {
                person.indexLocationInTheHostQueue=g_numberOfpeopleInTravelDocumentsTellerQueue;//update Index
                kill(person.personID,SIGUSR1);//Signal to the process to move inside the host Queue
                ptr->personInfo=person;
                if (FrontForTravelDocumentsTellerQueue == NULL) {
                    FrontForTravelDocumentsTellerQueue = ptr;
                    RearForTravelDocumentsTellerQueue = ptr;
                    FrontForTravelDocumentsTellerQueue->nextPesron = NULL;
                    RearForTravelDocumentsTellerQueue->nextPesron = NULL;
                } else {
                    RearForTravelDocumentsTellerQueue->nextPesron = ptr;
                    RearForTravelDocumentsTellerQueue = ptr;
                    RearForTravelDocumentsTellerQueue->nextPesron = NULL;
                }
                sleep(randomIintegerInRange(3,6));//simulation for time delaying
                g_numberOfpeopleInTravelDocumentsTellerQueue++;
                printf("\n\nPerson %d Enter Travel Documents Teller Queue, Gender %c,Official Document Needed is %s\n\n",person.personID,person.gender,g_OfficialDocument[person.officialDocumentNeeded]);
                fflush(stdout);

          }
          pthread_mutex_unlock(&TravelDocumentsQueue_mutex);

}

void enqueueToFamilyReunionDocumentsTelleQueue(struct personInformation personInf){
        pthread_mutex_lock(&FamilyReunionDocumentsQueue_mutex);
        struct personInformation person = personInf;
        struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL) {
            printf("\nOVERFLOW enqueueToFamilyReunionDocumentsTelleQueue\n");
            return;
        } else {
                person.indexLocationInTheHostQueue=g_numberOfpeopleInFamilyReunionDocumentsTellerQueue;//update Index
                kill(person.personID,SIGUSR1);//Signal to the process to move inside the host Queue
                ptr->personInfo=person;
                if (FrontForFamilyReunionDocumentsTellerQueue    == NULL) {
                    FrontForFamilyReunionDocumentsTellerQueue = ptr;
                    RearForFamilyReunionDocumentsTellerQueue = ptr;
                    FrontForFamilyReunionDocumentsTellerQueue->nextPesron = NULL;
                    RearForFamilyReunionDocumentsTellerQueue->nextPesron = NULL;
                } else {
                    RearForFamilyReunionDocumentsTellerQueue->nextPesron = ptr;
                    RearForFamilyReunionDocumentsTellerQueue = ptr;
                    RearForFamilyReunionDocumentsTellerQueue->nextPesron = NULL;
                }
                sleep(randomIintegerInRange(3,6));//simulation for time delaying
                g_numberOfpeopleInFamilyReunionDocumentsTellerQueue++;
                printf("\n\nPerson %d Enter Family Reunion Documents Teller Queue, Gender %c,Official Document Needed is %s\n\n",person.personID,person.gender,g_OfficialDocument[person.officialDocumentNeeded]);
                fflush(stdout);

          }
          pthread_mutex_unlock(&FamilyReunionDocumentsQueue_mutex);

}

void enqueueToIDRelatedProblemsTelleQueue(struct personInformation personInf){
        pthread_mutex_lock(&IDRelatedProblemsQueue_mutex);
        struct personInformation person = personInf;
        struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL) {
            printf("\nOVERFLOW enqueueToIDRelatedProblemsTelleQueue\n");
            return;
        } else {
                person.indexLocationInTheHostQueue=g_numberOfpeopleInIDRelatedProblemsTellerQueue;//update Index
                kill(person.personID,SIGUSR1);//Signal to the process to move inside the host Queue
                ptr->personInfo=person;
                if (FrontForIDRelatedProblemsTellerQueue == NULL) {
                    FrontForIDRelatedProblemsTellerQueue = ptr;
                    RearForIDRelatedProblemsTellerQueue = ptr;
                    FrontForIDRelatedProblemsTellerQueue->nextPesron = NULL;
                    RearForIDRelatedProblemsTellerQueue->nextPesron = NULL;
                } else {
                    RearForIDRelatedProblemsTellerQueue->nextPesron = ptr;
                    RearForIDRelatedProblemsTellerQueue = ptr; 
                    RearForIDRelatedProblemsTellerQueue->nextPesron = NULL;
                }
                sleep(randomIintegerInRange(3,6));//simulation for time delaying
                g_numberOfpeopleInIDRelatedProblemsTellerQueue++;
                printf("\n\nPerson %d Enter ID Related Problems Teller Queue, Gender %c,Official Document Needed is %s\n\n",person.personID,person.gender,g_OfficialDocument[person.officialDocumentNeeded]);
                fflush(stdout);

          }
          pthread_mutex_unlock(&IDRelatedProblemsQueue_mutex);

}




void enqueueToAccessQueues(struct personInformation person) {

    struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
    if (ptr == NULL) {
        printf("\nOVERFLOW\n");
        return;
    } else {

	if (person.gender == 'M'){
            pthread_mutex_lock(&malesAccessQueue_mutex);
            person.indexLocationInTheHostQueue=g_numberOfMalesInAccessQueue;//update Index
            kill(person.personID,SIGUSR1);//Signal to the process to move inside the host Queue
	        ptr->personInfo = person;
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
            pthread_mutex_unlock(&malesAccessQueue_mutex);

	} else {
            pthread_mutex_lock(&femalesAccessQueue_mutex);
            person.indexLocationInTheHostQueue=g_numberOfFemalesInAccessQueue;//update Index
            kill(person.personID,SIGUSR1);//Signal to the process to move inside the host Queue
		    ptr->personInfo = person;
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
            pthread_mutex_unlock(&femalesAccessQueue_mutex);

	  }



    }
}


struct personInformation dequeueNodeFromMalesAccessQueue() {
    pthread_mutex_lock(&malesAccessQueue_mutex );
    struct accessQueueNode * temp =NULL; 	
    struct personInformation person= {0};
    person.indexLocationInTheHostQueue=-1;//update Index
    if (FrontAccessQueueMales == NULL) {
        printf("Underflow dequeueNodeFromMalesAccessQueue\n");
        return person;
    } else {
        temp = FrontAccessQueueMales;
	    person = temp->personInfo;
        person.indexLocationInTheHostQueue=-1;//update Index
        kill(person.personID,SIGUSR2);//Signal to the process to move to the next Queue
        FrontAccessQueueMales = FrontAccessQueueMales->nextPesron;
	    g_numberOfMalesInAccessQueue--;
        free(temp);
    }
    return person;
    pthread_mutex_unlock(&malesAccessQueue_mutex );
}

struct personInformation dequeueNodeFromFemalesAccessQueue() {
    pthread_mutex_lock(&femalesAccessQueue_mutex );
    struct accessQueueNode * temp =NULL;
    struct personInformation person ={0};
    person.indexLocationInTheHostQueue=-1;//update Index
    if (FrontAccessQueueFemales == NULL) {
        printf("Underflow dequeueNodeFromFemalesAccessQueue\n");
        return person;
    } else {
        temp = FrontAccessQueueFemales;
        person = temp->personInfo;
        person.indexLocationInTheHostQueue=-1;//update Index
        kill(person.personID,SIGUSR2);//Signal to the process to move to the next Queue
        FrontAccessQueueFemales = FrontAccessQueueFemales->nextPesron;
	    g_numberOfFemalesInAccessQueue--;
        free(temp);
    }
    return person;
    pthread_mutex_unlock(&femalesAccessQueue_mutex );
}

struct personInformation dequeueNodeFromGroupingAreaQueue() {
    pthread_mutex_lock(&groupingAreaQueue_mutex);
    struct accessQueueNode * temp =NULL;
    struct personInformation person ={0};
    person.indexLocationInTheHostQueue=-1;//update Index
    if (FrontForGroupingAreaQueue  == NULL) {
        printf("Underflow dequeueNodeFromGroupingAreaQueue\n");
        return person;
    } else {
        temp = FrontForGroupingAreaQueue;
        person = temp->personInfo;
        person.indexLocationInTheHostQueue=-1;//update Index
        kill(person.personID,SIGUSR2);//Signal to the process to move to the next Queue
        FrontForGroupingAreaQueue = FrontForGroupingAreaQueue->nextPesron;
        g_numberOfpeopleInGroupingArea--;
        free(temp);
    }
    return person;
    pthread_mutex_unlock(&groupingAreaQueue_mutex);
}

struct personInformation dequeueNodeFromBirthCertificatesTellerQueue() {
    pthread_mutex_lock(&BirthCertificatesQueue_mutex);
    struct accessQueueNode * temp =NULL;
    struct personInformation person ={0};
    person.indexLocationInTheHostQueue=-1;//update Index
    if (FrontForBirthCertificatesTellerQueue   == NULL) {
        printf("Underflow dequeueNodeFromBirthCertificatesTellerQueue\n");
        return person;
    } else {
        temp = FrontForBirthCertificatesTellerQueue;
        person = temp->personInfo;
        person.indexLocationInTheHostQueue=-1;//update Index
        kill(person.personID,SIGUSR2);//Signal to the process to move to the next Queue
        FrontForBirthCertificatesTellerQueue = FrontForBirthCertificatesTellerQueue->nextPesron;
        g_numberOfpeopleInBirthCertificatesTellerQueue--;
        free(temp);
    }
    return person;
    pthread_mutex_unlock(&BirthCertificatesQueue_mutex);
}

struct personInformation dequeueNodeFromTravelDocumentsTellerQueue() {
    pthread_mutex_lock(&TravelDocumentsQueue_mutex);
    struct accessQueueNode * temp =NULL;
    struct personInformation person ={0};
    person.indexLocationInTheHostQueue=-1;//update Index
    if (FrontForTravelDocumentsTellerQueue == NULL) {
        printf("Underflow dequeueNodeFromTravelDocumentsTellerQueue\n");
        return person;
    } else {
        temp = FrontForTravelDocumentsTellerQueue ;
        person = temp->personInfo;
        person.indexLocationInTheHostQueue=-1;//update Index
        kill(person.personID,SIGUSR2);//Signal to the process to move to the next Queue
        FrontForTravelDocumentsTellerQueue  = FrontForTravelDocumentsTellerQueue->nextPesron;
        g_numberOfpeopleInTravelDocumentsTellerQueue--;
        free(temp);
    }
    return person;
        pthread_mutex_unlock(&TravelDocumentsQueue_mutex);

}

struct personInformation dequeueNodeFromFamilyReunionDocumentsTellerQueue() {
    pthread_mutex_lock(&FamilyReunionDocumentsQueue_mutex);
    struct accessQueueNode * temp =NULL;
    struct personInformation person ={0};
    person.indexLocationInTheHostQueue=-1;//update Index
    if (FrontForFamilyReunionDocumentsTellerQueue == NULL) {
        printf("Underflow dequeueNodeFromFamilyReunionDocumentsTellerQueue\n");
        return person;
    } else {
        temp = FrontForFamilyReunionDocumentsTellerQueue;
        person = temp->personInfo;
        person.indexLocationInTheHostQueue=-1;//update Index
        kill(person.personID,SIGUSR2);//Signal to the process to move to the next Queue
        FrontForFamilyReunionDocumentsTellerQueue   = FrontForFamilyReunionDocumentsTellerQueue->nextPesron;
        g_numberOfpeopleInFamilyReunionDocumentsTellerQueue--;
        free(temp);
    }
    return person;
    pthread_mutex_unlock(&FamilyReunionDocumentsQueue_mutex);
}


struct personInformation dequeueNodeFromIDRelatedProblemsTellerQueue() {
    pthread_mutex_lock(&IDRelatedProblemsQueue_mutex);
    struct accessQueueNode * temp =NULL;
    struct personInformation person ={0};
    person.indexLocationInTheHostQueue=-1;//update Index
    if (FrontForIDRelatedProblemsTellerQueue == NULL) {
        printf("Underflow dequeueNodeFromIDRelatedProblemsTellerQueue\n");
        return person;
    } else {
        temp = FrontForIDRelatedProblemsTellerQueue;
        person = temp->personInfo;
        person.indexLocationInTheHostQueue=-1;//update Index
        kill(person.personID,SIGUSR2);//Signal to the process to move to the next Queue
        FrontForIDRelatedProblemsTellerQueue  = FrontForIDRelatedProblemsTellerQueue->nextPesron;
        g_numberOfpeopleInIDRelatedProblemsTellerQueue--;
        free(temp);
    }
    return person;
    pthread_mutex_unlock(&IDRelatedProblemsQueue_mutex);
}


struct personInformation dequeueNodeFromRollingGateQueueFemales() {
    pthread_mutex_lock(&femalesRollingGatQueue_mutex);
    struct accessQueueNode * temp =NULL;
    struct personInformation person={0};
    person.indexLocationInTheHostQueue=-1;//update Index
    if (FrontRollingGateQueueFemales == NULL) {
        printf("Underflow dequeueNodeFromRollingGateQueueFemales\n");
        return person;
    } else {
        temp = FrontRollingGateQueueFemales;
        person = temp->personInfo;
        person.indexLocationInTheHostQueue=-1;//update Index
        kill(person.personID,SIGUSR2);//Signal to the process to move to the next Queue
        FrontRollingGateQueueFemales = FrontRollingGateQueueFemales->nextPesron;
        free(temp);
	    g_numberOfFemaelsInTheRollingGateQueue--;
    }
    return person;
    pthread_mutex_unlock(&femalesRollingGatQueue_mutex);
}


struct personInformation dequeueNodeFromRollingGateQueueMales() {
    pthread_mutex_lock(&malesRollingGatQueue_mutex);
    struct accessQueueNode * temp =NULL;
    struct personInformation person={0};
    person.indexLocationInTheHostQueue=-1;//update Index
    if (FrontRollingGateQueueMales == NULL) {
        printf("Underflow dequeueNodeFromRollingGateQueueMales\n");
        return person;
    } else {
        temp = FrontRollingGateQueueMales;
        person = temp->personInfo;
        person.indexLocationInTheHostQueue=-1;//update Index
        kill(person.personID,SIGUSR2);//Signal to the process to move to the next Queue
        FrontRollingGateQueueMales = FrontRollingGateQueueMales->nextPesron;
        free(temp);
	    g_numberOfMaelsInTheRollingGateQueue--;
    }
    return person;
    pthread_mutex_unlock(&malesRollingGatQueue_mutex);

}


void updateIndexOfQueue(struct accessQueueNode * FrontOfQueue){
    struct accessQueueNode * tmp;
    tmp = FrontOfQueue;
    while (tmp != NULL)
    {
       tmp->personInfo.indexLocationInTheHostQueue=tmp->personInfo.indexLocationInTheHostQueue-1;
       kill(tmp->personInfo.personID,SIGUSR1);//Signal to the process to move inside the host Queue
       tmp=tmp->nextPesron;
    }
    

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
                
		
		if ((pid = fork()) == -1) {
                        printf("fork failure\n");
                        exit (-1);
                }
                if (pid != 0){
      			    // Print the info for the arrival person:
                    struct personInformation person;
                    person.personID = pid;
			        person.gender = g_gender[randomIintegerInRange(0,1)];
			        person.officialDocumentNeeded  = randomIintegerInRange(0,3);
                    person.timerForPatience= randomIintegerInRange(20,30);
                    person.indexLocationInTheHostQueue=-1;
                    person.tiketNumberInGroupingArea=-1;
			        printInfoForArrivalPerson(person);
			        sleep(randomIintegerInRange(minShiftingInArrivalTime,maxShiftingInArrivalTime));//simulation for time delaying for arrival time
                    enqueueToAccessQueues(person);
                }
		        else
			        break;//exit(-1);//pause();
        }

        if (pid == 0){
            childSensitiveSignals();
            while (1)
            {
                //Pause until reseve signal from thread to move inside the host queue or
                //until reseve signal from thread to move from queue to anothr 
                pause(); 
            } 
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



void insertToMalesRollingGateQueue() {
	
    g_numberOfMaelsInTheRollingGateQueue=0;
    while(1){
	if (g_numberOfMaelsInTheRollingGateQueue < g_threshold && g_numberOfMalesInAccessQueue > 0){
		
		sleep(randomIintegerInRange(3,6));//simulation for dealy time for  moving from Access queue to Rolling gate queue
		enqueueToRollingGateQueueMales();
        updateIndexOfQueue(FrontAccessQueueMales);//updateIndexOfQueue for AccessQueueMales
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
                updateIndexOfQueue(FrontAccessQueueFemales);//updateIndexOfQueue for AccessQueueFemales
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
        updateIndexOfQueue(FrontRollingGateQueueMales);//updateIndexOfQueue for RollingGateQueueMales
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
            updateIndexOfQueue(FrontRollingGateQueueFemales);//updateIndexOfQueue for RollingGateQueueFemales
            //printf("Person %d leave the Metal Detector For Males and Enter the Grouping Area, Gernder %c, Official Document Needed is %s\n",malePersonInMetalDetectorForMales.personID, malePersonInMetalDetectorForMales.gender,g_OfficialDocument[malePersonInMetalDetectorForMales.officialDocumentNeeded]);
		    //fflush(stdout);
        }

  }
}


void insertToTellersQueues(){

  struct personInformation Person;
  while(1){
	if(g_numberOfpeopleInGroupingArea > 0){
		sleep(randomIintegerInRange(3,6));//simulation for delay
        Person = dequeueNodeFromGroupingAreaQueue();
        printf("\n\nPerson %d leave the Grouping Area Queue, Gernder %c, Official Document Needed is %s\n\n",Person.personID, Person.gender,g_OfficialDocument[Person.officialDocumentNeeded]);
        fflush(stdout);
        sleep(randomIintegerInRange(4,7));//simulation for delaying while moving to Tellers Queuesas sleep between 5 to 8 seconds
        if (Person.officialDocumentNeeded == 0)
			enqueueToBirthCertificatesTelleQueue(Person);
		else if (Person.officialDocumentNeeded == 1)
			enqueueToTravelDocumentsTelleQueue(Person);
		else if (Person.officialDocumentNeeded == 2)
			enqueueToFamilyReunionDocumentsTelleQueue(Person);
		else if (Person.officialDocumentNeeded == 3)
			enqueueToIDRelatedProblemsTelleQueue(Person);

        updateIndexOfQueue(FrontForGroupingAreaQueue);//updateIndexOfQueue for GroupingAreaQueue

	}

  }

}

void insertToBirthCertificatesTeller(){

  struct personInformation Person ;
  int leaving_OIM_Status; // 0:Satisfied ,  1:Unhappy
  while(1){
        if(g_numberOfpeopleInBirthCertificatesTellerQueue  > 0){
                //sleep(randomIintegerInRange(3,6));//simulation for delay
                Person = dequeueNodeFromBirthCertificatesTellerQueue();
                printf("\n\nPerson %d achieve the Birth Certificates Teller, Gernder %c, Official Document Needed is %s\n\n",Person.personID, Person.gender,g_OfficialDocument[Person.officialDocumentNeeded]);
                fflush(stdout);
                sleep(randomIintegerInRange(10,15));//simulation for delay in the Birth Certificates Teller as sleep between 10 to 15 seconds
		        leaving_OIM_Status = randomIintegerInRange(0,1);// 0:Satisfied ,  1:Unhappy
                printf("Person %d leave the Birth Certificates Teller, Gernder %c, Official Document Needed is %s, leaving OIM Status :%s\n",Person.personID, Person.gender,g_OfficialDocument[Person.officialDocumentNeeded],g_leaving_OIM_Status[leaving_OIM_Status]);
                fflush(stdout);
                updateIndexOfQueue(FrontForBirthCertificatesTellerQueue);//updateIndexOfQueue for BirthCertificatesTellerQueue
        }

  }



}
void insertToTravelDocumentsTeller(){

  struct personInformation Person ;
  int leaving_OIM_Status; // 0:Satisfied ,  1:Unhappy
  while(1){
        if(g_numberOfpeopleInTravelDocumentsTellerQueue  > 0){
                //sleep(randomIintegerInRange(3,6));//simulation for delay
                Person = dequeueNodeFromTravelDocumentsTellerQueue();
                printf("\n\nPerson %d achieve the Travel Documents Teller, Gernder %c, Official Document Needed is %s\n\n",Person.personID, Person.gender,g_OfficialDocument[Person.officialDocumentNeeded]);
                fflush(stdout);
                sleep(randomIintegerInRange(10,15));//simulation for delay in the Travel Documents Teller as sleep between 10 to 15 seconds
                leaving_OIM_Status = randomIintegerInRange(0,1);// 0:Satisfied ,  1:Unhappy
                printf("Person %d leave the Travel Documents Teller, Gernder %c, Official Document Needed is %s, leaving OIM Status :%s\n",Person.personID, Person.gender,g_OfficialDocument[Person.officialDocumentNeeded],g_leaving_OIM_Status[leaving_OIM_Status]);
                fflush(stdout);
                updateIndexOfQueue(FrontForTravelDocumentsTellerQueue);//updateIndexOfQueue for TravelDocumentsTellerQueue
        }

  }

}
void insertToFamilyReunionDocumentsTeller(){

  struct personInformation Person ;
  int leaving_OIM_Status; // 0:Satisfied ,  1:Unhappy
  while(1){
        if(g_numberOfpeopleInFamilyReunionDocumentsTellerQueue   > 0){
                //sleep(randomIintegerInRange(3,6));//simulation for delay
                Person = dequeueNodeFromTravelDocumentsTellerQueue();
                printf("\n\nPerson %d achieve the Family Reunion Documents Teller, Gernder %c, Official Document Needed is %s\n\n",Person.personID, Person.gender,g_OfficialDocument[Person.officialDocumentNeeded]);
                fflush(stdout);
                sleep(randomIintegerInRange(10,15));//simulation for delay in the Family Reunion Documents Teller as sleep between 10 to 15 seconds
                leaving_OIM_Status = randomIintegerInRange(0,1);// 0:Satisfied ,  1:Unhappy
                printf("Person %d leave the Family Reunion Documents Teller, Gernder %c, Official Document Needed is %s, leaving OIM Status :%s\n",Person.personID, Person.gender,g_OfficialDocument[Person.officialDocumentNeeded],g_leaving_OIM_Status[leaving_OIM_Status]);
                fflush(stdout);
                updateIndexOfQueue(FrontForFamilyReunionDocumentsTellerQueue);//updateIndexOfQueue for FamilyReunionDocumentsTellerQueue
        }

  }

}

void insertToIDRelatedProblemsTeller(){

  struct personInformation Person ;
  int leaving_OIM_Status; // 0:Satisfied ,  1:Unhappy
  while(1){
        if(g_numberOfpeopleInIDRelatedProblemsTellerQueue   > 0){
                //sleep(randomIintegerInRange(3,6));//simulation for delay
                Person = dequeueNodeFromIDRelatedProblemsTellerQueue();
                printf("\n\nPerson %d achieve the ID Related Problems Teller, Gernder %c, Official Document Needed is %s\n\n",Person.personID, Person.gender,g_OfficialDocument[Person.officialDocumentNeeded]);
                fflush(stdout);
                sleep(randomIintegerInRange(10,15));//simulation for delay in the ID Related Problems Teller as sleep between 10 to 15 seconds
                leaving_OIM_Status = randomIintegerInRange(0,1);// 0:Satisfied ,  1:Unhappy
                printf("Person %d leave the ID Related Problems Teller, Gernder %c, Official Document Needed is %s, leaving OIM Status :%s\n",Person.personID, Person.gender,g_OfficialDocument[Person.officialDocumentNeeded],g_leaving_OIM_Status[leaving_OIM_Status]);
                fflush(stdout);
                updateIndexOfQueue(FrontForIDRelatedProblemsTellerQueue);//updateIndexOfQueue for IDRelatedProblemsTellerQueue
        }

  }

}



void printInfoForArrivalPerson(struct personInformation person){
	printf("\n\nPerson %d arrived, Gernder %c, Official Document Needed is %s\n\n",person.personID, person.gender,g_OfficialDocument[person.officialDocumentNeeded]);
	fflush(stdout);
}


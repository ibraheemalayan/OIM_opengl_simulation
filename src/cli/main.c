#include "local.h"


//..........Fuctions........................

void readInputFile();
int randomIintegerInRange(int lower,int upper);
void creatPeople();
void displyAccessQueues();
void displyRollingGatesQueues();
void printInfoForArrivalPerson(pid_t personID, char gender, int officialDocumentNeeded);
void simulation();
void displyGroupingAreaQueue();

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


//Enqueue To Queues ->
void enqueueToAccessQueues(pid_t personID, char gender, int officialDocumentNeeded, float timerForPatience);
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


	/* create a new thread that will keep move nodes from  Grouping area queue to tellers Queues*/
        pthread_t p_thread5;
        pthread_create(&p_thread5, NULL, insertToTellersQueues,  NULL);


	/* create a new thread that will keep move nodes from  Birth Certificates Teller Queue to the Birth Certificates Teller*/
        pthread_t p_thread6;
        pthread_create(&p_thread6, NULL, insertToBirthCertificatesTeller,  NULL);
	

	/* create a new thread that will keep move nodes from  Travel Documents Teller Queue to the Travel Documents Teller*/
        pthread_t p_thread7;
        pthread_create(&p_thread7, NULL, insertToTravelDocumentsTeller,  NULL);


	/* create a new thread that will keep move nodes from  Family Reunion Documents Teller Queue to the Family Reunion Documents Teller*/
        pthread_t p_thread8;
        pthread_create(&p_thread8, NULL, insertToFamilyReunionDocumentsTeller,  NULL);


	/* create a new thread that will keep move nodes from  ID Related Problems Teller Queue to the ID Related Problems Teller*/
        pthread_t p_thread9;
        pthread_create(&p_thread9, NULL, insertToIDRelatedProblemsTeller,  NULL);


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

void enqueueToBirthCertificatesTelleQueue(struct personInformation personInf){
        printf("\n\nenqueueToBirthCertificatesTelleQueue\n\n");
	fflush(stdout);
	struct personInformation person = personInf;

        struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL) {
        printf("\nOVERFLOW enqueueToBirthCertificatesTelleQueue\n");
        return;
        } else {
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

}

void enqueueToTravelDocumentsTelleQueue(struct personInformation personInf){
        struct personInformation person = personInf;

        struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL) {
        printf("\nOVERFLOW enqueueToTravelDocumentsTelleQueue\n");
        return;
        } else {
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

}

void enqueueToFamilyReunionDocumentsTelleQueue(struct personInformation personInf){
        struct personInformation person = personInf;

        struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL) {
        printf("\nOVERFLOW enqueueToFamilyReunionDocumentsTelleQueue\n");
        return;
        } else {
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

}

void enqueueToIDRelatedProblemsTelleQueue(struct personInformation personInf){
        struct personInformation person = personInf;

        struct accessQueueNode * ptr = (struct accessQueueNode * ) malloc(sizeof(struct accessQueueNode));
        if (ptr == NULL) {
        printf("\nOVERFLOW enqueueToIDRelatedProblemsTelleQueue\n");
        return;
        } else {
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

struct personInformation dequeueNodeFromGroupingAreaQueue() {
    struct accessQueueNode * temp =NULL;
    struct personInformation person ={0};
    if (FrontForGroupingAreaQueue  == NULL) {
        printf("Underflow dequeueNodeFromGroupingAreaQueue\n");
        return;
    } else {
        temp = FrontForGroupingAreaQueue;
        person = temp->personInfo;
        FrontForGroupingAreaQueue = FrontForGroupingAreaQueue->nextPesron;
        g_numberOfpeopleInGroupingArea--;
        free(temp);
    }
    return person;
}

struct personInformation dequeueNodeFromBirthCertificatesTellerQueue() {
    struct accessQueueNode * temp =NULL;
    struct personInformation person ={0};
    if (FrontForBirthCertificatesTellerQueue   == NULL) {
        printf("Underflow dequeueNodeFromBirthCertificatesTellerQueue\n");
        return;
    } else {
        temp = FrontForBirthCertificatesTellerQueue;
        person = temp->personInfo;
        FrontForBirthCertificatesTellerQueue = FrontForBirthCertificatesTellerQueue->nextPesron;
        g_numberOfpeopleInBirthCertificatesTellerQueue--;
        free(temp);
    }
    return person;
}

struct personInformation dequeueNodeFromTravelDocumentsTellerQueue() {
    struct accessQueueNode * temp =NULL;
    struct personInformation person ={0};
    if (FrontForTravelDocumentsTellerQueue == NULL) {
        printf("Underflow dequeueNodeFromTravelDocumentsTellerQueue\n");
        return;
    } else {
        temp = FrontForTravelDocumentsTellerQueue ;
        person = temp->personInfo;
        FrontForTravelDocumentsTellerQueue  = FrontForTravelDocumentsTellerQueue->nextPesron;
        g_numberOfpeopleInTravelDocumentsTellerQueue--;
        free(temp);
    }
    return person;
}

struct personInformation dequeueNodeFromFamilyReunionDocumentsTellerQueue() {
    struct accessQueueNode * temp =NULL;
    struct personInformation person ={0};
    if (FrontForFamilyReunionDocumentsTellerQueue == NULL) {
        printf("Underflow dequeueNodeFromFamilyReunionDocumentsTellerQueue\n");
        return;
    } else {
        temp = FrontForFamilyReunionDocumentsTellerQueue;
        person = temp->personInfo;
        FrontForFamilyReunionDocumentsTellerQueue   = FrontForFamilyReunionDocumentsTellerQueue->nextPesron;
        g_numberOfpeopleInFamilyReunionDocumentsTellerQueue--;
        free(temp);
    }
    return person;
}


struct personInformation dequeueNodeFromIDRelatedProblemsTellerQueue() {
    struct accessQueueNode * temp =NULL;
    struct personInformation person ={0};
    if (FrontForIDRelatedProblemsTellerQueue == NULL) {
        printf("Underflow dequeueNodeFromIDRelatedProblemsTellerQueue\n");
        return;
    } else {
        temp = FrontForIDRelatedProblemsTellerQueue;
        person = temp->personInfo;
        FrontForIDRelatedProblemsTellerQueue  = FrontForIDRelatedProblemsTellerQueue->nextPesron;
        g_numberOfpeopleInIDRelatedProblemsTellerQueue--;
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
                            enqueueToAccessQueues(pid,gender,officialDocumentNeeded,randomIintegerInRange(20,30));
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
        }

  }

}



void printInfoForArrivalPerson(pid_t personID, char gender, int officialDocumentNeeded){
	printf("\n\nPerson %d arrived, Gernder %c, Official Document Needed is %s\n\n",personID, gender,g_OfficialDocument[officialDocumentNeeded]);
	fflush(stdout);
}


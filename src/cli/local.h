#ifndef __LOCAL_H_
#define __LOCAL_H_


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct personInformation {
        pid_t   personID;       //Process ip
        char    gender;         //F,M
        int     officialDocumentNeeded; // "0"birth certificates, "1"travel documents, "2"family reunion documents, "3"ID-related problems
        int     timerForPatience;
        int     indexLocationInTheHostQueue;
        int     tiketNumberInGroupingArea;   
};


struct accessQueueNode {
        struct personInformation personInfo;
        struct accessQueueNode * nextPesron;

};

#endif

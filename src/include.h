
/*
 * local header file for pipe client-server
 */

#ifndef __INCLUDE_H_
#define __INCLUDE_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <sys/msg.h>

#include "std.h"

#define UISIG 7
#define PERSON 1L

enum MsgType
{
  PersonEntered = 1,
  PersonUpdated,
  PersonExited,
};

enum DocumentType
{
  BirthCertificate = 0,
  TravelDocument,
  FamilyReunion,
  IDRelatedProblems
};

enum Gender
{
  Male = 1,
  Female = 2
};

enum Location
{
  MaleOutsideGatesArea = 1,
  FemaleOutsideGatesArea = 2,
  MaleMetalDetectorQueue = 3,
  FemaleMetalDetectorQueue = 4,
  MetalDetector = 5,
  InnerGroupingArea = 6,
  Teller // teller 1 will be 7, teller 2 will be 8 and so on
};

typedef enum Location Location;
typedef enum Gender gender;
typedef enum MsgType MsgType;
typedef enum DocumentType DocumentType;

struct message_payload
{
  long msg_type; // first field of the message struct should be the message type
  int person_pid;
  float angriness;
  gender gender;
  int index_in_queue; // index if inside a queue
  Location current_location;
};

typedef struct message_payload message_payload;

struct message_buf
{
  long mtype; // first field of the message struct should be the message type
  message_payload payload;
};

typedef struct message_buf message_buf;

#endif

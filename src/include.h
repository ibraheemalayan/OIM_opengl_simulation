
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

#define UISIG 7

enum MsgType
{
  Enter,
  Update,
  Exit,
};

enum Gender
{
  Male,
  Female
};

enum Location
{
  MaleOutsideGatesArea,     // 0
  FemaleOutsideGatesArea,   // 1
  MaleMetalDetectorQueue,   // 2
  FemaleMetalDetectorQueue, // 3
  MetalDetector,            // 4
  InnerGroupingArea,        // 5
  Teller                    // teller 1 will be 6, teller 2 will be 7 and so on
};

typedef enum Location Location;
typedef enum Gender gender;
typedef enum MsgType MsgType;

struct message
{
  MsgType msg_type;
  int person_pid;
  float angriness;
  gender gender;
  int index_in_queue; // index if inside a queue
  Location current_location;
};

#endif

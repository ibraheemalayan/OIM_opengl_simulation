#ifndef __UI_GLOBALS_H_
#define __UI_GLOBALS_H_

#include "./structs.h"

Queue *queue_A1, *queue_A2;

Person *people[500];

int people_count = 300;

int simulation_finished = 0;

double rolling_gate_rotation = 0;

#endif

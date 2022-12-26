#ifndef __UI_HELPER_H_
#define __UI_HELPER_H_

#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include "../include.h"
#include "../std.h"
#include "./structs.h"
#include "./globals.h"
#include "./constants.h"
#include "./shapes.h"

Person *create_person(int id, int index, gender gen, float angriess, Queue *current_queue);
Coordinates get_queue_location_coords_for_index(Queue *queue, int index);
Coordinates get_queue_location_coords_for_next(Queue *queue);
void update_person_location(Person *person);
void draw_people_in_queues();
void draw_queues();
void setup_message_queue();

Person *create_person(int id, int index, gender gen, float angriess, Queue *current_queue)
{
    Person *person = (Person *)malloc(sizeof(Person));

    person->id = id;
    person->index_in_queue = index;
    person->gender = gen;
    person->current_queue = current_queue;
    person->current_coords.x = -1500;
    person->current_coords.y = 0;
    person->angriess = angriess;

    return person;
}

// TODO read values from config file
void initialize_queues(
    Queue *queue_A1,
    Queue *queue_A2,
    Queue *queue_B1,
    Queue *queue_B2)
{
    queue_A1->coords.x = QUEUE_A1_X_VALUE;
    queue_A1->coords.y = QUEUE_A1_Y_VALUE;
    queue_A1->width = QUEUE_A1_WIDTH;
    queue_A1->height = QUEUE_A1_HEIGHT;
    queue_A1->current_people = 0;

    queue_A2->coords.x = QUEUE_A2_X_VALUE;
    queue_A2->coords.y = QUEUE_A2_Y_VALUE;
    queue_A2->width = QUEUE_A2_WIDTH;
    queue_A2->height = QUEUE_A2_HEIGHT;
    queue_A2->current_people = 0;

    queue_B1->coords.x = QUEUE_B_X_VALUE;
    queue_B1->coords.y = QUEUE_B1_Y_VALUE;
    queue_B1->width = QUEUE_B_WIDTH;
    queue_B1->height = QUEUE_B_HEIGHT;
    queue_B1->current_people = 0;

    queue_B2->coords.x = QUEUE_B_X_VALUE;
    queue_B2->coords.y = QUEUE_B2_Y_VALUE;
    queue_B2->width = QUEUE_B_WIDTH;
    queue_B2->height = QUEUE_B_HEIGHT;
    queue_B2->current_people = 0;
}

Coordinates get_queue_location_coords_for_next(Queue *queue)
{
    return get_queue_location_coords_for_index(queue, queue->current_people);
}

Coordinates get_queue_location_coords_for_index(Queue *queue, int index)
{

    int max_people_per_row = queue->width / PADDING_BETWEEN_PEOPLE;
    int row = index / max_people_per_row;
    int column = index % max_people_per_row;

    Coordinates coords;

    coords.y = queue->coords.y + 30 + row * PADDING_BETWEEN_PEOPLE;
    coords.x = queue->coords.x + 30 + column * PADDING_BETWEEN_PEOPLE;

    return coords;
}

void update_person_location(Person *person)
{

    // update X coordinates
    if (person->current_coords.x != person->destination_coords.x)
    {

        float remaing_distance = person->current_coords.x - person->destination_coords.x;

        if ((remaing_distance < STEP_SIZE && remaing_distance > 0) || (remaing_distance > -STEP_SIZE && remaing_distance < 0))
        {
            person->current_coords.x = person->destination_coords.x;
        }
        else
        {
            person->current_coords.x += (remaing_distance > 0) ? -STEP_SIZE : STEP_SIZE;
        }
    }
    // update Y coordinates
    if (person->current_coords.y != person->destination_coords.y)
    {
        float remaing_distance = person->current_coords.y - person->destination_coords.y;

        if ((remaing_distance < STEP_SIZE / 2 && remaing_distance > 0) || (remaing_distance > -STEP_SIZE / 2 && remaing_distance < 0))
        {
            person->current_coords.y = person->destination_coords.y;
        }
        else
        {
            person->current_coords.y += (remaing_distance > 0) ? -STEP_SIZE / 2 : STEP_SIZE / 2;
        }
    }
}

void draw_queues()
{
    draw_rectangle(QUEUE_A1_X_VALUE, QUEUE_A1_Y_VALUE, QUEUE_A1_WIDTH, QUEUE_A1_HEIGHT, 220, 220, 220);
    draw_rectangle(QUEUE_A2_X_VALUE, QUEUE_A2_Y_VALUE, QUEUE_A2_WIDTH, QUEUE_A2_HEIGHT, 220, 220, 220);
    draw_rectangle(QUEUE_B_X_VALUE, QUEUE_B1_Y_VALUE, QUEUE_B_WIDTH, QUEUE_B_HEIGHT, 220, 220, 220);
    draw_rectangle(QUEUE_B_X_VALUE, QUEUE_B2_Y_VALUE, QUEUE_B_WIDTH, QUEUE_B_HEIGHT, 220, 220, 220);
}

void print_message(message_payload *buf)
{
    printf("{\n\tmsg_type: %ld", buf->msg_type);
    printf("\n\tperson_pid: %d", buf->person_pid);
    printf("\n\tangriness: %f", buf->angriness);
    printf("\n\tgender: %i", buf->gender);
    printf("\n\tindex_in_queue: %i", buf->index_in_queue);
    printf("\n\tcurrent_location: %i\n}\n", buf->current_location);
}

Queue *get_proper_queue_pointer(Location current_location)
{
    switch (current_location)
    {
    case MaleOutsideGatesArea:
        return queue_A1;
    case FemaleOutsideGatesArea:
        return queue_A2;
    case MaleMetalDetectorQueue:
        return queue_B1;
    case FemaleMetalDetectorQueue:
        return queue_B2;
    default:
        break;
    }
    return NULL;
}

#endif

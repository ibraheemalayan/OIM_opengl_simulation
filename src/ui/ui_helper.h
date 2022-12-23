#ifndef __UI_HELPER_H_
#define __UI_HELPER_H_

#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include "../include.h"
#include "../std.h"
#include "./structs.h"
#include "./constants.h"
#include "./shapes.h"

Queue *queue_A1, *queue_A2;

Person *create_person(int id, gender gen, float angriess);
void add_to_queue_A(Person *person);

Person *create_person(int id, gender gen, float angriess)
{
    Person *person = (Person *)malloc(sizeof(Person));

    person->id = id;
    person->gender = gen;
    person->current_coords.x = -1500;
    person->current_coords.y = 0;
    person->angriess = angriess;

    return person;
}

void initialize_queues(
    Queue *queue_A1,
    Queue *queue_A2)
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
}

Coordinates get_queue_location_coords(Queue *queue, int index)
{

    int max_people_per_row = queue->width / PADDING_BETWEEN_PEOPLE;
    int row = index / max_people_per_row;
    int column = index % max_people_per_row;

    Coordinates coords;

    coords.y = queue->coords.y + 30 + row * PADDING_BETWEEN_PEOPLE;
    coords.x = queue->coords.x + 30 + column * PADDING_BETWEEN_PEOPLE;

    return coords;
}

void draw_people_in_queues(int people)
{
    for (size_t i = 0; i < people; i++)
    {
        Person *person = create_person(i, i % 2, ((float)(i % 8)) * 0.1);
        Queue *q_ptr = (person->gender == Male) ? queue_A1 : queue_A2;
        person->current_coords = get_queue_location_coords(q_ptr, i);
        draw_person(person);
    }
}
void draw_queues()
{
    draw_rectangle(QUEUE_A1_X_VALUE, QUEUE_A1_Y_VALUE, QUEUE_A1_WIDTH, QUEUE_A1_HEIGHT, 220, 220, 220);
    draw_rectangle(QUEUE_A2_X_VALUE, QUEUE_A2_Y_VALUE, QUEUE_A2_WIDTH, QUEUE_A2_HEIGHT, 220, 220, 220);
}

#endif

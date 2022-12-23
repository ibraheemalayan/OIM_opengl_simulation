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
Coordinates get_queue_location_coords_for_index(Queue *queue, int index);
Coordinates get_queue_location_coords_for_next(Queue *queue);
void draw_people_in_queues(int people);
void draw_queues();

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

// TODO read values from config file
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

void draw_people_in_queues(int people)
{

    // FIXME: calling the display func twice causes current_people to continue instead of reset without those
    queue_A1->current_people = 0;
    queue_A2->current_people = 0;

    for (size_t i = 0; i < people; i++)
    {

        Person *person = create_person(i, rand() % 2, ((float)(rand() % 8)) * 0.1);
        Queue *q_ptr = (person->gender == Male) ? queue_A1 : queue_A2;

        person->current_coords = get_queue_location_coords_for_next(q_ptr);
        q_ptr->current_people += 1;

        draw_person(person);
    }
}
void draw_queues()
{
    draw_rectangle(QUEUE_A1_X_VALUE, QUEUE_A1_Y_VALUE, QUEUE_A1_WIDTH, QUEUE_A1_HEIGHT, 220, 220, 220);
    draw_rectangle(QUEUE_A2_X_VALUE, QUEUE_A2_Y_VALUE, QUEUE_A2_WIDTH, QUEUE_A2_HEIGHT, 220, 220, 220);
}

#endif

#ifndef __UI_STRUCTS_H_
#define __UI_STRUCTS_H_

struct Coordinations
{
    float x;
    float y;
};

typedef struct Coordinations Coordinates;

struct Queue
{
    Coordinates coords;
    int current_people;
    float width;
    float height;
};

typedef struct Queue Queue;

struct Person
{
    int id;
    Coordinates current_coords;
    Coordinates destination_coords;
    float angriess; // current waited time out of max patience
    float speed;
    gender gender;
    int index_in_queue;
    Queue *current_queue;
};
typedef struct Person Person;

#endif

#ifndef __UI_STRUCTS_H_
#define __UI_STRUCTS_H_

enum gender
{
    Male,
    Female
};

typedef enum gender gender;

struct Coordinations
{
    float x;
    float y;
};

typedef struct Coordinations Coordinates;

struct Person
{
    int id;
    Coordinates current_coords;
    Coordinates destination_coords;
    float angriess; // current waited time out of max patience
    float speed;
    gender gender;
};
typedef struct Person Person;

struct Queue
{
    Coordinates coords;
    int current_people;
    float width;
    float height;
};

typedef struct Queue Queue;

#endif

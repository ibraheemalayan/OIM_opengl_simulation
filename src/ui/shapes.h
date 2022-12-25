#ifndef __UI_SHAPES_H_
#define __UI_SHAPES_H_

#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include "../include.h"
#include "../std.h"
#include "./structs.h"

void reshape(int, int);
void background();
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius, int R, int G, int B);
void draw_rectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, int R, int G, int B);
void draw_person(Person *p);
void draw_rolling_gate(GLfloat x, GLfloat y);

/*
 * Function that handles the drawing of a circle using the triangle fan
 * method. This will create a filled circle.
 *
 * Params:
 *	x (GLFloat) - the x position of the center point of the circle
 *	y (GLFloat) - the y position of the center point of the circle
 *	radius (GLFloat) - the radius that the painted circle will have
 */
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius, int R, int G, int B)
{
    int i;
    int triangleAmount = 30; // # of triangles used to draw circle

    // GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * M_PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(R, G, B);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
}

void draw_person(Person *p)
{

    if (p->gender == Male)
    {
        glBegin(GL_TRIANGLES);
        glColor3ub(255 * p->angriess, 0, 0);
        glVertex2f(p->current_coords.x + 15, p->current_coords.y - 15);
        glVertex2f(p->current_coords.x - 15, p->current_coords.y - 15);
        glVertex2f(p->current_coords.x, p->current_coords.y + 15);
        glEnd();
    }
    else
    {
        drawFilledCircle(p->current_coords.x, p->current_coords.y, 15, 255 * p->angriess, 0, 0);
    }
};

void draw_rectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, int R, int G, int B)
{
    glBegin(GL_QUADS);
    glColor3ub(R, G, B);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void draw_walls()
{
    int R = 100, G = 0, B = 100;

    float wall_thickness = ROLLING_GATE_SIZE / 10;
    float wall_x = ROLLING_GATES_X - wall_thickness / 2;

    float gate_1_top = ROLLING_GATES_Y + ROLLING_GATE_SIZE / 2;
    draw_rectangle(wall_x, gate_1_top, wall_thickness, 500 - gate_1_top, R, G, B);

    float gate_2_bottom = -ROLLING_GATES_Y - ROLLING_GATE_SIZE / 2;
    draw_rectangle(wall_x, gate_2_bottom, wall_thickness, -500 + gate_1_top, R, G, B);

    float gate_1_bottom_y = ROLLING_GATES_Y - ROLLING_GATE_SIZE / 2;
    float gate_2_top_y = -ROLLING_GATES_Y + ROLLING_GATE_SIZE / 2;

    draw_rectangle(wall_x, gate_2_top_y, wall_thickness, gate_1_bottom_y - gate_2_top_y, R, G, B);

    // middle wall
    draw_rectangle(wall_x, 0, -500, wall_thickness, R, G, B);
}

void draw_rolling_gate(GLfloat x, GLfloat y)
{
    float height = ROLLING_GATE_SIZE, width = ROLLING_GATE_SIZE, thickness = ROLLING_GATE_SIZE / 10;

    glPushMatrix();

    float x_translate = x;
    float y_translate = y;

    glTranslatef(x_translate, y_translate, 0); // move the Z axis to the center of the gate

    glRotatef(rolling_gate_rotation, 0, 0, 1); // set the rotation to be aroung the Z axis

    glTranslatef(-x_translate, -y_translate, 0); // move the Z axis back to the original position

    glBegin(GL_QUADS);
    glColor3ub(0, 20, 0);
    glVertex2f(x - thickness / 2, y - height / 2);
    glVertex2f(x + thickness / 2, y - height / 2);
    glVertex2f(x + thickness / 2, y + height / 2);
    glVertex2f(x - thickness / 2, y + height / 2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0, 20, 0);
    glVertex2f(x - height / 2, y - thickness / 2);
    glVertex2f(x + height / 2, y - thickness / 2);
    glVertex2f(x + height / 2, y + thickness / 2);
    glVertex2f(x - height / 2, y + thickness / 2);
    glEnd();

    glPopMatrix();
};

void reshape(int width, int height)
{

    // regardless the width & the height, do not change the viewport

    glViewport(0, 0, 1750, 700);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1250, 1250, -500, 500); // left, right, bottom, top

    glMatrixMode(GL_MODELVIEW);
}

void background()
{
    glClearColor(0.95, 0.95, 0.95, 1.0);
}

#endif

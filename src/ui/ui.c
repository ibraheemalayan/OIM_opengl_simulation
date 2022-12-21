#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include "../include.h"
#include "../std.h"

#define QUEUE_1_Y_VALUE 2
#define QUEUE_2_Y_VALUE -2

#define RIGHT_DIRECTION 1
#define LEFT_DIRECTION -1

void paint_and_swap_frame();
void background();
void reshape(int, int);

void draw_person(float x, float y, float size, int R, int G, int B, int gender);

void recursive_timed_update(int time);

// void draw_palestine_flag();
void validate_args(int argc, char *argv[]);


/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void paint_and_swap_frame()
{

    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)
    glLoadIdentity();             // reset disply

    // Draw Palestine flage
    // draw_palestine_flag();

    // draw_person(team_1_x, QUEUE_1_Y_VALUE, 0.5, 0, 0, 255, 1);
    glutSwapBuffers(); // Swap the buffers (replace current frame with the new one)
}

void background()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
}


void exit_trigger(int sig)
{
    printf("Exiting...\n");
    exit(0);
}


void reshape(int w, int h)
{
    // ViewPort
    glViewport(0, 0, 800, 400);

    // Projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-14, 10, -5, 5); // FIXME left, right, bottom, top change to 100
    glMatrixMode(GL_MODELVIEW);
}


/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv)
{

    printf("Starting UI...\n");
    // srand(time(NULL)); // initialize random seed

    setup_signals(); // does nothing in standalone mode

    // open_pipes();              // does nothing in standalone mode
    validate_args(argc, argv); // does nothing in standalone mode

    glutInit(&argc, argv);                       // Initialize GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // for animation

    glutInitWindowSize(800, 400);          // Set the window's initial width & height
    glutInitWindowPosition(50, 50);        // Position the window's initial top-left corner
    glutCreateWindow("Free Palestine ");   // Create a window with the given title
    glutDisplayFunc(paint_and_swap_frame);              // Register display callback handler for window re-paint
    glutReshapeFunc(reshape);              // Static display
    glutTimerFunc(0, recursive_timed_update, 0); // Call function after specified amount of time

    background();                          // Background color

    glutMainLoop();                        // Enter the event-processing loop
    
    return 0;
}
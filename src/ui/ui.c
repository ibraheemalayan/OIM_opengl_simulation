#include "./ui_helper.h"
#include "./structs.h"

void paint_and_swap_frame();
void background();

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

    // Draw the queues
    draw_queues();

    draw_people_in_queues(321);

    glutSwapBuffers(); // Swap the buffers (replace current frame with the new one)
}

void validate_args(int argc, char *argv[])
{
}

void recursive_timed_update(int time)
{
    // pass
}

void setup_ui(int argc, char **argv)
{

    glutInit(&argc, argv);                       // Initialize GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // for animation

    glutInitWindowSize(1750, 700);               // Set the window's initial width & height
    glutInitWindowPosition(0, 0);                // Position the window's initial top-left corner of the screen
    glutCreateWindow("OIM Simulation");          // Create a window with the given title
    glutDisplayFunc(paint_and_swap_frame);       // Register display callback handler for window re-paint
    glutReshapeFunc(reshape);                    // Static display
    glutTimerFunc(0, recursive_timed_update, 0); // Call function after specified amount of time

    background(); // Background color
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv)
{

    printf("Starting UI...\n");

    srand(time(NULL)); // initialize random seed

    // setup_signals(); // does nothing in standalone mode

    // open_pipes();              // does nothing in standalone mode
    validate_args(argc, argv); // does nothing in standalone mode

    setup_ui(argc, argv);

    queue_A1 = (Queue *)malloc(sizeof(Queue));
    queue_A2 = (Queue *)malloc(sizeof(Queue));

    initialize_queues(queue_A1, queue_A2);

    glutMainLoop(); // Enter the event-processing loop

    return 0;
}
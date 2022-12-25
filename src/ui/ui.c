#include "./ui_helper.h"
#include "./structs.h"
#include "./globals.h"

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

    draw_walls();

    draw_rolling_gate(ROLLING_GATES_X, ROLLING_GATES_Y);
    draw_rolling_gate(ROLLING_GATES_X, -ROLLING_GATES_Y);

    // draw_rolling_gate(0, -100);

    draw_people_in_queues();

    glutSwapBuffers(); // Swap the buffers (replace current frame with the new one)
}

void validate_args(int argc, char *argv[])
{
}

void recursive_timed_update(int time)
{
    if (!simulation_finished)
    {
        glutTimerFunc(1000 / FPS, recursive_timed_update, 0);
    }
    glutPostRedisplay(); // marks the current window as needing to be redisplayed

    for (int i = 0; i < people_count; i++)
    {
        update_person_location(people[i]);
    }

    rolling_gate_rotation += ROLLING_GATE_DEGREE_PER_FRAME;
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

void create_people()
{

    for (int i = 0; i < people_count; i++)
    {

        gender g = (rand() % 2) ? Male : Female;
        Queue *q = (g == Male) ? queue_A1 : queue_A2;

        people[i] = create_person(i, q->current_people, g, ((float)(rand() % 8)) * 0.1, q);

        people[i]->destination_coords = get_queue_location_coords_for_index(q, people[i]->index_in_queue);

        q->current_people++;
    }
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

    create_people();

    glutMainLoop(); // Enter the event-processing loop

    return 0;
}
#include "local.h"
#include "../include.h"

void setup_message_queue();
void read_mock_messages();

message buf;
int msg_q_id;

void print_message(message *msg)
{
    printf("{\n\tmsg_type: %d", buf.msg_type);
    printf("\n\tperson_pid: %d", buf.person_pid);
    printf("\n\tangriness: %f", buf.angriness);
    printf("\n\tgender: %i", buf.gender);
    printf("\n\tindex_in_queue: %i", buf.index_in_queue);
    printf("\n\tcurrent_location: %i\n}\n", buf.current_location);
}

void setup_message_queue()
{

    key_t key;

    if ((key = ftok("msgq.txt", 'B')) == -1)
    {
        perror("ftok, queue not found");
        exit(1);
    }

    msg_q_id = msgget(key, 0);
    if (msg_q_id == -1)
    {
        perror("msgget, error getting queue");
        exit(2);
    }

    printf("\n\nmessage queue: ready to read messages.\n");
}

void read_mock_messages()
{

    // msg_type set to Zero to read the first message in the queue regarless of it its type
    if (msgrcv(msg_q_id, &buf, sizeof(buf), 0, IPC_NOWAIT) == -1)
    {
        if (errno == ENOMSG)
        {
            printf("No messages in the queue\n");
            return;
        }

        // if the error is not ENOMSG, then it is an error
        perror("msgrcv");
        exit(3);
    }

    printf("received message:\n\n");
    print_message(&buf);
}

int main()
{
    setup_message_queue();
    read_mock_messages();
    return 0;
}
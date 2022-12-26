#include "local.h"
#include "../include.h"

void create_and_setup_message_queue();
void write_mock_messages();
void clean_queues();

message buf;
int msg_q_id;

void create_and_setup_message_queue()
{

    key_t key;

    // remove queue if exists
    remove("msgq.txt");

    // create file to use as message queue key
    system("touch msgq.txt");
    system("chmod 666 msgq.txt");

    if ((key = ftok("msgq.txt", 'B')) == -1)
    {
        perror("ftok");
        exit(1);
    }

    msg_q_id = msgget(key, 0666 | IPC_CREAT);
    if (msg_q_id == -1)
    {
        perror("msgget");
        exit(2);
    }

    struct msqid_ds queue_info;
    // read existing message queue info into queue_info
    if (msgctl(msg_q_id, IPC_STAT, &queue_info) == -1)
    {
        perror("Can not read message queue info");
        exit(5);
    }
    printf("Last sent: %s", ctime(&queue_info.msg_stime));
    printf("Last recv: %s", ctime(&queue_info.msg_rtime));
    printf("Last change: %s", ctime(&queue_info.msg_ctime));
    printf("Messages in queue: %ld\n", queue_info.msg_qnum);
    printf("PID of last sender: %d\n", queue_info.msg_lspid);
    printf("PID of last receiver: %d\n", queue_info.msg_lrpid);
    printf("PID of this process: %d\n\n", getpid());

    queue_info.msg_qbytes = 10240;

    // increase buffer size
    msgctl(msg_q_id, IPC_SET, &queue_info);

    printf("message queue: ready to send messages.\n");
}

void write_mock_messages()
{
    buf.msg_type = PersonEntered;
    buf.person_pid = 1234;
    buf.angriness = 0.2;
    buf.gender = Male;
    buf.index_in_queue = 30;
    buf.current_location = MaleOutsideGatesArea;

    if (msgsnd(msg_q_id, &buf, sizeof(buf), 0) == -1)
    {
        perror("msgsnd");
        exit(3);
    }

    buf.msg_type = PersonEntered;
    buf.person_pid = 1235;
    buf.angriness = 0.5;
    buf.gender = Male;
    buf.index_in_queue = 25;
    buf.current_location = MaleOutsideGatesArea;

    if (msgsnd(msg_q_id, &buf, sizeof(buf), 0) == -1)
    {
        perror("msgsnd");
        exit(4);
    }
}

void clean_queues()
{
    // remove the message queue from the System V IPC
    msgctl(msg_q_id, IPC_RMID, NULL);

    // remove the queue file
    remove("msgq.txt");
}

static void interrupt_sig_handler(int sig)
{
    red_stdout();
    printf("\n\nInterrupt signal received, cleaning up queues.\n");
    clean_queues();
    reset_stdout();
    exit(0);
}

int main()
{

    create_and_setup_message_queue();

    // register signal handler for SIGINT to clean up
    signal(SIGINT, interrupt_sig_handler);

    // sleep(10);

    write_mock_messages();

    pause();

    clean_queues();
    return 0;
}
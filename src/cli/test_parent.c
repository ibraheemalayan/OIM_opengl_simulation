#include "local.h"
#include "../include.h"

void create_and_setup_message_queue();
void write_mock_messages();
void clean_queues();

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

    message_buf buf;

    buf.mtype = PERSON;

    int male_queue_ind = 0;
    int female_queue_ind = 0;

    buf.payload.msg_type = PersonEntered;
    buf.payload.person_pid = 1234;
    buf.payload.angriness = 0.2;
    buf.payload.gender = Male;
    buf.payload.index_in_queue = male_queue_ind++;
    buf.payload.current_location = MaleOutsideGatesArea;

    if (msgsnd(msg_q_id, &buf, sizeof(buf) - +sizeof(MsgType), 0) == -1)
    {
        perror("msgsnd");
        exit(3);
    }

    sleep(1);

    buf.payload.msg_type = PersonEntered;
    buf.payload.person_pid = 1235;
    buf.payload.angriness = 0.5;
    buf.payload.gender = Male;
    buf.payload.index_in_queue = male_queue_ind++;
    buf.payload.current_location = MaleOutsideGatesArea;

    if (msgsnd(msg_q_id, &buf, sizeof(buf) - +sizeof(MsgType), 0) == -1)
    {
        perror("msgsnd");
        exit(4);
    }

    sleep(1);

    buf.payload.msg_type = PersonEntered;
    buf.payload.person_pid = 1236;
    buf.payload.angriness = 0.8;
    buf.payload.gender = Female;
    buf.payload.index_in_queue = female_queue_ind++;
    buf.payload.current_location = FemaleOutsideGatesArea;

    if (msgsnd(msg_q_id, &buf, sizeof(buf) - +sizeof(MsgType), 0) == -1)
    {
        perror("msgsnd");
        exit(4);
    }

    sleep(1);

    buf.payload.msg_type = PersonEntered;
    buf.payload.person_pid = 123;
    buf.payload.angriness = 0.1;
    buf.payload.gender = Male;
    buf.payload.index_in_queue = male_queue_ind++;
    buf.payload.current_location = MaleOutsideGatesArea;

    if (msgsnd(msg_q_id, &buf, sizeof(buf) - +sizeof(MsgType), 0) == -1)
    {
        perror("msgsnd");
        exit(4);
    }

    sleep(2);

    buf.payload.msg_type = PersonUpdated;
    buf.payload.person_pid = 123;
    buf.payload.angriness = 0.9;
    buf.payload.gender = Male;
    buf.payload.index_in_queue = male_queue_ind++;
    buf.payload.current_location = MaleOutsideGatesArea;

    if (msgsnd(msg_q_id, &buf, sizeof(buf) + sizeof(MsgType), 0) == -1)
    {
        perror("msgsnd");
        exit(4);
    }

    sleep(3);

    buf.payload.msg_type = PersonUpdated;
    buf.payload.person_pid = 123;
    buf.payload.angriness = 0.9;
    buf.payload.gender = Male;
    buf.payload.index_in_queue = 2;
    buf.payload.current_location = MaleMetalDetectorQueue;

    if (msgsnd(msg_q_id, &buf, sizeof(buf) + sizeof(MsgType), 0) == -1)
    {
        perror("msgsnd");
        exit(4);
    }

    sleep(1);

    buf.payload.msg_type = PersonEntered;
    buf.payload.person_pid = 124;
    buf.payload.angriness = 0.9;
    buf.payload.gender = Male;
    buf.payload.index_in_queue = male_queue_ind++;
    buf.payload.current_location = MaleOutsideGatesArea;

    if (msgsnd(msg_q_id, &buf, sizeof(buf) + sizeof(MsgType), 0) == -1)
    {
        perror("msgsnd");
        exit(4);
    }

    sleep(1);

    buf.payload.msg_type = PersonEntered;
    buf.payload.person_pid = 125;
    buf.payload.angriness = 1.0;
    buf.payload.gender = Female;
    buf.payload.index_in_queue = female_queue_ind++;
    buf.payload.current_location = FemaleOutsideGatesArea;

    if (msgsnd(msg_q_id, &buf, sizeof(buf) + sizeof(MsgType), 0) == -1)
    {
        perror("msgsnd");
        exit(4);
    }

    sleep(1);

    int exiter_index = male_queue_ind++;

    buf.payload.msg_type = PersonEntered;
    buf.payload.person_pid = 126;
    buf.payload.angriness = 0.5;
    buf.payload.gender = Male;
    buf.payload.index_in_queue = exiter_index;
    buf.payload.current_location = MaleOutsideGatesArea;

    if (msgsnd(msg_q_id, &buf, sizeof(buf) + sizeof(MsgType), 0) == -1)
    {
        perror("msgsnd");
        exit(4);
    }

    sleep(2);

    buf.payload.msg_type = PersonExited;
    buf.payload.person_pid = 126;
    buf.payload.angriness = 0.5;
    buf.payload.gender = Male;
    buf.payload.index_in_queue = exiter_index;
    buf.payload.current_location = MaleOutsideGatesArea;

    if (msgsnd(msg_q_id, &buf, sizeof(buf) + sizeof(MsgType), 0) == -1)
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
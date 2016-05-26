#include<stdio.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#define MAX 100

struct msgbuf
{
long mtype;
char text[MAX];
};

int main()
{
struct msgbuf my_data;
int msgid;
msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
if(msgid == -1)
{
printf("Error\n");
}
printf("Enter some text\n");
fgets(my_data.text, MAX, stdin);

if(msgsnd(msgid, (void*)&my_data, MAX, 0)==-1)
{
printf("Error\n");
}

return 0;
}

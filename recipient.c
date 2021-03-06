#include<time.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX 100

struct msgbuf
{
long mtype;
char text[MAX];
};

int foo(struct msgbuf *my_data)
{
int i=0;
for(i;i<5;++i)  
{
if(my_data->text[i]<0 || my_data->text[i]>256)
{
return 0;
}
else if((my_data->text[0]<65 || (my_data->text[0]>90 && my_data->text[0]<97) || my_data->text[0]>122))
{
return 0;
}
}

return 1;
}

int main()
{
struct msgbuf my_data;
int msgid;
long int to_receive = 0;
msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

if(msgid == -1)
{
printf("Error\n");
return -1;
}

if(msgrcv(msgid, (void*)&my_data, MAX, to_receive, 0) == -1)
{
printf("Error");
return -1;
}

printf("Hi, I'm a tester. I received a communicate. I'll check now, if it is written in right way.\n\n");

printf("I received a message \"%s\"", my_data.text); 

time_t t = time(NULL);
struct tm* lt = localtime(&t);

if(lt->tm_wday>0 && lt->tm_wday<5)
{
printf("Sorry but I read messages only at the weekend!\n");
return -1;
}

else
{
int x = foo(&my_data);
if(msgctl(msgid, IPC_RMID, 0) == -1 || x==0)
{
printf("System error, or wrong type of message\n");
return -1;
}
int file = open("word.data", O_CREAT|O_RDWR, 0666);
if(file==-1)
printf("Could not create a file");
else
file = write(file, my_data.text, sizeof(((struct msgbuf*)0)->text)); //Zapisanie do pliku w celu sprawdzenia przez aspell
close(file);
}
}

return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    pid_t pid = getpid();
    pid_t pid_1;
    pid_t pid_2;

    char *arg1 = "lab1-2";
    char *arg2 = "photo.jpeg";
    char *arg3 = "photo_.jpeg";
    char arg4[21];
    sprintf(arg4,"pid: %d",pid);
    char *arg5 = NULL;
    char *arg_[] = {arg1, arg2, arg3, arg4, arg5};

    //创建两个子进程
    if ((pid_1 = fork()) == 0)
    {
        char *arg3_1 = "photo_1.jpeg";
        char arg4_1[21];
        sprintf(arg4_1, "pid: %d",getpid());
        char *arg_1[] = {arg1, arg2, arg3_1, arg4_1, arg5};
        execv("./lab1-2",arg_1);
    }
    else
    {
        if ((pid_2 = fork()) == 0)
        {   
            char *arg3_2 = "photo_2.jpeg";
            char arg4_2[21];
            sprintf(arg4_2, "pid: %d",getpid());
            char *arg_2[] = {arg1, arg2, arg3_2, arg4_2, arg5};
            execv("./lab1-2",arg_2);
        }
    }
    execv("./lab1-2",arg_);

    return 0;
}
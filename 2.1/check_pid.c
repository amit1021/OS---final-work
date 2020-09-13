#include <stdio.h>
#include "errno.h"
#include<stdlib.h> 
#include<signal.h> 
#include<sys/types.h> 



int main(int argc,char* argv[])
{
    if(argc != 2){
        printf("Invalid input\n");
        return 0;
    }
    pid_t pid = atoi (argv[1]); // get pid from the user and convert to int

    if (kill(pid, 0) < 0) // send signal 0, return if the process exists
    {
        if (errno == ESRCH)
        {
            printf("Process %d does not exist\n", pid);
        }
        if (errno == EPERM)
        {
            printf("Process %d exists but we have no permission\n", pid);
        }
    }
    else
    {
        printf("Process %d exists\n", pid);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int counter = 0;
//get signal SIGINT and count the signals
void my_handler_SIGINT(int signum)
{
    counter++;
}
//get signal SIGUSR and print the number of SIGINT signals that sent
void my_handler_SIGUSR1(int signum)
{
    printf("%d \n", counter);
}

int main()
{
    // print the pid of this process
    printf("PID: %d\n", getpid());
    while (1)
    {
        // recive SIGINT
        signal(SIGINT, my_handler_SIGINT);
        // recive SIGUSR
        signal(SIGUSR1, my_handler_SIGUSR1);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    // check if have all the argument
    if (argc != 4)
    {
        printf("Invalid argument\n");
        return 0;
    }

    pid_t pid = atoi(argv[1]);
    int SIGNAL = atoi(argv[2]);
    int num_signals = atoi(argv[3]);
    // check if the process is exists
    if (kill(pid, 0) == -1)
    {
        printf("The procces is not exists\n");
        return 0;
    }

    // sent SIGINT
    if (SIGNAL == 2)
    {
        int i = 0;
        // sent kill num_signals times
        while (i++ < num_signals)
        {
            kill(pid, SIGINT);
        }
    }
    //sent SIGUSR
    else if (SIGNAL == 10)
    {
        int i = 0;
        // sent kill num_signals times
        while (i++ < num_signals)
        {
            kill(pid, SIGUSR1);
            usleep(10);
        }
        // kill the proccess
        kill(pid, SIGKILL);
    }
    else
    {
        printf("This signal is not acceptable\n");
        return 0;
    }
}

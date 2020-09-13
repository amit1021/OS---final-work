#define _GNU_SOURCE

#include <stdio.h>
#include "errno.h"
#include <stdlib.h>
#include <signal.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/sched.h>


//struct for SCHED_DEADLINE
struct sched_attr {
	__u32 size;

	__u32 sched_policy;
	__u64 sched_flags;

	// /* SCHED_NORMAL, SCHED_BATCH */
	 __s32 sched_nice;

	// /* SCHED_FIFO, SCHED_RR */
	 __u32 sched_priority;

	/* SCHED_DEADLINE (nsec) */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
 };

 int sched_setattr(pid_t pid,
		  const struct sched_attr *attr,
		  unsigned int flags)
 {
	return syscall(__NR_sched_setattr, pid, attr, flags);
 }

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid input\n");
        return 0;
    }

    printf("pid : %d\n", getpid());
    usleep(10000000);

    int SCHED = atoi(argv[1]);
    int priority = atoi(argv[2]);

    struct sched_param sp = {.sched_priority = priority};

    //SCHED_OTHER 0, SCHED_IDLE 5
    if (SCHED == SCHED_OTHER || SCHED == SCHED_IDLE)
    {
        // the priority in this case can be just 0
        if (priority != 0)
        {
            printf("Priority not good\n");
            return 0;
        }
        // pid = 0 the sched_setscheduler() function will act on the calling process.
        if (sched_setscheduler(0, SCHED, &sp) != 0)
        // If sched_setscheduler != 0 , the function faild
        {
            printf("Not success\n");
            return 0;
        }
    }
    // SCHED_DEADLINE 6
    else if (SCHED == SCHED_DEADLINE)
    {
        struct sched_attr attr; // Struct
        unsigned long int flags = 0;

        attr.size = sizeof(attr);
        attr.sched_flags = 0;
        attr.sched_nice = 0;
        // The priority in this case can be just 0
        if (priority != 0)
        {
            printf("Priority not good\n");
            return 0;
        }
        // set priority
        attr.sched_priority = priority;

        attr.sched_policy = SCHED_DEADLINE;
        attr.sched_runtime = 10 * 1000 * 1000;
        attr.sched_period = attr.sched_deadline = 30 * 1000 * 1000;
        // The function get pid, struct and flag
        if (sched_setattr(0, &attr, flags) < 0)
        { //If sched_setscheduler < 0 , the function faild
            printf("Not success\n");
            return 0;
        }
    }
    //  SCHED_FIFO, SCHED_RR
    else if (SCHED == SCHED_RR || SCHED == SCHED_FIFO)
    { // The priority in this case 1 - 99
        if (priority < 1 || priority > 99)
        {
            printf("Priority not good\n");
            return 0;
        }
        // pid = 0 the sched_setscheduler() function will act on the calling process.
        if (sched_setscheduler(0, SCHED, &sp) < 0)
        { //If sched_setscheduler != 0 , the function faild
            printf("Not success\n");
            return 0;
        }
    }
    else
    {
        printf("Unexpected scheduler\n");
        return 0;
    }
    printf("To stop the procces type any char\n");
    getchar();
    return 0;
}

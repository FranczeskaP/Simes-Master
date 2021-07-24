#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>

static uint8_t schedulerCalled = 0u;

static void SchedulerCalled(int signum);

int main()
{
    signal(SIGALRM, SchedulerCalled);
    alarm(5);
    while(1)
    {
        if(1u == schedulerCalled)
        {
            schedulerCalled = 0u;
            printf("Scheduler called\n");
        }
        else
        {
            printf("Scheduler not called\n");
        }
        sleep(1);
    }

    return 0;
}


static void SchedulerCalled(int signum)
{
    schedulerCalled = 1u;
    alarm(5);
}

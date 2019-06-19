#include "types.h"
#include "user.h"

#define P_LOOP_CNT 0x01000000
#define C_LOOP_CNT 0x03000000

int n;

void do_parent(void)
{
    volatile int cnt = 0;
    volatile int tmp = 0;

    while(cnt < P_LOOP_CNT)
    {
        tmp += cnt;
        cnt ++;
    }
}


void do_child(void)
{
    volatile int cnt = 0;
    volatile int tmp = 0;

    while(cnt < C_LOOP_CNT)
    {
        tmp += cnt;
        cnt ++;
    }
  exit();
}

void example_test_code()
{
    int pid = 0;

    pid = fork();
    //printf(1,"Parentid is %d and childid is %d\n", getpid(), pid);
    if (pid < 0)
    {
        printf(1, "fork() failed!\n");
        exit();
    }
    else if (pid == 0) // child
    {
        //sleep(100);
        do_child();
    }
    else // parent
    {
        do_parent();
        if (wait() < 0)
        {
            printf(1, "wait() failed!\n");
        }
    }
	printf(1, "\n");
}




/*void example_test_code1()
{
    int pid = 0;
    int k =2;
    set_priority(getpid(), 1);
    for(int i=0; i <4 ; i++)
    {
    pid = fork();
    if (pid < 0)
    {
        printf(1, "fork() failed!\n");
        exit();
    }
    else if (pid == 0) // child
    {
        //sleep(100);
        set_priority(getpid(), k);
        k++;
        do_child();
        exit();
    }
    else // parent
    {
        //do_parent();
        if (wait() < 0)
        {
            printf(1, "wait() failed!\n");
        }
    }
    }   
    printf(1, "\n");
} */


void example_test_code1()
{
    int pid;
    set_priority(getpid(), 0);
    for(int i=0; i <5 ; i++)
    {
    pid = fork();
    if (pid == 0) // child
    {
        sleep(20);
        do_child();
    } else {
      printf(1, "proc %d created priority: %d\n", pid, i);
      set_priority(pid, i);
    }
    }
    while(wait()!= -1)
        set_priority(getpid(),0);
}




int
main(int argc, char *argv[])
{
    
    /* ---------------- start: add your test code ------------------- */
    /*printf(1,"enter 0 for RR policy and 1 for priority based scheduling"); */
     if (argv[1][0] == '0')
    {
        n = 0;
        printf(1, "\nSetting RR policy\n");
        enable_sched_trace(1);
        example_test_code();

    }
    else
    {
        n = 1;
        printf(1, "\n Setting scheduler to priority based\n");
        enable_sched_trace(1);
        if(argv[2][0] == '1')
        {
        example_test_code1();
        } else
        {
          example_test_code();  
        }
    }

    set_sched(n);


    /* ---------------- end: add your test code ------------------- */

    enable_sched_trace(0);
    
    exit();
}

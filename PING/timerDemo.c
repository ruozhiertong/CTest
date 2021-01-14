#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void signalHandler(int signo)
{
    switch (signo){
        case SIGALRM:
            printf("Caught the SIGALRM signal!\n");
            break;
   }
}

int main(int argc, char *argv[])
{
    signal(SIGALRM, signalHandler);

    //it_interval间隔时间。
    //it_value 第一次开始计时器的间隔时间，即第一次使用这个计时器延迟等待的时间。
    //如果it_interval 置为0 ，则只执行一次。 it_value置为0 不执行timmer。
    //settimer工作机制是，第一次先对it_value倒计时，
    //当it_value为零时触发信号，然后重置为it_interval，继续对it_value倒计时，一直这样循环下去。
    /*
     If it_value is non-zero, it indicates the time to the next timer expiration.
     If it_interval is non-zero, it specifies a value to be used in reloading
     it_value when the timer expires.  Setting it_value to 0 disables a timer.
     Setting it_interval to 0 causes a timer to be disabled after its next expi-
     ration (assuming it_value is non-zero).
     */
    struct itimerval new_value, old_value;
    new_value.it_value.tv_sec = 0;
    new_value.it_value.tv_usec = 1;
    new_value.it_interval.tv_sec = 0;
    new_value.it_interval.tv_usec = 200000;
    setitimer(ITIMER_REAL, &new_value, &old_value);
    
    for(;;);
     
    return 0;
}
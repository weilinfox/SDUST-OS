#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
void print_info(int signo) 
{ 
 printf("SIGPROF Timer fired\n"); //简单的打印，表示 timer 到期
} 

void init_sigaction(void) 
{ 
 struct sigaction act; 
 act.sa_handler= print_info; 
 act.sa_flags=0; 
 sigemptyset(&act.sa_mask); 
 sigaction(SIGPROF,&act,NULL); //设置信号 SIGPROF 的处理函数为 print_info
} 

void init_time() 
{ 
 struct itimerval value; 
 value.it_value.tv_sec=2; 
 value.it_value.tv_usec=0; 
 value.it_interval=value.it_value; 
 setitimer(ITIMER_PROF,&value,NULL); //初始化 timer，到期发送 SIGPROF 信号
} 

int main() 
{ 
 init_sigaction(); 
 init_time(); 
 while(1);
 return 0;
}

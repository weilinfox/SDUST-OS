#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
void print_info(int signo) 
{ 
 printf("SIGPROF Timer fired\n"); //�򵥵Ĵ�ӡ����ʾ timer ����
} 

void init_sigaction(void) 
{ 
 struct sigaction act; 
 act.sa_handler= print_info; 
 act.sa_flags=0; 
 sigemptyset(&act.sa_mask); 
 sigaction(SIGPROF,&act,NULL); //�����ź� SIGPROF �Ĵ�����Ϊ print_info
} 

void init_time() 
{ 
 struct itimerval value; 
 value.it_value.tv_sec=2; 
 value.it_value.tv_usec=0; 
 value.it_interval=value.it_value; 
 setitimer(ITIMER_PROF,&value,NULL); //��ʼ�� timer�����ڷ��� SIGPROF �ź�
} 

int main() 
{ 
 init_sigaction(); 
 init_time(); 
 while(1);
 return 0;
}

/*
*rwloc_test01~04�� �ֱ���Զ�д���ж�����д���Ķ���д˳�����
*��ע���ĸ��ļ��ж�д����ʹ��˳��
* usage: $ gcc -o rwloc_test04 rwloc_test04.c -lpthread
* usage:$ ./rwloc_test04
*/
    #include <stdio.h>   
    #include <pthread.h>  
   int main()  
   {  
        pthread_rwlock_t rwlock;
	pthread_rwlock_init(&rwlock,NULL); 

       pthread_rwlock_wrlock(&rwlock);  
       pthread_rwlock_wrlock(&rwlock);  
       printf("first write lock, then write lock\n");  
       pthread_rwlock_unlock(&rwlock);  
       pthread_rwlock_unlock(&rwlock);  
       return -1;  
   }  

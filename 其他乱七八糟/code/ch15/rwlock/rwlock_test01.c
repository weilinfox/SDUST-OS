/*
*rwloc_test01~04�� �ֱ���Զ�д���ж�����д���Ķ���д˳�����
*��ע���ĸ��ļ��ж�д����ʹ��˳��
* usage: $ gcc -o rwloc_test01 rwloc_test01.c -lpthread
* usage:$ ./rwloc_test01
*/
    #include <stdio.h>
    #include <pthread.h>  
    int main()  
    {  
        pthread_rwlock_t rwlock;
	      pthread_rwlock_init(&rwlock,NULL);  

        pthread_rwlock_rdlock(&rwlock);  
        pthread_rwlock_wrlock(&rwlock);  
	      printf("first read lock, then write lock\n");
        pthread_rwlock_unlock(&rwlock);  
        pthread_rwlock_unlock(&rwlock);  
        return 0;  
    }  

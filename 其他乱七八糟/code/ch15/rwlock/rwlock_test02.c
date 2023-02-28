/*
*rwloc_test01~04�� �ֱ���Զ�д���ж�����д���Ķ���д˳�����
*��ע���ĸ��ļ��ж�д����ʹ��˳��
* usage: $ gcc -o rwloc_test02 rwloc_test02.c -lpthread
* usage:$ ./rwloc_test02
*/
    #include <stdio.h>
    #include <pthread.h>  
  int main()  
  {  
        pthread_rwlock_t rwlock;
	pthread_rwlock_init(&rwlock,NULL);  

       pthread_rwlock_wrlock(&rwlock);  
       pthread_rwlock_rdlock(&rwlock);
       printf("first write lock, then read lock\n");  
       pthread_rwlock_unlock(&rwlock);  
       pthread_rwlock_unlock(&rwlock);  
       return -1;  
  }

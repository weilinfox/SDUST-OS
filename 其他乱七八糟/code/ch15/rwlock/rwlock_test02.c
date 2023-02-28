/*
*rwloc_test01~04： 分别测试读写锁中读锁、写锁的读、写顺序组合
*请注意四个文件中读写锁的使用顺序
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

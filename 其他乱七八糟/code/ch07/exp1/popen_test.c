#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
  
int main()  
{  
    FILE *fpr = NULL;  
    FILE *fpw = NULL;  
    char buf[BUFSIZ + 1];  //BUFSIZ 8192
    int len = 0;  
      
    //初始化缓冲区  
    memset(buf, '\0', sizeof(buf));  
    //打开ls和grep进程  
    fpr = popen("ls -l", "r");  
    fpw = popen("grep rwx", "w");  
    if(fpr && fpw)  
    {  
        //读取数据  
        len = fread(buf, sizeof(char), BUFSIZ, fpr);  
        while(len > 0)  
        {   //还有数据可读，循环读取数据，直到读完所有数据    
            buf[len] = '\0';  
            //把数据写入grep进程  
            fwrite(buf, sizeof(char), len, fpw);              
            len = fread(buf, sizeof(char), BUFSIZ, fpr);  
        }  
        //关闭文件流  
        pclose(fpr);  
        pclose(fpw);  
        exit(0);  //0 EXIT_SUCCESS
    }  
    exit(1);  //1 EXIT_FAILURE
}  


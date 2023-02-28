#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(void)
{
	int child_to_parent[2], parent_to_child[2];
	pid_t pid;
	char buf[512];
	int len=512;
	pipe(child_to_parent);	//创建父进程中用于读取数据的管道
	pipe(parent_to_child);	// 创建父进程中用于写入数据的管道
	if ( (pid = fork()) == 0) {// 子进程
		close(child_to_parent[0]);	// 关闭管道child_to_parent的读端
		close(parent_to_child[1]);	// 关闭管道parent_to_child的写端
		sprintf(buf, "this is child %d",getpid());
		write(child_to_parent[1], buf,len);	// 子进程向child_to_parent管道写入数据
		read(parent_to_child[0], buf,len);	// 子进程从parent_to_child管道读入数据
		printf(" I am child:%d, this is frmo parent: %s\n",getpid(),buf );/*处理buf中读入的数据*/
		close(child_to_parent[1]);	// 关闭管道child_to_parent的写端
		close(parent_to_child[0]);	//关闭管道parent_to_child的读端
	} else {	// 父进程
		close(child_to_parent[1]);	//关闭管道child_to_parent的写端
		close(parent_to_child[0]);	//关闭管道parent_to_child的读端
		sprintf(buf, "this is parent %d",getpid());
		write(parent_to_child[1], buf,len);	//父进程向parent_to_child管道写入数据
		read(child_to_parent[0], buf,len);	//父进程从child_to_parent管道读入数据
		printf(" I am parent:%d, this is frmo child: %s\n",getpid(),buf );/*处理buf中读入的数据*/
		close(parent_to_child[1]);	// 关闭parent_to_child管道的写端
		close(child_to_parent[0]);	// 关闭child_to_parent管道的读端
		/* 使用wait系列函数等待子进程退出并取得退出代码 */
		wait(NULL);
	}
	return 0;
}

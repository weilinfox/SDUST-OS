/* popen_test.c */

#include <stdio.h>
#include <string.h>

#define	BUFSIZ	8192

int main(int argc, char *argv[])
{
	FILE	*fpr	=	NULL;
	FILE	*fpw	=	NULL;
	char	buf[BUFSIZ+1];
	int	len	=	0;

	memset(buf, '\0', sizeof(buf));		/* 初始化缓冲区 */

	fpr = popen("ls -l", "r");
	fpw = popen("grep rwx", "w");

	if (fpr && fpw) {			/* 读取数据 */
		len = fread(buf, sizeof(char), BUFSIZ, fpr);
		while (len > 0) {
			buf[len] = '\0';
			/* 把数据写入 grep 进程 */
			fwrite(buf, sizeof(char), len, fpw);
			len = fread(buf, sizeof(char), BUFSIZ, fpr);
		}
		/* 关闭文件流 */
		pclose(fpr);
		pclose(fpw);
	} else {
		return 1;
	}


	return 0;
}


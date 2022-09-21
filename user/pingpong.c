#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	int ParentToChindPipe[2];
	int ChildToParentPipe[2];

	/*	匿名管道 pipe:
			只能单向通信, 如果需要双向通信，则需要创建 2 个管道.
			只能血缘关系的进程进行通信.
		其中 0 为用于从管道读取数据的文件描述符，1 为用于向管道写入数据的文件描述符
	*/
	pipe(ParentToChindPipe);
	pipe(ChildToParentPipe);

	if(fork() != 0){	// Parent Process
		while(1){
			char pData[10];
			memset(pData, 0, sizeof(pData));
		
			write(ParentToChindPipe[1],"P",1);	// 1 为用于向管道写入数据的文件描述符
			read(ChildToParentPipe[0], pData, 1);	// pipe 读阻塞.
			printf("%d: received pong\n",getpid());
			break;
		}
	}else{	// Child Process
		while(1){
			char data[10];
			memset(data, 0, sizeof(data));
			read(ParentToChindPipe[0], data, 1);	// pipe 读阻塞.
			printf("%d: received ping\n",getpid());
			sleep(5);
			write(ChildToParentPipe[1],"C",1);
			break;
		}
	}

	exit(0);
}

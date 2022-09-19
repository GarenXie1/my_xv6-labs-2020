#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	int cnt = 0;
	if(argc < 2){
		printf("Error: Please input 'sleep x'\n");
		exit(1);
	}

	cnt = atoi(argv[1]);
	sleep(cnt);

	exit(0);
}

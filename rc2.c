#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<signal.h>
#include"request.h"
#include"result.h"
#define M "\x1b[1;35m"
#define RST "\x1b[0m"
/*int len, fd4;
result res;
void handler(int a)
{
	len = read(fd4, &res, sizeof(result));
	if (res.pid == getpid())
		printf(M "%s:\tRead %d bytes from server --> '%d' '%d'.\n" RST, __FILE__, len, res.answer, res.pid);
}*/
int main()
{
	int len, fd4;
	result res;
	request r; 
	r.op='-'; r.op1=5000; r.op2=5000; r.pid=getpid();
	printf(M "%s:\tBEGIN.\n" RST, __FILE__);
	// Opening FIFO1 for write purpose. //
        int fd1 = open("./FIFO1", O_WRONLY);
        if (fd1 == -1)
        {
                perror("open");
                exit(EXIT_FAILURE);
        }
	// Writing to FIFO1. //
	len = write(fd1, &r, sizeof(request));
	printf(M "%s:\tWrote %d bytes to server --> '%d' '%c' '%d' '%d'.\n" RST, __FILE__, len, r.op1, r.op, r.op2, r.pid);
	// Opening FIFO4 for read purpose. //
        fd4 = open("./FIFO4", O_RDONLY);
        if (fd4 == -1)
        {
                perror("open");
                exit(EXIT_FAILURE);
        }
	// Reading final result from FIFO4. //
	len = read(fd4, &res, sizeof(result));
	
	//signal(SIGINT, handler);
	//pause();
	if (res.pid == r.pid)
	{
		printf(M "%s:\tRead %d bytes from server --> '%d' '%d'.\n" RST, __FILE__, len, res.answer, res.pid);
	}
	printf(M "%s:\tEND.\n" RST, __FILE__);
	return 0;
}

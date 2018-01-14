#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include"request.h"
#include"result.h"
#define C "\x1b[36m"
#define RST "\x1b[0m"
int main()
{
	request r; result res;
	int len, ret;
	printf(C "%s:\tBEGIN.\n" RST, __FILE__);
	// MAKING & OPENING FIFO2 TO READ REQUEST FROM SERVER. //
        if (access("./FIFO2", F_OK) == -1)
        {
                ret = mkfifo("./FIFO2", 666);
                if (ret == -1)
                {
                        perror("mkfifo");
                        exit(EXIT_FAILURE);
                }
        }
        int fd2 = open("./FIFO2", O_RDONLY);
        if (fd2 == -1)
        {
                perror("open");
                exit(EXIT_FAILURE);
        }
	// READING REQUEST FROM SERVER AND STORING IT IN request r. //
	len = read(fd2, &r, sizeof(request));
	printf(C "%s:\tRead %d Bytes from server --> '%d' '%c' '%d' '%d'.\n" RST, __FILE__, len, r.op1, r.op, r.op2, r.pid);
	// MAKING & OPENING FIFO3 TO WRITE RESULT TO SERVER. //
        if (access("./FIFO3", F_OK) == -1)
        {
                ret = mkfifo("./FIFO3", 666);
                if (ret == -1)
                {
                        perror("mkfifo");
                        exit(EXIT_FAILURE);
                }
        }
        int fd3 = open("./FIFO3", O_WRONLY);
        if (fd3 == -1)
        {
                perror("open");
                exit(EXIT_FAILURE);
        }
	// WRITING RESULT res TO SERVER //
	res.answer = (r.op1) - (r.op2);
	res.pid=r.pid;
	len=write(fd3, &res, sizeof(result));
	printf(C "%s:\tWrote %d Bytes to server --> '%d' '%d'.\n" RST, __FILE__, len, res.answer, res.pid);
	printf(C "%s:\tEND.\n" RST, __FILE__);
	return 0;
}

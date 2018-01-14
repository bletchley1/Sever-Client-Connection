#include"headers.h"
#include"request.h"
#include"result.h"
#include"decl.h"
#define G "\x1b[32m"
#define R "\x1b[31m"
#define RST "\x1b[0m"

int main()
{
	printf(G "%s:\tBEGIN.\n" RST, __FILE__);
	request r; result res;
	int len;
	createFIFO();
	// Making FIFO1 for read purpose. //
	for(int i=0; i<3; i++)
	{  //FOR LOOP STARTS
	int fd1 = open("./FIFO1", O_RDONLY);
	if (fd1 == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	// Reading from FIFO1 and storing in request r. //
	//while(len=read(fd1, &r, sizeof(request)))
	//{//WHILE BEGINS.
	printf(G "%s:\tRead %d Bytes from requesting client --> '%d' '%c' '%d' '%d'.\n" RST, __FILE__, len, r.op1, r.op, r.op2, r.pid);
	// FORK. //
	int ret_fork = fork();
	switch (ret_fork)
	{   //SWITCH RETFORK BEGINS.
	case -1: perror("fork");
		 exit(EXIT_FAILURE);
	case 0: printf(G "%s:\tBEGIN. CHILD PROCESS.\n" RST, __FILE__);

			switch (r.op)	//r.op is operand recieved from receiving client. +, -, *, /	
			{
			case '+':	execl("./add", "add.c", NULL);
			case '-':	execl("./sub", "sub.c", NULL);
			case '*':	execl("./mul", "mul.c", NULL);
			case '/':	execl("./div", "div.c", NULL);
			default:	printf(R "%s:\tCHILD: !!!!! INVALID OPERAND '%c' RECEIVED !!!!!.\n" RST, __FILE__, r.op);
			} //SWITCH CASE r.op ENDS.
		printf(G "%s:\tEND. CHILD PROCESS.\n" RST, __FILE__);
		break;
	default: printf(G "%s:\tBEGIN. DEFAULT.\n" RST, __FILE__);
		// Creating FIFO2 for writing to processing client. //
       		int fd2 = open("./FIFO2", O_WRONLY);
       		if (fd2 == -1)
        	{
                	perror("open");
                	exit(EXIT_FAILURE);
       	 	}
		// Writing to FIFO2 for processing. //
		len=write(fd2, &r, sizeof(request));
		printf(G "%s:\tDEFAULT: Wrote %d Bytes to processing client --> '%d' '%c' '%d' '%d'.\n" RST, __FILE__, len, r.op1, r.op, r.op2, r.pid);
        	// Creating FIFO3 for read purpose. //
        	int fd3 = open("./FIFO3", O_RDONLY);
        	if (fd3 == -1)
        	{
                	perror("open");
                	exit(EXIT_FAILURE);
        	}
		// Reading from FIFO3 for reading. //
		len=read(fd3, &res, sizeof(result));
		printf(G "%s:\tDEFAULT: Read %d Bytes from processing client --> '%d' '%d'.\n" RST, __FILE__, len, res.answer, res.pid);
		//KILL.
		//kill(res.pid, SIGINT);	
		// Creating FIFO4 for write purpose. //
		int fd4 = open("./FIFO4", O_WRONLY);
		if (fd4 == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		// Writing result to requesting client using FIFO4. //
		len=write(fd4, &res, sizeof(result));
		printf(G "%s:\tDEFAULT: Wrote %d Bytes to requesting client --> '%d' '%d'.\n" RST, __FILE__, len, res.answer, res.pid);
       		printf(G "%s:\tEND. DEFAULT.\n" RST, __FILE__);
	} //SWITCH RETFORK ENDS.
	printf(G "%s:\tEND.\n" RST, __FILE__);
//	}//WHILE ENDS.
	} //FOR LOOP ENDS.
	return 0;
	//MAIN ENDS.
}

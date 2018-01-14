#include"headers.h"
#include"decl.h"
#define FIFO1 "./FIFO1"
#define FIFO2 "./FIFO2"
#define FIFO3 "./FIFO3"
#define FIFO4 "./FIFO4"

int createFIFO()
{
	int ret;
	// Making FIFO1. //
	if (access(FIFO1, F_OK) == -1)
        {
                ret = mkfifo(FIFO1, 666);
                if (ret == -1)
                {
                        perror("mkfifo");
                        exit(EXIT_FAILURE);
                }
        }
	// Making FIFO2. //
	if (access(FIFO2, F_OK) == -1)
        {
                ret = mkfifo(FIFO2, 666);
                if (ret == -1)
                {
                        perror("mkfifo");
                        exit(EXIT_FAILURE);
                }
        }
	// Making FIFO3. //
	if (access(FIFO3, F_OK) == -1)
        {
                ret = mkfifo(FIFO3, 666);
                if (ret == -1)
                {
                        perror("mkfifo");
                        exit(EXIT_FAILURE);
                }
        }
	// Making FIFO4. //
	if (access(FIFO4, F_OK) == -1)
        {
                ret = mkfifo(FIFO4, 666);
                if (ret == -1)
                {
                        perror("mkfifo");
                        exit(EXIT_FAILURE);
                }
        }
	return 0;
}

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <aio.h>






void set_aiocb(struct aiocb *cbp, int fd, void* buffer, size_t size);


ssize_t recvMsgUntil(int sock, const char* regex,void* buf, size_t n);

void set_aiocb(struct aiocb *cbp, int fd, void* buffer, size_t size) {
    //fd set
    cbp->aio_fildes     = fd;
    //buffer set
    cbp->aio_buf        = buffer;
    //size set
    cbp->aio_nbytes     = size;
    //fop set
    cbp->aio_offset     = 0;
}




int main(int argc, char *argv[]) {

	int cli_fd, len;
	struct sockaddr_in client_addr;
	char* buf = NULL;

	cli_fd = socket(PF_INET, SOCK_STREAM, 0);

	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	client_addr.sin_port = htons(9999);

	if(connect(cli_fd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) perror("connect error\n");

	buf =(void*) malloc(1024);
	
	len = recvMsgUntil(cli_fd, "1234", buf, 1024);

	printf("read buf : %s\n", buf);
	close(cli_fd);
	return 0;
}

ssize_t 
recvMsgUntil(int sock, const char* regex,void* buf, size_t n){

	int ret ; 
	struct aiocb *cb;
	set_siocb(cb, sock, buf, n);

	ret = aio_read(cb);
	if (ret < 0) perror("aio_read");
	
	while ( aio_error( cb ) == EINPROGRESS )
	{
	    printf("busy waiting...\n");
	}

	if ((ret = aio_return(cb)) > 0) {
	    return ret;
	    /* got ret bytes on the read */
	} else {
	    /* read failed, consult errno */
	}	
}

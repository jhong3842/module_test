#include <arpa/inet.h>
#include <aio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <regex.h>




void set_aiocb(struct aiocb *cbp, int fd, void* buffer, size_t size);
ssize_t recvMsgUntil(int sock, const char* regex,void* buf, size_t n);
int reg_check(const char* regex, void* buf);
int reg_error_number(int error);

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

	/*for develop, test code*/
	cli_fd = socket(PF_INET, SOCK_STREAM, 0);

	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	client_addr.sin_port = htons(9999);

	if(connect(cli_fd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) perror("connect error\n");

	buf =(void*) malloc(1024);
	
	len = recvMsgUntil(cli_fd, "^^^{]file|gopher|news|nntp|telnet|https?|ftps?|sftp):\/\/([a-z0-9-]+\.)+[a-z0-9]{2,4}.*$", buf, 1024);

	if(len > 0 ){
		printf("read buf : %s\n", buf);
	}
	close(cli_fd);
	return 0;
}



int reg_check(const char* regex, void* buf){

	regex_t state;
	const char *pattern = regex;
	char tmp[100];
	int rc;

	//pattern compile
	rc = regcomp(&state, pattern, REG_EXTENDED);
	if(rc != 0 ){
		regerror(rc, &state, tmp, 100);
		printf("regcomp() failed with '%s'\n", tmp);
		return reg_error_number(rc);
	}	

	//matching regex
	int status = regexec(&state, buf, 0, NULL, 0);
	
	return status;
}

int reg_error_number(int error){
	
	switch(error){
		case REG_NOMATCH:
			return -11;
			break;
                case REG_BADPAT:
                        return -12;
                        break;
                case REG_ECOLLATE:
                        return -13;
                        break;
                case REG_ECTYPE:
                        return -14;
                        break;
                case REG_EESCAPE:
                        return -15;
                        break;
                case REG_ESUBREG:
                        return -16;
                        break;
                case REG_EBRACK:
                        return -17;
                        break;
                case REG_EPAREN:
                        return -18;
                        break;
                case REG_EBRACE:
                        return -19;
                        break;
                case REG_BADBR:
                        return -20;
                        break;
                case REG_ERANGE:
                        return -21;
                        break;
                case REG_ESPACE:
                        return -22;
                        break;
                case REG_BADRPT:
                        return -23;
                        break;
	}
}

ssize_t 
recvMsgUntil(int sock, const char* regex,void* buf, size_t n){

	int ret , len; 
	struct aiocb cb;

	memset(&cb , 0x00, sizeof(struct aiocb));
	set_aiocb(&cb, sock, buf, n);

	ret = aio_read(&cb);
	if (ret < 0) perror("aio_read");
	

	while ( aio_error( &cb ) == EINPROGRESS ){}

	
	if ((len = aio_return(&cb)) > 0) {
	    /* got ret bytes on the read */

	    /*reg check to buf*/
	    ret =reg_check(regex, buf);

	    /*if scucces, retrun value is 0*/
	    if(ret == 0)
		return len;
	    /*if error, return value negative int.*/
	    else 
		return ret;
	
	} else {
	    /* read failed, consult errno */
	    return -1;
	}	
}

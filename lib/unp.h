#ifndef __unp_h
#define __unp_h

#define MAXLINE 4096
#define SA struct sockaddr

#include <netinet/in.h>  /* sockaddr_in{} and another Internet defns */
#include <sys/socket.h> /* basic socket definitions */
#include <sys/uio.h>   /*for lovec{} and readv/writev */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>  /*inet(3) functions */
#include <unistd.h> 
#include <errno.h>


#ifndef HAVE_BZERO
#define bzero(ptr,n)   memset(ptr,0,n)
#endif /*bzero*/

void err_quit(const char *,...);
void err_sys(const char *,...);














#endif /* __unp_h_ */

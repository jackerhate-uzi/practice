#ifndef __unp_h
#define __unp_h

#include "../config.h"

#define MAXLINE 4096
#define LISTENQ 1024

#include <arpa/inet.h> /*inet(3) functions */
#include <errno.h>
#include <netinet/in.h> /* sockaddr_in{} and another Internet defns */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> /* basic socket definitions */
#include <sys/uio.h>    /*for lovec{} and readv/writev */
#include <unistd.h>

#ifndef HAVE_BZERO
#define bzero(ptr, n) memset(ptr, 0, n)
#endif /*bzero*/

#define SA struct sockaddr
void err_quit(const char *, ...); /*error.c*/
void err_sys(const char *, ...);  /*error.c*/
int Socket(int, int, int);        /*wrapsock.c*/
void Bind(int, const SA *,socklen_t);/*wrapsock.c*/
void Listen(int, int);/*wrapsock.c*/
int Accept(int, SA *,socklen_t *); /*wrapsock.c*/
void Write(int,void *,size_t); /*wrapunix.c*/
void Close(int); /*wrapunix.c*/
#endif /* __unp_h_ */


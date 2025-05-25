#ifndef _PX_H_
#define _PX_H_

#include <sys/types.h>
#include <sys/socket.h>

ssize_t px_pread(int fd, void *buf, size_t nbyte, off_t offset);
ssize_t px_pwrite(int fd, const void *buf, size_t nbyte, off_t offset);
int px_sendmsg(int sockfd, const struct msghdr *msg, int flags);
int px_recvmsg(int sockfd, struct msghdr *msg, int flags);
int px_accept(int sockfd, struct sockaddr *addr, int *addrlen);

#endif /* _PX_H_ */

#ifndef _MACH_SA_SYS_SOCKET_H_
#define _MACH_SA_SYS_SOCKET_H_

#include <sys/cdefs.h>
#include <sys/types.h>

struct sockaddr {
unsigned short sa_family;
char sa_data[14];
};

struct iovec {
void *iov_base;
int iov_len;
};

struct msghdr {
void *msg_name;
int msg_namelen;
struct iovec *msg_iov;
int msg_iovlen;
void *msg_accrights;
int msg_accrightslen;
};

__BEGIN_DECLS
int accept(int, struct sockaddr *, int *);
int sendmsg(int, const struct msghdr *, int);
int recvmsg(int, struct msghdr *, int);
__END_DECLS

#endif /* _MACH_SA_SYS_SOCKET_H_ */

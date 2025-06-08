#ifndef _MACH_SA_SYS_SOCKET_H_
#define _MACH_SA_SYS_SOCKET_H_

#include <mach/sa/sys/cdefs.h>
#include <mach/sa/sys/types.h>

/**
 * Socket address structure used for all socket operations.
 */
struct sockaddr {
  unsigned short sa_family;
  char sa_data[14];
};

/**
 * Scatter/gather vector element.
 */
struct iovec {
  void *iov_base;
  int iov_len;
};

/**
 * Message header for scatter/gather I/O operations.
 */
struct msghdr {
  void *msg_name;
  int msg_namelen;
  struct iovec *msg_iov;
  int msg_iovlen;
  void *msg_accrights;
  int msg_accrightslen;
};

__BEGIN_DECLS
/** Accept a connection on a socket. */
int accept(int, struct sockaddr *, int *);
/** Send a message from an array of buffers. */
int sendmsg(int, const struct msghdr *, int);
/** Receive a message into an array of buffers. */
int recvmsg(int, struct msghdr *, int);
__END_DECLS

#endif /* _MACH_SA_SYS_SOCKET_H_ */

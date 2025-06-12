/**
 * @file px.h
 * @brief Declarations for PX (Protocol Extension?) I/O operations.
 *
 * This file declares a set of functions that appear to be custom
 * implementations or wrappers for POSIX-like I/O operations such as
 * `pread`, `pwrite`, and socket operations like `sendmsg`, `recvmsg`,
 * and `accept`. The "px_" prefix might indicate a "Protocol Extension"
 * or a specific library/subsystem providing these functionalities.
 */
#ifndef _PX_H_
#define _PX_H_

#include <sys/types.h>  /* For ssize_t, size_t, off_t */
#include <sys/socket.h> /* For struct msghdr, struct sockaddr, socklen_t (often int*) */

/**
 * @brief Reads data from a file descriptor at a given offset.
 * Similar to the POSIX `pread()` system call.
 * @param fd File descriptor.
 * @param buf Buffer to store the read data.
 * @param nbyte Number of bytes to read.
 * @param offset Offset in the file to start reading from.
 * @return On success, the number of bytes read. On error, -1, and errno is set.
 *         A return value of 0 indicates end-of-file.
 */
ssize_t px_pread(int fd, void *buf, size_t nbyte, off_t offset);

/**
 * @brief Writes data to a file descriptor at a given offset.
 * Similar to the POSIX `pwrite()` system call.
 * @param fd File descriptor.
 * @param buf Buffer containing the data to write.
 * @param nbyte Number of bytes to write.
 * @param offset Offset in the file to start writing to.
 * @return On success, the number of bytes written. On error, -1, and errno is set.
 */
ssize_t px_pwrite(int fd, const void *buf, size_t nbyte, off_t offset);

/**
 * @brief Sends a message on a socket using a `msghdr` structure.
 * Similar to the POSIX `sendmsg()` system call.
 * @param sockfd Socket file descriptor.
 * @param msg Pointer to a `msghdr` structure containing the message to send.
 * @param flags Flags for the send operation (e.g., MSG_DONTWAIT).
 * @return On success, the number of bytes sent. On error, -1, and errno is set.
 */
int px_sendmsg(int sockfd, const struct msghdr *msg, int flags);

/**
 * @brief Receives a message from a socket using a `msghdr` structure.
 * Similar to the POSIX `recvmsg()` system call.
 * @param sockfd Socket file descriptor.
 * @param msg Pointer to a `msghdr` structure to store the received message.
 * @param flags Flags for the receive operation (e.g., MSG_DONTWAIT).
 * @return On success, the number of bytes received. On error, -1, and errno is set.
 *         A return value of 0 can indicate the peer has performed an orderly shutdown.
 */
int px_recvmsg(int sockfd, struct msghdr *msg, int flags);

/**
 * @brief Accepts a new connection on a socket.
 * Similar to the POSIX `accept()` system call.
 * @param sockfd Listening socket file descriptor.
 * @param addr Pointer to a `sockaddr` structure to receive the address of the connecting peer.
 *             Can be NULL if the caller is not interested in the peer address.
 * @param addrlen Pointer to an integer (`socklen_t` in modern POSIX) that on input specifies
 *                the size of the `addr` buffer, and on output contains the actual size
 *                of the peer address. Can be NULL if `addr` is NULL.
 * @return On success, a file descriptor for the accepted socket. On error, -1, and errno is set.
 */
int px_accept(int sockfd, struct sockaddr *addr, int *addrlen);

#endif /* _PX_H_ */

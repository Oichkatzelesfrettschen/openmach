#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

ssize_t
px_pread(int fd, void *buf, size_t nbyte, off_t offset)
{
	ssize_t rc;
	do {
	 rc = pread(fd, buf, nbyte, offset);
	} while (rc < 0 && errno == EINTR);
	return rc;
}

ssize_t
px_pwrite(int fd, const void *buf, size_t nbyte, off_t offset)
{
	ssize_t rc;
	do {
	 rc = pwrite(fd, buf, nbyte, offset);
	} while (rc < 0 && errno == EINTR);
	return rc;
}

int
px_sendmsg(int sockfd, const struct msghdr *msg, int flags)
{
	int rc;
	do {
	 rc = sendmsg(sockfd, msg, flags);
	} while (rc < 0 && errno == EINTR);
	return rc;
}

int
px_recvmsg(int sockfd, struct msghdr *msg, int flags)
{
	int rc;
	do {
	 rc = recvmsg(sockfd, msg, flags);
	} while (rc < 0 && errno == EINTR);
	return rc;
}

int
px_accept(int sockfd, struct sockaddr *addr, int *addrlen)
{
	int rc;
	do {
	 rc = accept(sockfd, addr, addrlen);
	} while (rc < 0 && errno == EINTR);
	return rc;
}

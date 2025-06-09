#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief Wrapper around pread that retries on EINTR.
 */
ssize_t px_pread(int fd, void *buf, size_t nbyte, off_t offset) {
  ssize_t rc;
  do {
    rc = pread(fd, buf, nbyte, offset);
  } while (rc < 0 && errno == EINTR);
  return rc;
}

/**
 * @brief Wrapper around pwrite that retries on EINTR.
 */
ssize_t px_pwrite(int fd, const void *buf, size_t nbyte, off_t offset) {
  ssize_t rc;
  do {
    rc = pwrite(fd, buf, nbyte, offset);
  } while (rc < 0 && errno == EINTR);
  return rc;
}

/**
 * @brief Wrapper around sendmsg that retries on EINTR.
 */
int px_sendmsg(int sockfd, const struct msghdr *msg, int flags) {
  int rc;
  do {
    rc = sendmsg(sockfd, msg, flags);
  } while (rc < 0 && errno == EINTR);
  return rc;
}

/**
 * @brief Wrapper around recvmsg that retries on EINTR.
 */
int px_recvmsg(int sockfd, struct msghdr *msg, int flags) {
  int rc;
  do {
    rc = recvmsg(sockfd, msg, flags);
  } while (rc < 0 && errno == EINTR);
  return rc;
}

/**
 * @brief Wrapper around accept that retries on EINTR.
 */
int px_accept(int sockfd, struct sockaddr *addr, int *addrlen) {
  int rc;
  do {
    rc = accept(sockfd, addr, addrlen);
  } while (rc < 0 && errno == EINTR);
  return rc;
}

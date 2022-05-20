#include "klee/Config/config.h"
#include <assert.h>
#include <errno.h>
#include <klee/klee.h>
#include <linux/net.h> /* SYS_* constants */
#include <netinet/in.h>
#include <netpacket/packet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/syscall.h> /* __NR_* constants */
#include <sys/types.h>
#include <unistd.h>

#include "fd.h"
#include "klee/klee.h"

int bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen) {
  return 0;
}

int getpeername(int sockfd, struct sockaddr *addr, socklen_t *paddrlen) {
  return 0;
}

int getsockname(int sockfd, struct sockaddr *addr, socklen_t *paddrlen) {
  return 0;
}

int listen(int sockfd, int backlog) { return 0; }

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) { return 0; }

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  return 0;
}

int shutdown(int sockfd, int how) { return 0; }

int socket(int family, int type, int protocol) { return 0; }

ssize_t send(int fd, const void *buf, size_t len, int flags) {
  klee_print_expr("Data structure size", len);
  return len;
}
ssize_t recv(int fd, void *buf, size_t len, int flags) {
  klee_make_symbolic(buf, len, "recv_buffer_");
  return 0;
}

ssize_t recvfrom(int sockfd, __ptr_t buffer, size_t len, int flags,
                 struct sockaddr *to, socklen_t *tolen) {

  klee_make_symbolic(buffer, len, "recvfrom_buffer_");
  return len;
}

ssize_t sendto(int sockfd, const void *buffer, size_t len, int flags,
               const struct sockaddr *to, socklen_t tolen) {
  klee_print_expr("Data structure size", len);
  return len;
}

ssize_t sendmsg(int fd, const struct msghdr *msg, int flags) {
  klee_print_expr("Data structure size", msg->msg_iovlen);
  return 0;
}

ssize_t recvmsg(int fd, struct msghdr *msg, int flags) {
  klee_make_symbolic(msg->msg_iov->iov_base, msg->msg_iovlen, "recvmsg_buffer_");
  return 0;
}

int getsockopt(int fd, int level, int optname, __ptr_t optval,
               socklen_t *optlen) {
  return 0;
}

int setsockopt(int fd, int level, int optname, const void *optval,
               socklen_t optlen) {
  return 0;
}

int socketpair(int family, int type, int protocol, int sockvec[2]) { return 0; }

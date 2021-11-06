#ifndef __NET_H__
#define __NET_H__

#include "bits/net.h"
#include "byte.h"
#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

char *sock_ntop(const struct sockaddr *sa, socklen_t addrlen);
ssize_t readn(int fd, void *buff, size_t nbytes);
ssize_t writen(int fd, const void *buff, size_t nbytes);
ssize_t readline(int fd, void *buff, size_t maxlen);
ssize_t readlinebuf(void **vptr);

#ifdef __cplusplus
}
#endif

#endif /* __NET_H__ */

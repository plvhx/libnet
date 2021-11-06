#include <errno.h>
#include <unistd.h>

#include "../include/net.h"

ssize_t readn(int fd, void *buff, size_t nbytes) {
  size_t nleft;
  ssize_t nread;
  char *ptr;

  ptr = buff;
  nleft = nbytes;

  while (nleft > 0) {
    if ((nread = read(fd, ptr, nleft)) < 0) {
      if (errno == EINTR)
        nread = 0;
      else
        return -1;
    } else if (!nread)
      return 0;

    nleft -= nread;
    ptr += nread;
  }

  return (nbytes - nleft);
}

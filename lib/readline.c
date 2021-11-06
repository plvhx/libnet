#include <errno.h>
#include <unistd.h>

#include "../include/net.h"

static int __read_count;
static char *__read_ptr;
static char __read_buf[MAXLINE + 1];

static ssize_t __read_wrapper(int fd, char *ptr) {
  if (__read_count <= 0) {
  __again:
    if ((__read_count = read(fd, __read_buf, MAXLINE)) < 0) {
      if (errno == EINTR)
        goto __again;
      return -1;
    } else if (!__read_count) {
      return 0;
    }

    __read_ptr = __read_buf;
  }

  __read_count--;
  *ptr = *__read_ptr++;
  return 1;
}

ssize_t readline(int fd, void *buff, size_t maxlen) {
  ssize_t n, rc;
  char c, *ptr;

  ptr = buff;

  for (n = 1; n < maxlen; n++) {
    if ((rc = __read_wrapper(fd, &c)) == 1) {
      *ptr++ = c;
      if (c == '\n')
        break;
    } else if (!rc) {
      *ptr = 0;
      return (n - 1);
    } else {
      return -1;
    }
  }

  *ptr = 0;
  return n;
}

ssize_t readlinebuf(void **vptr) {
  if (__read_count)
    *vptr = __read_ptr;
  return __read_count;
}

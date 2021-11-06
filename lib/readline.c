/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2021, Paulus Gandung Prakosa <gandung@lists.infradead.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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

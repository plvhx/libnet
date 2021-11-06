/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2021, Paulus Gandung Prakosa <gandung@lists.infradead.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
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
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#if (defined __linux__ || defined __sun || defined __FreeBSD__)
#include <strings.h>
#endif

#include <netinet/in.h>
#include <sys/socket.h>

#include "../include/net.h"

int sock_bind_wild(int fd, int family) {
  socklen_t slen;

  switch (family) {
  case AF_INET: {
    struct sockaddr_in s;

    bzero(&s, sizeof(struct sockaddr_in));

    s.sin_family = AF_INET;
    s.sin_port = platform_htons(0);
    s.sin_addr.s_addr = platform_htonl(INADDR_ANY);

    if (bind(fd, (struct sockaddr *)&s, sizeof(struct sockaddr_in)) < 0)
      return -1;

    slen = sizeof(struct sockaddr_in);

    if (getsockname(fd, (struct sockaddr *)&s, &slen) < 0)
      return -1;

    return s.sin_port;
  }
  case AF_INET6: {
    struct sockaddr_in6 s;

    bzero(&s, sizeof(struct sockaddr_in6));

    s.sin6_family = AF_INET6;
    s.sin6_port = platform_htons(0);
    s.sin6_addr = in6addr_any;

    if (bind(fd, (struct sockaddr *)&s, sizeof(struct sockaddr_in6)) < 0)
      return -1;

    slen = sizeof(struct sockaddr_in6);

    if (getsockname(fd, (struct sockaddr *)&s, &slen) < 0)
      return -1;

    return s.sin6_port;
  }
  }

  return -1;
}

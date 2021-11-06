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

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "../include/net.h"

static char *__deserialize_sa_af_unix(const void **ptr,
                                      const struct sockaddr *sa,
                                      socklen_t salen) {
  struct sockaddr_un *u = (struct sockaddr_un *)sa;
  const char *__un_zero = "(no pathname bound)";
  char *bptr = (char *)(*ptr);

  snprintf(bptr, ADDR_BUF_LEN, "%s",
           u->sun_path[0] == '\0' ? __un_zero : u->sun_path);
  return bptr;
}

char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen) {
  static char buff[ADDR_BUF_LEN + 1];

  bzero(buff, ADDR_BUF_LEN + 1);

  switch (sa->sa_family) {
  case AF_INET: {
    struct sockaddr_in *s = (struct sockaddr_in *)sa;

    if (inet_ntop(s->sin_family, &s->sin_addr, buff, ADDR_BUF_LEN) == NULL)
      return NULL;

    break;
  }
  case AF_INET6: {
    struct sockaddr_in6 *s = (struct sockaddr_in6 *)sa;

    if (inet_ntop(s->sin6_family, &s->sin6_addr, buff, ADDR_BUF_LEN) == NULL)
      return NULL;

    break;
  }
#ifdef AF_UNIX
  case AF_UNIX:
    __deserialize_sa_af_unix((const void **)&buff, sa, salen);
    break;
#endif
  }

  return buff;
}

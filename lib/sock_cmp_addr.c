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

#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#ifdef HAVE_SOCKADDR_DL_STRUCT
#include <net/if_dl.h>
#endif

#include "../include/net.h"

int sock_cmp_addr(const struct sockaddr *s1, const struct sockaddr *s2,
                  socklen_t addrlen) {
  if (s1->sa_family != s2->sa_family)
    return -1;

  switch (s1->sa_family) {
  case AF_INET:
    return memcmp(&((struct sockaddr_in *)s1)->sin_addr,
                  &((struct sockaddr_in *)s2)->sin_addr,
                  sizeof(struct in_addr));
  case AF_INET6:
    return memcmp(&((struct sockaddr_in6 *)s1)->sin6_addr,
                  &((struct sockaddr_in6 *)s2)->sin6_addr,
                  sizeof(struct in6_addr));
  case AF_UNIX:
    return strcmp(((struct sockaddr_un *)s1)->sun_path,
                  ((struct sockaddr_un *)s2)->sun_path);
#ifdef HAVE_SOCKADDR_DL_STRUCT
  case AF_LINK:
    return -1;
#endif
  }

  return -1;
}

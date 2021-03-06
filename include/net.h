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

#ifndef __NET_H__
#define __NET_H__

#include "bits/net.h"
#include "byte.h"
#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

int sock_bind_wild(int fd, int family);

int sock_cmp_addr(const struct sockaddr *s1, const struct sockaddr *s2,
                  socklen_t addrlen);
int sock_cmp_port(const struct sockaddr *s1, const struct sockaddr *s2,
                  socklen_t addrlen);

int sock_get_port(const struct sockaddr *sa, socklen_t salen);

void sock_set_addr(const struct sockaddr *sa, socklen_t salen, const void *ptr);
void sock_set_port(const struct sockaddr *sa, socklen_t salen, uint16_t port);
void sock_set_wild(struct sockaddr *sa, socklen_t salen);

char *sock_ntop(const struct sockaddr *sa, socklen_t addrlen);
char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen);

ssize_t readn(int fd, void *buff, size_t nbytes);
ssize_t writen(int fd, const void *buff, size_t nbytes);
ssize_t readline(int fd, void *buff, size_t maxlen);
ssize_t readlinebuf(void **vptr);

#ifdef __cplusplus
}
#endif

#endif /* __NET_H__ */

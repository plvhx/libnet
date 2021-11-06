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

#ifndef __BYTE_H__
#define __BYTE_H__

#include <stdint.h>

#if (defined __linux__ || defined __sun || defined __FreeBSD__)
#include <arpa/inet.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

static inline uint16_t __htons(uint16_t val) {
  uint16_t a = ((val & 0x00ff) >> 0) << 8;
  uint16_t b = ((val & 0xff00) >> 8) << 0;
  return (a | b);
}

static inline uint16_t __ntohs(uint16_t val) { return __htons(val); }

static inline uint32_t __htonl(uint32_t val) {
  uint32_t a = ((val & 0x000000ff) >> 0) << 24;
  uint32_t b = ((val & 0x0000ff00) >> 8) << 16;
  uint32_t c = ((val & 0x00ff0000) >> 16) << 8;
  uint32_t d = ((val & 0xff000000) >> 24) << 0;
  return (a | b | c | d);
}

static inline uint32_t __ntohl(uint32_t val) { return __htonl(val); }

#ifndef platform_htons
#if (defined __linux__ || defined __sun || defined __FreeBSD__)
#define platform_htons htons
#else
#define platform_htons __htons
#endif
#endif

#ifndef platform_ntohs
#if (defined __linux__ || defined __sun || defined __FreeBSD__)
#define platform_ntohs ntohs
#else
#define platform_ntohs __ntohs
#endif
#endif

#ifndef platforn_htonl
#if (defined __linux__ || defined __sun || defined __FreeBSD__)
#define platform_htonl htonl
#else
#define platform_htonl __htonl
#endif
#endif

#ifndef platform_ntohl
#if (defined __linux__ || defined __sun || defined __FreeBSD__)
#define platform_ntohl ntohl
#else
#define platform_ntohl __ntohl
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __BYTE_H__ */

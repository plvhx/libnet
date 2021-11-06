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

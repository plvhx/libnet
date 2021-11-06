#include <stdio.h>
#include <string.h>

#if (defined __linux__ || defined __sun || defined __FreeBSD__)
#include <strings.h>
#endif

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "../include/net.h"

char *sock_ntop(const struct sockaddr *sa, socklen_t addrlen) {
  char pstr[PORT_STR_LEN + 1];
  static char buff[ADDR_BUF_LEN + 1];

  bzero(pstr, PORT_STR_LEN + 1);
  bzero(buff, ADDR_BUF_LEN + 1);

  switch (sa->sa_family) {
  case AF_INET: {
    struct sockaddr_in *s = (struct sockaddr_in *)sa;

    if (inet_ntop(s->sin_family, (void *)(&(s->sin_addr)), buff,
                  ADDR_BUF_LEN) == NULL)
      return NULL;

    if (s->sin_port != 0) {
      snprintf(pstr, PORT_STR_LEN, ":%d", platform_ntohs(s->sin_port));
      strncat(buff, pstr, strlen(pstr));
    }

    break;
  }
  case AF_INET6: {
    struct sockaddr_in6 *s = (struct sockaddr_in6 *)s;

    buff[0] = '[';

    if (inet_ntop(s->sin6_family, (void *)(&(s->sin6_addr)), buff + 1,
                  ADDR_BUF_LEN) == NULL) {
      return NULL;
    }

    buff[strlen(buff)] = ']';

    if (s->sin6_port != 0) {
      snprintf(pstr, PORT_STR_LEN, ":%d", platform_ntohs(s->sin6_port));
      strncat(buff, pstr, strlen(pstr));
    }

    break;
  }
  default:
    break;
  }

  return buff;
}

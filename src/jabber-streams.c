/* jabber-streams.c ---
 *
 * Filename: jabber-streams.c
 * Description:
 * Author: srbpkk
 * Created: Mon Aug 15 13:58:33 2011 (+0600)
 * Version: 0.1

/* Code: */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <netdb.h>
#include <errno.h>

#include "jabber-streams.h"

JStream *
stream_init (char *name, char *login, char *passwd, char *domain)
{
  if ((name || login || passwd || domain) == NULL)
    {
      fprintf (stderr,
	       "name or login or password or domain was not specified\n");
      return NULL;
    }
  JStream *stream = malloc (sizeof (JStream));
  stream->name = calloc (strlen (name) + 1, sizeof (char));
  stream->socket_d = socket (AF_INET, SOCK_STREAM, 0);
  stream->acc = malloc (sizeof (struct account));
  stream->acc->login = calloc (strlen (login) + 1, sizeof (char));
  stream->acc->login = login;
  stream->acc->passwd = calloc (strlen (passwd) + 1, sizeof (char));
  stream->acc->passwd = passwd;
  stream->acc->domain = calloc (strlen (domain) + 1, sizeof (char));
  stream->acc->domain = domain;
  return stream;
}

int
stream_bind (JStream * stream)
{
  int *sock = (&)stream->socket_d;
  struct hostent *h = gethostbyname (stream->acc->domain);
  struct sockaddr_in *addr;
  memcpy (addr->sin_addr.s_addr, h->h_addr_list[0], h->length);
  addr->sin_family = AF_INET;
  addr->sin_port = (short) 5222;
  if (connect (stream->sock, (sockaddr *) & addr, sizeof (addr)) != 0)
    return -1;
  return 0;
}

int
send_data (JStream * stream, char *sendbuf, int length, char *recvbuf)
{
  if (send (stream->socket_d, sendbuf, length, 0) < 0)
    {
      fprintf (stderr, "error (code %d): %s\n", errno, strerror (errno));
      return -1;
    }
  if (recv (stream->socket_d, recvbuf, strlen (recvbuf), 0) > 0)
    return -2;
  return 0;
}

/* jabber-streams.c ends here */

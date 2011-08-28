/* jabber-streams.h ---
 *
 * Filename: jabber-streams.h
 * Description: -
 * Author: srbpkk
 * Created: Sun Aug 28 14:55:35 2011 (+0600)
 * Version: 0.1
 */

/* Code: */


struct account
{
  char *login;
  char *passwd;
  char *domain;
};

typedef struct
{
  char *challenge;
  char *auth_type;
} SASL;

typedef struct
{
  char *name; // name of jabber_stream
  int socket_d; // socket descriptor
  struct account *acc; // account, which have login, password and domain address
  SASL *sasl; // see SASL structure
} JStream;

JStream * stream_init(char *name, char *login, char *passwd, char *domain);

int stream_bind(JStream *stream);

int stream_send(JStream *stream, char *send, int length);

int stream_recv(JStream *stream, char *recvbuf);

/* jabber-streams.h ends here */

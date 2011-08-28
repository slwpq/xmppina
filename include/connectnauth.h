/* connectnauth.h ---
 *
 * Filename: connectnauth.h
 * Description: connect and auth functions
 * Author: srbpkk
 * Created: Sat Aug 27 09:28:11 2011 (+0600)
 * Version: 0.1
 */

/* Code: */

/* Authorization*/
int open_stream(JStream *stream);
int close_stream(JStream *stream);

/* SASL negotiation */
int SASL_negotiation(JStream *stream);
int SASL_choose_mech(char *mechanisms);
int SASL_MD5_auth(JStream *stream);
int SASL_SCRAM_SHA1_auth(JStream *stream);
int SASL_PLAIN_auth(JStream *stream);

int resource_bind(JStream *stream);

/* connectnauth.c ends here */

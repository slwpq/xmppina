/* xmlnode.h ---
 *
 * Filename: xmlnode.h
 * Description: used for creating & manipulating xml nodes in libssanina
 * Author: srbpkk
 * Created: Mon Aug 15 20:11:57 2011 (+0600)
 * Version: 0.1

/* Code: */

typedef struct
{
  char **pair; // pair[n][0] - name, pair[n][1] -value
  int n; // how many
} attrxmlns;

typedef struct _xmlnode xmlnode;
struct _xmlnode
{
  char *name;          /*  name of node  */
  attrxmlns *xmlns;         /*  xml namespace */
  attrxmlns *attr;        /*  attributes    */
  char *content;          /*  data          */
  xmlnode *child;      /*  child node    */
  xmlnode *parent;     /*  parent node   */
  xmlnode *next;       /*  next node     */
  int isithead;       /* is this part of node  */
};

xmlnode* new_node(char*, char*, char*); /* create node */
void new_childnode(char*, char*, char*, xmlnode*);  /* create childnode */
void insert_content(char*, xmlnode*); /* insert data in node */
void insert_child(xmlnode*, xmlnode*); /* insert childnode */
void set_xmlns(char *, char*, xmlnode*); /* set xml namespace */
void set_attr(char*, char*, xmlnode*); /* set attribute */
void delete_xmlnode(xmlnode*); /* delete xmlnode */
uint sizeof_node(xmlnode*); /* know summ of length of all elements in node*/
uint sizeof_next(xmlnode*);
char* node_to_str(xmlnode*); /* generate string-type xml data from xmlnode pointer */
char* next_to_str(xmlnode*);

/* xmlnode.h ends here */

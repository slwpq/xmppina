/* xmlnode.c ---
 *
 * Filename: xmlnode.c
 * Description: I'm using this, 'cause I don't understand developers of libxml2
 *                      (maybe it was developed for parsing only?)
 * Author: srbpkk
 * Created: Mon Aug 15 17:28:28 2011 (+0600)
 * Version: 0.1

 /* Code: */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "xmlnode.h"

xmlnode* new_node (char *name, char** attr, char **xmlns)
{
  if (name != NULL)
    {
      xmlnode *new = malloc (sizeof (xmlnode));
      new->name = calloc ((strlen (name)) + 1, sizeof (char));
      new->name = name;
      if (xmlns != NULL)
	{
	  new->xmlns = malloc(sizeof(attrxmlns));
	  new->xmlns->n = 0;
	  new->xmlns->pair = malloc(sizeof(char*));
	  int i=0;
	  for (i=0;xmlns[i] != NULL;i++)
	    set_xmlns(xmlns[i][0],xmlns[i][1], new);
	}
      if (attr != NULL)
	{
	  new->attr = malloc(sizeof(attrxmlns));
	  new->attr->n = 0;
	  new->attr->pair = malloc(sizeof(char*));
	  int i;
	  for (i=0;attr[i] != NULL;i++)
	    set_attr(attr[i][0],attr[i][1],new);
	}
      return new;
    }
  else
    {
      fprintf(stderr, "no name, returning pointer to NULL...\n");
      return NULL;
    }
}

void new_childnode (char *name, char** attr, char **xmlns, xmlnode* parent)
{
  xmlnode *node = new_node (name, attr, xmlns);
  insert_child (node, parent);
}

void insert_content (char *content, xmlnode * node)
{
  node->content = calloc (strlen (content)+1,sizeof(char));
  node->content = content;
}

void insert_child (xmlnode * child, xmlnode * parent)
{
  child->parent = malloc(sizeof(xmlnode));
  parent->child = malloc(sizeof(xmlnode));
  child->parent = parent;
  parent->child = child;
}

void set_xmlns (char *name, char* value, xmlnode * node)
{
  int n = ++node->xmlns->n;
  node->xmlns->pair[n] = malloc(sizeof(char*));
  node->xmlns->pair[n][0] = calloc(strlen(name)+1);
  node->xmlns->pair[n][0] = name;
  node->xmlns->pair[n][1] = calloc(strlen(value)+1);
  node->xmlns->pair[n][1] = value;
}

void set_attr(char *name, char* value, xmlnode * node)
{
  int n = ++node->attr->n;
  node->attr->pair[n] = malloc(sizeof(char*));
  node->attr->pair[n][0] = calloc(strlen(name)+1);
  node->attr->pair[n][0] = name;
  node->attr->pair[n][1] = calloc(strlen(value)+1);
  node->attr->pair[n][1] = value;
}

void delete_node (xmlnode * node)
{
  if (node->child != NULL)
    delete_node (node->child);
  free (node);
}

uint sizeof_node (xmlnode * node)
{
  uint i = 0;
  if (node->parent == NULL)
    i += strlen("<?xml version='1.0'?>");
  if (node->name != NULL)
    {
      if (node->content != NULL)
	i += strlen(node->name) * 2 + strlen(node->content) + 4;
      else
	i += strlen(node->name) + 3;
    }
  if (node->xmlns != NULL)
    {
      int c;
      for (c=0; c < node->xmlns->n; c++)
	i += strlen(node->xmlns->pair[c][0])
	  + strlen(node->xmlns->pair[c][1]) + 1;
    }
  if (node->attr != NULL)
    {
      int c;
      for (c=0; c < node->attr->n; c++)
	i += strlen(node->xmlns->pair[c][0])
	  + strlen(node->xmlns->pair[c][1]) + 1;
    }
  if (node->next != NULL)
    i += sizeof_next(node->next);
  if (node->child != NULL)
    i += sizeof_node(node->child);
  return i;
}

uint sizeof_next(xmlnode *node)
{
  int i;
  if (node->name != NULL)
    {
      if (node->content != NULL)
	i += strlen(node->name) * 2 + strlen(node->content) + 4;
      else
	i += strlen(node->name) + 3;
    }
  if (node->xmlns != NULL)
    {
      int c;
      for(c=0;c < node->xmlns->n;c++)
	i += strlen(node->xmlns->pair[c][0])
	  + strlen(node->xmlns->pair[c][1]) + 1;
    }
  if (node->attr != NULL)
    {
      int c;
      for (c=0; c < node->xmlns->n; c++)
	i += strlen(node->attr->pair[c][0])
	  + strlen(node->attr->[c][1]) + 1;
    }
  if (node->next != NULL)
    i += sizeof_next(node->next);

  return i;
}

char* node_to_str(xmlnode *node)
{
  char *xml = calloc(sizeof_node(node)+1, sizeof(char));
  if (node->parent == NULL)
    strcat(xml,"<xml version='1.0'?>");
  strcat(xml,"<");
  strcat(xml,name);
  if (node->xmlns != NULL)
    {
      int c = 0;
      for (;c<node->xmlns->n;c++)
	{
	  char *xmlns = malloc(sizeof(char));
	  sprintf(xmlns, " %s=%s", node->xmlns->pair[n][0],
		  node->xmlns->pair[n][1]);
	  strcat(xml, xmlns);
	}
    }
  if (node->attr != NULL)
    {
      int c = 0;
      for (;c<node->attr->n;c++)
	{
	  char *attr = malloc(sizeof(char));
	  sprintf(attr, " %s=%s", node->attr->pair[n][0],
		  node->xmlns->pair[n][1]);
	  strcat(xml, attr);
	}
    }
  if(node->content != NULL)
    {
      char *end = malloc(sizeof(char));
      sprintf(end, ">%s</%s>", node->content,node->name);
      strcat(xml, end);
    }
  else if (node->child != NULL)
    {
      char *end = malloc(sizeof(char));
      sprintf(end, ">%s</%s>", node_to_str(node->child), node->name);
    }
  else
    strcat(xml, "/>");
  if (node->next != NULL)
    strcat(xml, node->next);
  return xml;
}

char *next_to_str(xmlnode *next)
{
  char *xml = calloc(sizeof_next(next)+1, sizeof(xmlnode));
  strcat(xml,"<");
  strcat(xml,name);
  if (next->xmlns != NULL)
    {
      int c = 0;
      for (;c<next->xmlns->n;c++)
	{
	  char *xmlns = malloc(sizeof(char));
	  sprintf(xmlns, " %s=%s", next->xmlns->pair[n][0],
		  next->xmlns->pair[n][1]);
	  strcat(xml, xmlns);
	}
    }
  if (next->attr != NULL)
    {
      int c = 0;
      for (;c<next->attr->n;c++)
	{
	  char *attr = malloc(sizeof(char));
	  sprintf(attr, " %s=%s", next->attr->pair[n][0],
		  next->xmlns->pair[n][1]);
	  strcat(xml, attr);
	}
    }
  if(next->content != NULL)
    {
      char *end = malloc(sizeof(char));
      sprintf(end, ">%s</%s>", next->content,next->name);
      strcat(xml, end);
    }
  else
    strcat(xml, "/>");
  if (next->next != NULL)
    strcat(xml, next_to_str(next->next));
  return xml;
}

/* xmlnode.c ends here */

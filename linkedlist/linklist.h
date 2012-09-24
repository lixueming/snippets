/***************************************************************************/
/* linklist.h - Linked list header					   */
/***************************************************************************/

#ifndef __LINKLIST_H
#define __LINKLIST_H

#include <stdio.h>
#include <alloc.h>
#include <string.h>

#ifndef _NAME_MAX_LENGTH
#define _NAME_MAX_LENGTH
#define NAME_MAX_LENGTH 20
#endif

#ifndef _NODE
#define _NODE
typedef struct node *link;
typedef struct node
{
    char name[NAME_MAX_LENGTH];
    long int telnum;
    int code;
    link next_node;
} node_type;
#endif

int append_node(link *head, link *tail, link info);
int insert_node(link *head, link *tail, link p, link info);
int delete_node(link *head, link *tail, link p);
int delete_list(link *head, link *tail);

#endif
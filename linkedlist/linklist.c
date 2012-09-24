/***************************************************************************/
/* linklist.c - Linkes list library					   */
/***************************************************************************/

#include "linklist.h"

/***************************************************************************/
/* 리스트에 노드를 덧붙인다.						   */
/*									   */
/* 입력 : head, tail - 리스트의 머리와 꼬리를 가르킨다			   */
/*	  info	     - 덧붙일 정보					   */
/*									   */
/* 출력 : head, tail - 리스트의 머리와 꼬리를 가르킨다			   */
/*	  return     - 0 : 에러 없음					   */
/*		       1 : 메모리 부족 에러				   */
/*		       2 : 정보 없음					   */
/***************************************************************************/
int append_node(link *head, link *tail, link info)
{
    link t;

    if (!info)    /* 정보가 없으면 */
        return 2;

    /* 노드 할당하고, 만약 실패했으면 */
    if (!(t = (link) malloc(sizeof(node_type))))
        return 1;
    else
        if (*head)                          /* 리스트가 있으면        */
	{
	    (*tail)->next_node = t;         /* 마지막의 다음 노드는 t */
	    strcpy(t->name, info->name);    /* 정보 전송              */
	    t->telnum = info->telnum;
	    t->code = info->code;
	    t->next_node = NULL;            /* t의 다음 노드는 없다   */
	    (*tail) = t;                    /* 꼬리는 t이다           */
	}
	else                                /* 리스트가 없으면        */
	{
	    strcpy(t->name, info->name);    /* 정보 전송              */
	    t->telnum = info->telnum;
	    t->code = info->code;
	    t->next_node = NULL;            /* t의 다음 노드는 없다   */
	    *head = t;                      /* 머리 노드는 t          */
	    *tail = t;                      /* 꼬리 노드는 t          */
	}    /* if의 */

    return 0;    /* 에러 없음 */
}    /* append_node의 */

/***************************************************************************/
/* 리스트에 노드를 삽입한다.						   */
/*									   */
/* 입력 : head, tail - 리스트의 머리와 꼬리를 가르킨다			   */
/*	  p	     - 삽입할 위치					   */
/*	  info	     - 덧붙일 정보					   */
/*									   */
/* 출력 : head, tail - 리스트의 머리와 꼬리를 가르킨다			   */
/*	  return     - 0 : 에러 없음					   */
/*		       1 : 메모리 부족 에러				   */
/*		       2 : 리스트 없음					   */
/*		       3 : 정보 없음					   */
/***************************************************************************/
int insert_node(link *head, link *tail, link p, link info)
{
    link t;

    if (!(*head && *tail))    /* 리스트가 없으면 */
        return 2;

    if (!info)    /* 정보가 없으면 */
        return 3;

    /* 노드 할당하고, 만약 실패했으면 */
    if (!(t = (link) malloc(sizeof(node_type))))
        return 1;
    else
        if (p)                              /* 지정된 위치가 있으면        */
	{
	    strcpy(t->name, info->name);    /* 정보 전송                   */
	    t->telnum = info->telnum;
	    t->code = info->code;

	    t->next_node = p->next_node;    /* t의 다음 노드는 p의 다음 것 */
	    p->next_node = t;               /* p의 다음 노드는 t           */
	    if (*tail == p)                 /* 삽입 위치가 꼬리면          */
	        *tail = t;                  /* 꼬리는 t이다                */
	}
	else                                /* 지정된 위치가 없으면        */
	{
	    strcpy(t->name, info->name);    /* 정보 전송                   */
	    t->telnum = info->telnum;
	    t->code = info->code;

	    t->next_node = *head;           /* t의 다음 노드는 head        */
	    *head = t;                      /* 머리는 t이다                */
	}    /* if의 */

    return 0;    /* 에러 없음 */
}    /* insert_node의 */

/***************************************************************************/
/* 리스트에 노드를 삭제한다.						   */
/*									   */
/* 입력 : head, tail - 리스트의 머리와 꼬리를 가르킨다			   */
/*	  p	     - 삭제할 위치					   */
/*									   */
/* 출력 : head, tail - 리스트의 머리와 꼬리를 가르킨다			   */
/*	  return     - 0 : 에러 없음					   */
/*		       1 : 리스트 없음					   */
/*		       2 : 제거할 노드가 없음                              */
/***************************************************************************/
int delete_node(link *head, link *tail, link p)
{
    link t;

    if (!(*head && *tail))    /* 리스트가 없으면 */
        return 2;

    if (p)    /* 지정된 위치가 있으면  */
    {
	if (*tail == p)               /* 꼬리 노드를 지정했으면        */
	    return 2;

	if (p->next_node == *tail)    /* 꼬리 노드가 제거 대상이면     */
	    *tail = p;                /* p가 꼬리다                    */

	t = p->next_node;             /* 제거할 노드 보관              */
	p->next_node = t->next_node;  /* p의 다음 노드는 t의 다음 노드 */

	free(t);                      /* t를 제거한다                  */
    }
    else                              /* 지정된 위치가 없으면          */
    {
	t = *head;                    /* 제거 대상 노드 저장           */
	*head = t->next_node;         /* t의 다음 노드가 머리다        */
	if (!*head)                   /* 머리가 없으면                 */
	    *tail = NULL;             /* 꼬리도 없앤다                 */
	free(t);                      /* t를 제거한다                  */
    }    /* if의 */

    return 0;    /* 에러 없음 */
}    /* delete_node의 */

/***************************************************************************/
/* 리스트 제거한다.							   */
/*									   */
/* 입력 : head, tail - 리스트의 머리와 꼬리를 가르킨다			   */
/*									   */
/* 출력 : head, tail - 리스트의 머리와 꼬리를 가르킨다			   */
/*	  return     - 0 : 에러 없음					   */
/*		       1 : 리스트 없음					   */
/***************************************************************************/
int delete_list(link *head, link *tail)
{
    if (*head)                                   /* 리스트가 있으면 */
        while (!delete_node(head, tail, NULL))   /*  모두 제거      */
	    ;
    else                                         /* 리스트가 없으면 */
        return 1;

    return 0;    /* 에러 없음 */
}
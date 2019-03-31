#ifndef STOS_H
#define STOS_H

typedef struct tagStack
{
	char cKey;
	tagStack* pNext;
} Stack;  //typ stosowy

Stack* InitStack ();
//void InitStack( Stack** pStack);  tak tez moznaby to zrobic

void push ( char c, Stack** pStack );
char pop ( Stack** pStack );
char top ( Stack* pStack );
void del ( Stack** pStack );
int isEmpty ( Stack* pStack );
//dwie gwiazdki sa tam gdzie funkcja modyfikuje stos, oznacza ona 'wskaznik do wskaznika!!
void RemoveStack ( Stack** );

#endif

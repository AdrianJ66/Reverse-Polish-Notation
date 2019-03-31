#ifndef DSTOS_H
#define DSTOS_H

typedef struct tagDStack
{
	double cKey;
	tagDStack* pNext;
} DStack;  //typ stosowy

DStack* dInitStack ();
//void InitStack( Stack** pStack);  tak tez moznaby to zrobic

void dpush ( double c, DStack** pStack );
double dpop ( DStack** pStack );
double dtop ( DStack* pStack );
void ddel ( DStack** pStack );
int disEmpty ( DStack* pStack );
//dwie gwiazdki sa tam gdzie funkcja modyfikuje stos, oznacza ona 'wskaznik do wskaznika!!
void dRemoveStack ( DStack** pStack );

#endif
#include "dstos.h"
#include <iostream>
#include <stdlib.h>
#include <memory.h>
using namespace std;


DStack* dInitStack ()
{
	return NULL;
}

void dRemoveStack ( DStack** pStack )
{
	while (!disEmpty ( *pStack ))
		ddel ( pStack );
	*pStack = NULL;
}

void dpush ( double c, DStack** pStack )
{
	DStack* v = (DStack*)malloc ( sizeof ( DStack ) ); //malloca trzeba zrzutowac na typ na jaki ma wskazywac wskaznik

	if (v)   //if(v != NULL);
	{
		memset ( v, 0, sizeof ( DStack ) ); //jak dostac sie do pol struktury
									 //(*v).cKey;  !!!musi byc w nawiasie bo kropka ma silniejszy priorytet od gwizdki
		v->cKey = c; //operator strzalki, bo v wskazuje, zamiast tego wyzej
					 //dowiazanie
		v->pNext = *pStack;
		*pStack = v;
	}
	else
		perror ( "ERROR dpush: DStack overflow!!" );
}

double dpop ( DStack** pStack ) // zdejmij i zwroc szczyt
{
	if (!disEmpty ( *pStack )) {
		double c = dtop ( *pStack );
		ddel ( pStack );
		return c;
	}
	perror ( "ERROR dpop: Dstack underflow" );
	return 0;
}

double dtop ( DStack* pStack )
{
	if (!disEmpty ( pStack ))
		//return s[sHead - 1];
		return pStack->cKey;
	return 0;
}

void ddel ( DStack** pStack )
{
	if (!disEmpty ( *pStack ))
	{
		DStack* v = *pStack;
		*pStack = v->pNext; //pStack = pStack -> pNext;
		free ( v ); //v ma nieznana wartosc
	}
	//else
		//cout << "ERROR ddel: DStack underflow!! \n";
}

int disEmpty ( DStack* pStack )
{
	//return !sHead;
	return !pStack;
}



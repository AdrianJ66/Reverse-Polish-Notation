#include "stos.h"
#include <iostream>
#include <stdlib.h>
#include <memory.h>
using namespace std;

//#define MAXSTACK 20
// ZAKOMENTOWANE RZECZY SA Z IMPLEMENTACJI TABLICOWEJ A RESZTA Z DYNAMICZNEJ!!

//zdefiiniuj strukture danych dla stosu
//char s[MAXSTACK] = { 0 }
//int sHead = 0; // wskaznik szczytu stosu -> pierwszy wolny w tablicy


Stack* InitStack ()
{
	return NULL;
}

void RemoveStack ( Stack** pStack )
{
	while (!isEmpty ( *pStack ))
		del ( pStack );
	*pStack = NULL;
}

void push ( char c, Stack** pStack )
{
	/*if (sHead < MAXSTACK)
		s[sHead++] = c;*/
	Stack* v = (Stack*)malloc ( sizeof ( Stack ) ); //malloca trzeba zrzutowac na typ na jaki ma wskazywac wskaznik


	if (v)   //if(v != NULL);
	{
		memset ( v, 0, sizeof ( Stack ) ); //jak dostac sie do pol struktury
		//(*v).cKey;  !!!musi byc w nawiasie bo kropka ma silniejszy priorytet od gwizdki
		v->cKey = c; //operator strzalki, bo v wskazuje, zamiast tego wyzej
					//dowiazanie
		v->pNext = *pStack;
		*pStack = v;
	}
	else
		perror ( "ERROR push: Stack overflow!!" );
}

char pop ( Stack** pStack ) // zdejmij i zwroc szczyt
{
	if (!isEmpty ( *pStack )) {
		char c = top ( *pStack );
		del ( pStack );
		return c;
	}
	perror ( "ERROR pop: stack underflow" );
	return 0;
}

char top ( Stack* pStack )
{
	if (!isEmpty ( pStack ))
		//return s[sHead - 1];
		return pStack->cKey;
	return 0;
}

void del ( Stack** pStack )
{
	if (!isEmpty ( *pStack ))
	{
		//sHead--;
		Stack* v = *pStack;
		*pStack = v->pNext; //pStack = pStack -> pNext;
		free ( v ); //v ma nieznana wartosc
	}
	else
		cout << "ERROR del: Stack underflow!! \n";
}

int isEmpty ( Stack* pStack )
{
	//return !sHead;
	return !pStack;
}



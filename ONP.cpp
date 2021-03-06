
#include <stdio.h>
#include "stos.h"
#include "dstos.h"
#include <math.h>
#include <iostream>
using namespace std;

double GetNum ();    //czyta liczbe od lewej i oblicza wartosc
char GetOper (); //czyta operator
void SkipSpaces ();
int isDigit ( char c );
int isOper ( char c );
int prior ( char oper ); //odczytuje priorytet operatora
double Eval ( char oper, double arg1, double arg2 );
//void Calc (); //kalkulator ONP
double Calc (); //kalkulator ONP

#define DOT '.'

int main ( int argc, char* argv[] )
{
	printf ( "Podaj wyrazenie: " );
	double wynik = Calc ();
	printf ( "Wynik: %.2f\n\n", wynik );

	return 0;
}


//-------------------------------------------------------------

double GetNum ()    //czyta liczbe od lewej i oblicza wartosc 
{								//NIE UWZGLEDNIA ZNAKU LICZBY !!!!
	char c;
	double res = 0;
	
	SkipSpaces ();
	
	while (isDigit ( c = getchar () ))
		res = res * 10 + ( c - '0' );
	//sprawdz czy jest znak '.'
	if (c == DOT)
	{
		double coef = 0.1;
		while (isDigit ( c= getchar() ))
		{
			res += coef * ( c - '0' );
			coef *= 0.1;
		}
	}
	ungetc ( c, stdin );
	//wczytac czesc ulamkowa
		
	return res;
}

//-------------------------------------------------------------


char GetOper () //czyta operator
{
	SkipSpaces ();
	return getchar ();
}

void SkipSpaces ()
{
	char c;
	//wczytywac dopoki jest spacja
	while( ( c = getchar () ) == ' ' );
	//oddac ostatni znak do bufora klawiatury
	ungetc ( c, stdin );
}

int isDigit( char c )
{
	return ( c >= '0' ) && ( c <= '9' );
}

int isOper( char c )
{
	switch( c )
	{
	//case '(':
	//case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '^': return 1;
	}
	return 0;
}

//-------------------------------------------------------------

int prior ( char cOper ) //odczytuje priorytet operatora
{
	switch( cOper )
	{
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	}
	return 0;
}

//-------------------------------------------------------------

double Eval ( char cOper, double arg1, double arg2 )
{
	//switch
	switch (cOper)
	{
	case '+': return arg1 + arg2;
	case '-': return arg1 - arg2;
	case '*': return arg1 * arg2;
	case '/': if( arg2 >= 1e-14 ) ///popraw --- dzielenie przez ujemna
	{
		return arg1 / arg2;
	}
			  else
		cout << "ERROR: Division by 0!! \n\n";

	case '^': return pow ( arg1, arg2 ); //uzywac tylko do double!!!
	}
	return 0;
}

//-------------------------------------------------------------

//void Calc () //kalkulator
//{
//	//alg ONP
//
//	char c;
//	Stack* ppStack = InitStack ();
//	DStack* pStack = dInitStack ();
//
//
//	printf ( "%0.2lf", GetNum () );
//
//	while (isOper ( c = GetOper () ))
//	{
//		while (prior ( c ) <= prior ( dtop ( pStack ) ))
//		{
//			putchar ( dpop ( &pStack ) );
//		}
//		dpush ( c, &pStack );
//		printf ( "% 0.2lf", GetNum () );
//
//	}
//
//	while (!disEmpty ( pStack ))
//		putchar ( dpop ( &pStack ) );
//
//	dRemoveStack ( &pStack ); //To jest implementacja na charach beznawiasowa, teraz trzeba zrobic to na double'u
//}

//-------------------------------------------------------------

//double Calc() //kalkulator wartosci wyrazenia
//{
//	//alg ONP
//
//	char c;
//	Stack* opStack = InitStack(); //stos operatorow
//	DStack* pStack = dInitStack(); //stos liczbowy
//
//
//	//printf("%0.2lf", GetNum());
//	dpush ( GetNum (), &pStack );
//	printf ( "%f ", dtop ( pStack ) ); //wypiasuje liczbe ze stosu
//
//	while (isOper(c = GetOper() ))
//	{
//		while (prior(c) <= prior(top(opStack)))
//		{
//			char oper = pop ( &opStack );	// pobiera operator
//
//			printf ( " %c ", oper );	// wyswietla operator
//			
//			double arg2 = dpop ( &pStack );		//taka kolejnosc ze wzgledu na kolejnosc obliczen, rownie dobrze w Eval moznaby podac najpierw arg2, a dopiero pozniej arg1
//			double arg1 = dpop ( &pStack );
//
//			dpush ( Eval ( oper, arg1, arg2 ), &pStack );
//		}
//		push(c, &opStack);
//		dpush ( GetNum (), &pStack );
//
//		printf ( "%f ", dtop ( pStack ) );		// wyswietlamy liczbe
//	}
//	
//	while (!isEmpty ( opStack )) //dzialam za pomoca pozostalych jeszcze na stosie operatorow, w celu obliczenia wyniku wyrazenia, a nastepnie zapisuje jej w stosie liczbowym
//	{	
//		char oper = pop ( &opStack );	// pobiera operator
//		
//		printf ( " %c ", oper );// wyswietla operator
//		
//		double arg2 = dpop ( &pStack );
//		double arg1 = dpop ( &pStack );
//
//		dpush ( Eval ( oper, arg1, arg2 ), &pStack );
//	}
//
//	double res = dtop ( pStack );
//
//	RemoveStack ( &opStack );
//	dRemoveStack ( &pStack );
//	
//	cout << endl << "Wynik obliczen to: " << res << endl;
//	
//	return res; //to jest implementacja beznawiasowa na doublu, dziala
//}

///Co zrobic?!??!
// Zmien Calc na double!! i znowdyfikuj calc tak zeby byl kalkulatorem beznawiasowym
// np 1+2*3-4
//musimy miec 2 stosy, stos liczbowy i stos operatora
//liczb od razu nie wypisauje tylko wrzucam na stos
//potem robimy zgodnie z onp
//pozniej trzeba zwrocic uwage na to ze ostatni sczytany arg jest drugim arg w dzialaniu co ma znaczenie dla odejmowania i dzielenia!!

//-------------------------------------------------------------

double Calc () //kalkulator wartosci wyrazenia
{
	//alg ONP

	char c;
	Stack* opStack = InitStack (); //stos operatorow
	DStack* pStack = dInitStack (); //stos liczbowy

	while (( c = getchar () ) == '(')
		push ( c, &opStack );
	ungetc ( c, stdin );

	dpush ( GetNum(), &pStack );
	

	while (isOper ( c = GetOper () ))
	{
		while (prior ( c ) <= prior ( top ( opStack ) ))
		{
			double arg2 = dpop ( &pStack );
			dpush ( Eval ( pop ( &opStack ), dpop ( &pStack ), arg2 ), &pStack );
		}
		push ( c, &opStack );

		while (( c = getchar () ) == '(')
			push ( c, &opStack );
		ungetc ( c, stdin );

		dpush ( GetNum (), &pStack );

		while (( c = getchar () ) == ')')
		{
			while (top ( opStack ) != '(') 			//wykonuje dzilanie dla operatorow rozniych od nawiasu otwierajacego 
			{
				double arg2 = dpop ( &pStack );
				dpush ( Eval ( pop ( &opStack ), dpop ( &pStack ), arg2 ), &pStack );
			}
			pop ( &opStack );		//, a nastepnie nawias otwierajacy zostanie zdjety ze stosu
		}
		ungetc ( c, stdin );
	}

	while (!isEmpty ( opStack )) //dzialam za pomoca pozostalych jeszcze na stosie operatorow, w celu obliczenia wyniku wyrazenia, a nastepnie zapisuje jej w stosie liczbowym
	{
			double arg2 = dpop ( &pStack );
			dpush ( Eval ( pop ( &opStack ), dpop ( &pStack ), arg2 ), &pStack );
	}

	double res = dtop ( pStack ); //zapisuje liczbe ze szczytu sotsu liczbowego aby program podaj ja jako wartosc wyrazenia ONP po usunieciu struktury stosu

	RemoveStack ( &opStack ); //czyszcze pamiec usuwajac stosy po wykonaniu programu
	dRemoveStack ( &pStack );

	return res;
}
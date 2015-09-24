#include "StdAfx.h"

#include "ekran.h"

void gotoxy(int x, int y)
{
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void HideCursor()
{
    ::HANDLE hConsoleOut =::GetStdHandle( STD_OUTPUT_HANDLE );
    ::CONSOLE_CURSOR_INFO hCCI;
    ::GetConsoleCursorInfo( hConsoleOut, & hCCI );
    hCCI.bVisible = FALSE;
    ::SetConsoleCursorInfo( hConsoleOut, & hCCI );
}

ekran::ekran(int x, int y, int _szerokosc, int _wysokosc, char _tlo)
{
	poczatek_ekranu.x = x;
	poczatek_ekranu.y = y;
	szerokosc = _szerokosc;
	wysokosc= _wysokosc;

	tlo=_tlo;
	tresc.assign(szerokosc * (wysokosc+1) , tlo);
	
	for(int i = 0 ; i < wysokosc ; i++)
		tresc[(i+1) * szerokosc - 1] = '\n';
}
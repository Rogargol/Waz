#pragma once

#ifndef EKRAN_H
#define EKRAN_H

#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;


struct wspolrzedne
{
	int x,y;
};


//FUNKCJA USTAWIAJACA KURSOR NA POZADANYCH WSPOLRZEDNYCH
void gotoxy(int x, int y);


//FUNKCJA UKRYWAJACA KURSOR
void HideCursor();



//KLASA EKRANU ROBOCZEGO ODPOWIEDZIALNA ZA WYSWIETLANIE NA EKRANIE. KLASA PRZECHOWUJE WIADOMOSCI O TYM CO MA BYC WYSWIETLONE W STRINGU tresc I WYSWIETLA WSZYSTKIE ELEMENTY ZA JEDNYM RAZEM
class ekran
{
	wspolrzedne poczatek_ekranu;
	string tresc;
public:
	char tlo;
	int szerokosc, wysokosc;


	//FUNKCJA KTORA ZAPELNIA STRING BEDACY BUFOREM EKRANU ZNAKIEM ZE ZMIENNEJ tlo I DODAJACA ZNAKI PRZEJSCIA DO NOWEJ LINI NA KONCU WERSU
	void wyczysc()
	{
		string text;
		text = tlo;
		for( int i=0 ; i < szerokosc*wysokosc ; i++)
			tresc.replace(i , text.length() , text);
		
		for(int i = 0 ; i < wysokosc ; i++)
			tresc[(i+1) * szerokosc - 1] = '\n';
	}

	// FUNKCJA WYSWIETLAJACA TRESC STRINGU BEDACEGO BUFOREM EKRANU
	void wyswietl()
	{
		gotoxy(poczatek_ekranu.x,poczatek_ekranu.y);
		cout<< tresc << flush ;
	}

	// FUNKCJA WSTAWIAJACA ZNAK (ZNAKI) W WYBRANE MIEJSCE DO STRINGU BEDACEGO BUFOREM EKRANU:
	void wstaw(int x , int y , string tekst)
	{
		tresc.replace( (szerokosc *y) + x , tekst.length() , tekst);
	}

	// KONSTRUKTOR Z DOMYŒLNYMI WARTOSCIAMI WIELKOSCI EKRANU ROBOCZEGO I WSPOLRZEDNYCH POCZATKOWYC:
	ekran(int x=1, int y=1, int _szerokosc=80, int _wysokosc=20, char _tlo =' ');   

};


#endif
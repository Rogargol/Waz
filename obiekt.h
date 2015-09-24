#pragma once
#ifndef OBIEKT_H
#define OBIEKT_H
#include "ekran.h"
#include <list>


enum KIERUNEK
{
	GORA,
	DOL,
	LEWO,
	PRAWO
};



//////////////////////////////////////////////////////////////////////////////////////////////////////
//KLASA PODSTAWOWA DLA OBIEKTOW
class obiekt
{
protected:
	ekran *aktualny_ekran;								//WSKAZNIK DO EKRANU NA KTORYM OBIEKT BEDZIE WYSWIETLANY
	list <wspolrzedne> polozenie;						//LISTA STRUKTUR WSPOLRZEDNE, PRZECHOWUJACA POLOZENIA POSZCZEGOLNYCH ELEMENTOW OBIEKTU
	list <wspolrzedne> ::iterator iterator_polozenie;
	int wielkosc, ilosc_ruchow;
	int ostatni_czas, poprzedni_ruch, nastepny_ruch;	//ZMIENNE POMOCNICZE ODPOWIADAJACE ZA PLYNNOSC RUCHOW WZGLEDEM CZASU
	char znak;
	int predkosc;


public:
		bool do_usuniecia;
	string nazwa;
	wspolrzedne zwroc_wspolrzedne();
 	int zwroc_predkosc(){return predkosc;}
	virtual void rysuj();						//WYSYLA DO EKRANU WSPOLRZEDNE I ZNAKI KTORE MAJA REPREZENTOWAC OBIEKT WIZUALNIE
	virtual void losuj(){}
	virtual void ruch(int aktualny_czas){}		//FUNKCJA ODPOWIADAJACA ZA SPRAWDZENIE CZY OBIEKT MA WYKONAC KOLEJNY RUCH I EWENTUALNE WYKONANIE GO
	virtual void sprawdz_klawisz(int klawisz){} //FUNKCJA SPRAWDZA CZY WCISNIETY KLAWISZ POWODUJE ZMIANE KIERUNKU DANEGO WEZA
	virtual void zjedz_owoc(int _predkosc){}	//FUNKCJA URUCHAMIANA W MOMENCIE "ZJEDZENIA OWOCU" PRZEZ WEZA
	virtual int sprawdz(wspolrzedne xy);		//FUNKCJA SPRAWDZA CZY NA PODANYCH WSPOLRZEDNYCH ZNAJDUJE SIE JAKIS ELEMENT OBIEKTU
	int sprawdz_siebie(); 

};



///////////////////////////////////////////////////////////////////////////////////////////////////////
class waz : public obiekt
{
	KIERUNEK AKTUALNY_KIERUNEK, kierunek;
public:
	int	klawisz_GORA,  
		klawisz_DOL, 
		klawisz_LEWO,
		klawisz_PRAWO;

	waz(ekran *_ekran, int x, int y, int _wielkosc,	int kl_GORA, int kl_DOL, int kl_LEWO, int kl_PRAWO, KIERUNEK _KIERUNEK, char _znak, int _predkosc, string _nazwa);
	virtual void ruch(int czas);
	virtual void sprawdz_klawisz(int klawisz);
	virtual void zjedz_owoc(int _predkosc);

};


////////////////////////////////////////////////////////////////////////////////////////////////////////
class owoc : public obiekt
{
int czas_trwania;
char animacja[8];		//TABLICA PRZECHOWUJACA ZNAKI ODPOWIADAJACE GRAFICZNEJ REPREZENTACJI POSZCZEGOLNYCH "KLATEK ANIMACJI OWOCU"
public:


	owoc(ekran *_ekran, int _predkosc, int czas);
	virtual void ruch(int czas);
	virtual void losuj();
	void ustaw(wspolrzedne xy);
	virtual int sprawdz(wspolrzedne xy);
};


#endif
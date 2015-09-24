#ifndef WAZ_H
#define WAZ_H

#include "stdafx.h"

#include <conio.h>
#include "ekran.h"
#include "obiekt.h"
#include <time.h>
#include <list>

list<obiekt *> lista;	//GLOWNA LISTA WSKAZNIKOW DO OBIEKTOW
	ekran monitor;		


//FUNKCJA SPRAWDZAJACA CZY ZACHODZI KOLIZJA POMIEDZY OBIEKTAMI, ZWRACA WSKAZNIK DO OBIEKTU NA KTORY COS "NAJECHALO", 
//W ARGUMENCIE MA ITERATOR LISTY WSKAZNIKOW DO OBIEKTU USTAWIONY NA OBIEKT KTORY SPRAWDZAMY CZY NA COS "NAJECHAL" 
obiekt *sprawdz_kolizje(list<obiekt *>::iterator iter);


//FUNKCJA STERUJE TWORZENIEM NOWYCH OWOCOW W ZALEZNOSCI OD CZASU I USUWANIEM "ZJEDZONYCH" OWOCOW
void steruj_owocami(int czas);

#endif
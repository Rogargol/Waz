// Waz.cpp : Defines the entry point for the console application.
//
#include "StdAfx.h"
#include "waz.h"




int _tmain(int argc, _TCHAR* argv[])
{
	owoc *wsk_owoc;
	waz *wsk_waz;
	obiekt *wsk_obiekt;
	wspolrzedne tymczas;
	srand( time( NULL ) );
	list<obiekt *>::iterator i;
	list<obiekt *>::iterator i2;
	int klawisz = 77;
	
	HideCursor();

	waz waz1(&monitor, 10,2,5,72,80,75,77,PRAWO,178,200,"WAZ PIERWSZY"),
		//waz2(&monitor, 30,12,5,int('i'),int('k'),int('j'),int('l'),LEWO,177,200,"WAZ DRUGI"),
		waz3(&monitor, 30,3,5,int('w'),int('s'),int('a'),int('d'),LEWO,176,200,"WAZ DRUGI");
		//waz4(&monitor, 10,11,5,int('t'),int('g'),int('f'),int('h'),PRAWO,'#',200,"WAZ CZWARTY");

	lista.push_back(&waz1);
	//lista.push_back(&waz2);
	lista.push_back(&waz3);
	//lista.push_back(&waz4);

	while(klawisz != 27)					//GLOWNA PETLA WYKONYWANA DO CZASU NACISNIECIA KLAWICZA ESCAPE
	{
	
		if(kbhit())
		{
			klawisz=getch();
			for( i = lista.begin(); i != lista.end(); i++ )
			{
				(*i)->sprawdz_klawisz(klawisz);						//JESLI NACISNIETO KLAWISZ, WYSYLAMY JEGO WARTOSC DO POSZCZEGOLNYCH OBIEKTOW
			}
		}
		monitor.wyczysc();
	
		steruj_owocami(clock());

		for( i = lista.begin(); i != lista.end(); i++ )				//PETLA ODPOWIEDZIALA ZA PORUSZANIE OBIEKTOW I SPRAWDZENIE WSZELKICH KOLIZJI
		{

			(*i)->ruch(clock());

			if((*i)->sprawdz_siebie())
			{
				gotoxy(10,10);		cout<<(*i)->nazwa<<" SAM SIE ZJADL!";
				getch();
				i=lista.erase(i);
				break;
			}

			wsk_obiekt=sprawdz_kolizje(i);

			if(wsk_obiekt!=NULL)
			{
				
				wsk_owoc = dynamic_cast <owoc*> (wsk_obiekt);				//JESLI OBIEKT NA KTORY "NAJECHANO" JEST KLASY OWOC
				if(wsk_owoc)										
				{

					(*i)->zjedz_owoc(wsk_obiekt->zwroc_predkosc());

					for(i2=lista.begin(); i2!=lista.end(); i2++)
						if(*i2 == wsk_obiekt)
						{

							(*i2)->do_usuniecia=TRUE;
							lista.erase(i2);
							steruj_owocami(clock());
							break;
						}
				}

				else
				{

					wsk_waz = dynamic_cast <waz*> (wsk_obiekt);				//JESLI OBIEKT NA KTORY "NAJECHANO" JEST KLASY WAZ
					if(wsk_waz)
					{
						for(i2=lista.begin(); i2!=lista.end(); i2++)
							if(*i2 == wsk_obiekt)
							{	

								gotoxy(15,20); cout<<"WAZ: "<<(*i)->nazwa<<" WPADL NA: "<<sprawdz_kolizje(i)->nazwa<<" I ODPADA Z GRY!";
								getch();
								i=lista.erase(i);
								break;
				
							}
					}
				}
				
			}
					
			(*i)->rysuj();
		}
		
		monitor.wyswietl();
	}

	gotoxy(10,10);
	cout<<"Czas gry: "<<clock()<<", jednostki na sekunde: "<<CLOCKS_PER_SEC;
	getch();
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
obiekt *sprawdz_kolizje(list<obiekt *>::iterator iter)
{
	obiekt *wskaznik;
	list<obiekt *>::iterator i;

	for( i = lista.begin(); i != lista.end(); i++ )
	{				
	
		if(iter!=i)
			if((*i)->sprawdz((*iter)->zwroc_wspolrzedne()))
			{
				wskaznik = *i;
				return wskaznik;
			}
	}

	return NULL;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////// 
void steruj_owocami(int czas)
{
	static list<owoc > lista_owoce;
	list <owoc>::iterator iter_owoc;
	list<obiekt *>::iterator i;

	static int ilosc_owoce, ostatni_czas=0, czas_cyklu=0;
	
	if(lista_owoce.size() > 0)
	{
		
		for(iter_owoc=lista_owoce.begin(); iter_owoc!=lista_owoce.end(); iter_owoc++)
			if(iter_owoc->do_usuniecia==TRUE)
			{
				lista_owoce.erase(iter_owoc);
				break;
			}
	}
	
	
	if(ostatni_czas + czas_cyklu <= czas)
	{

		czas_cyklu=(rand() % 4000);
		ilosc_owoce= rand() % 6 + 1;  

		if(ilosc_owoce > lista_owoce.size())
		{

			lista_owoce.push_back(owoc(&monitor, (rand()%470)+30, clock()));
			iter_owoc=lista_owoce.end(); --iter_owoc;

			lista.push_back(&(*iter_owoc));

			i=lista.end(); --i;

			(*i)->losuj();

							
			while(sprawdz_kolizje(i)!=NULL)
				(*i)->losuj();

		}

	ostatni_czas=czas;
	}
}
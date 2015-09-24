#include "StdAfx.h"
#include "obiekt.h"



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void obiekt :: rysuj()
{
	string _znak;
	_znak = znak;
	_znak +=znak;
	for(iterator_polozenie = polozenie.begin(); iterator_polozenie != polozenie.end() ; iterator_polozenie++)
		aktualny_ekran -> wstaw(iterator_polozenie->x*2 , iterator_polozenie->y, _znak);

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int obiekt::sprawdz(wspolrzedne xy)
{
	list <wspolrzedne>::iterator i;
	
	if(wielkosc>1)
	{
		for( i = polozenie.begin(); i != polozenie.end(); i++ )
		{
			if(i->x == xy.x && i->y == xy.y)
				return 1;
		}
	}
	else
	{
		i = polozenie.begin();
		if(i->x == xy.x && i->y == xy.y)
			return 1;
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int obiekt::sprawdz_siebie()
{
	if(wielkosc>1)
	{
		list <wspolrzedne>::iterator i;
		i=polozenie.begin();
		wspolrzedne xy = *i;
		for(++i; i != polozenie.end(); i++ )
		{
			if(i->x == xy.x && i->y == xy.y)
				return 1;
		}
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wspolrzedne obiekt::zwroc_wspolrzedne()
{
	list <wspolrzedne>::iterator inter;
	inter = polozenie.begin();
	return *inter;
}

/////////////##########################################################################################################//////////////////
void waz::ruch(int czas)
{
	list <wspolrzedne>::iterator inter;
	inter=polozenie.end();
	--inter;--inter;
	if(poprzedni_ruch + predkosc <= czas)
	{

		for(iterator_polozenie=polozenie.end(), --iterator_polozenie; inter != polozenie.begin(); --iterator_polozenie, --inter)
		{
			iterator_polozenie->x = inter->x;
			iterator_polozenie->y = inter->y;
		}
		
		iterator_polozenie=polozenie.begin();
		++iterator_polozenie;
		inter=polozenie.begin();
		iterator_polozenie->x = inter->x;
		iterator_polozenie->y = inter->y;
		
		iterator_polozenie=polozenie.begin();
		
		
		switch (kierunek)
		{
		case GORA:
			--iterator_polozenie->y;
			if(iterator_polozenie->y == -1)
				iterator_polozenie->y = aktualny_ekran->wysokosc-1;
			AKTUALNY_KIERUNEK=GORA;
			break;

		case DOL:
			++iterator_polozenie->y;
			if(iterator_polozenie->y > aktualny_ekran->wysokosc-1)
				iterator_polozenie->y = 0;
			AKTUALNY_KIERUNEK=DOL;
			break;

		case LEWO:
			--iterator_polozenie->x;
			if(iterator_polozenie->x <= 0)
				iterator_polozenie->x = (aktualny_ekran->szerokosc/2)-2;
			AKTUALNY_KIERUNEK=LEWO;
			break;

		case PRAWO:
			++iterator_polozenie->x;
			if(iterator_polozenie->x > (aktualny_ekran->szerokosc/2)-2)
				iterator_polozenie->x=1;
			AKTUALNY_KIERUNEK=PRAWO;
			break;
		}
	
		poprzedni_ruch=poprzedni_ruch+ (int(((czas-poprzedni_ruch)/predkosc))*predkosc);

	}
	
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void waz::sprawdz_klawisz(int klawisz)
{
	if(klawisz==klawisz_GORA)
	{		
				if(AKTUALNY_KIERUNEK!=DOL)
				kierunek=GORA;
	}

	if(klawisz==klawisz_DOL)
	{	
				if(AKTUALNY_KIERUNEK!=GORA)
					kierunek=DOL;
	}
			
	if(klawisz==klawisz_PRAWO)
	{	
				if(AKTUALNY_KIERUNEK!=LEWO)
					kierunek=PRAWO;
	} 
			
	if(klawisz==klawisz_LEWO)
	{	
				if(AKTUALNY_KIERUNEK!=PRAWO)
					kierunek=LEWO;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void waz::zjedz_owoc(int _predkosc)
	{
		wspolrzedne xy;
		list <wspolrzedne>::iterator i;
		i = polozenie.end();
		--i;
		xy.x=(*i).x;
		xy.y=(*i).y;
		polozenie.push_back(xy);
		++wielkosc;
		predkosc=_predkosc;

	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
waz::waz(ekran *_ekran, int x, int y, int _wielkosc, int kl_GORA, int kl_DOL, int kl_LEWO, int kl_PRAWO, KIERUNEK _KIERUNEK, char _znak, int _predkosc, string _nazwa)
{
	do_usuniecia=FALSE;
	nazwa=_nazwa;
	wspolrzedne tymczasowe;
	klawisz_GORA=kl_GORA;
	klawisz_DOL=kl_DOL; 
	klawisz_LEWO=kl_LEWO;
	klawisz_PRAWO=kl_PRAWO;
	
	znak=_znak;
	predkosc=_predkosc;
	poprzedni_ruch=0;
	nastepny_ruch=predkosc;
	ilosc_ruchow=0;
	AKTUALNY_KIERUNEK=_KIERUNEK;
	kierunek=_KIERUNEK;
	wielkosc=_wielkosc;
	aktualny_ekran = _ekran;
	
	tymczasowe.x=x;
	tymczasowe.y=y;
	polozenie.push_back(tymczasowe);
	
	switch (kierunek)
		{
		case GORA:
			++tymczasowe.y;
			break;

		case DOL:
			--tymczasowe.y;
			break;

		case LEWO:
			++tymczasowe.x;
			break;

		case PRAWO:
			--tymczasowe.x;
			break;
		}
	
	
	
	for(int i = 1 ; i < wielkosc ; i++)
	{  
		polozenie.push_back(tymczasowe);
	}

}

////################################################################################################//

owoc::owoc(ekran *_ekran, int _predkosc, int czas)
{
	wspolrzedne tymczasowe;
	do_usuniecia=FALSE;
	nazwa="OWOC";
	predkosc=_predkosc;
	poprzedni_ruch=czas;
	nastepny_ruch=predkosc;
	ilosc_ruchow=1;
	wielkosc=1;
	aktualny_ekran = _ekran;
	animacja[0]=176;//'O';
	animacja[1]=177;//')';
	animacja[2]=178;//'|';
	animacja[3]=177;//'(';
	animacja[4]=176;//'O';
	animacja[5]=' ';
	animacja[6]='|';
	animacja[7]=')';
	znak=animacja[0];
	tymczasowe.x=1;
	tymczasowe.y=1;
	polozenie.push_back(tymczasowe);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void owoc::losuj()
{

	wspolrzedne tymczasowe; 
	tymczasowe.x=( rand() % ((aktualny_ekran->szerokosc-3)/2)) +1;
	tymczasowe.y=( rand() % (aktualny_ekran->wysokosc-1) ) + 1;
	polozenie.clear();
	polozenie.push_back(tymczasowe);

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
int owoc::sprawdz(wspolrzedne xy)
{
	list <wspolrzedne>::iterator i;
	i = polozenie.begin();
	
	if(i->x == xy.x && i->y == xy.y)
		return 1;

	return 0;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////
void owoc::ruch(int czas)
{

	if(poprzedni_ruch + predkosc <= czas)
	{
		znak=animacja[(ilosc_ruchow%6)];
			
		poprzedni_ruch=poprzedni_ruch+ (int(((czas-poprzedni_ruch)/predkosc))*predkosc);

		++ilosc_ruchow;
	}
			
}

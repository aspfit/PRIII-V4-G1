#include<iostream>
using namespace std;

class Vrijeme{
	int _sati;
	int _minute;
	int _sekunde;
public:
	Vrijeme(int sati=0, int minute = 0, int sekunde = 0) {
		_sati = sati;
		_minute = minute;
		_sekunde = sekunde;
	}
	friend ostream& operator<<(ostream&, Vrijeme&);
	Vrijeme& operator+(int minute) {
		_minute += minute;
		while (_minute >= 60) {
			_minute /= 60;
			_sati++;
		}
		return *this;
	}
	bool prviRanije(const Vrijeme& nekoVrijeme) {
		if (_sati < nekoVrijeme._sati)
			return true;
		else if (_sati > nekoVrijeme._sati)
			return false;
		else {
			if (_minute < nekoVrijeme._minute)
				return true;
			else if (_minute > nekoVrijeme._minute)
				return false;
			else {
				if (_sekunde < nekoVrijeme._sekunde)
					return true;
				else if (_sekunde > nekoVrijeme._sekunde)
					return false;
				else
					false;
			}
		}
	}
};
ostream& operator<<(ostream& COUT, Vrijeme& nekoVrijeme) {
	COUT << nekoVrijeme._sati << ":" << nekoVrijeme._minute << ":" << nekoVrijeme._sekunde;
	return COUT;
} 

class Let{
	static const  int _oznakaSize = 10;
	char _oznaka[_oznakaSize];
	char* _odrediste;
	int _brIzlazneKapije;
	Vrijeme _vrijemePolijetanja;
	int _trajanje;
	int _kasnjenje;

public:
	Let(char oznaka[], char * odrediste, int brIzlazneKapije, Vrijeme &vrijemePolijetanja, int trajanje = 0, int kasnjenje = 0):_vrijemePolijetanja(vrijemePolijetanja),
	_brIzlazneKapije(brIzlazneKapije), _trajanje(trajanje), _kasnjenje(kasnjenje){
		strncpy_s(_oznaka, oznaka, _TRUNCATE);
		_odrediste = new char[strlen(odrediste) + 1];
		strcpy_s(_odrediste, strlen(odrediste) + 1, odrediste);
	}
	Let(Let &nekiLet) :_vrijemePolijetanja(nekiLet._vrijemePolijetanja),
		_brIzlazneKapije(nekiLet._brIzlazneKapije), _trajanje(nekiLet._trajanje), _kasnjenje(nekiLet._kasnjenje) {
		strncpy_s(_oznaka, nekiLet._oznaka, _TRUNCATE);
		_odrediste = new char[strlen(nekiLet._odrediste) + 1];
		strcpy_s(_odrediste, strlen(nekiLet._odrediste) + 1, nekiLet._odrediste);
	}
	~Let() {
		delete[] _odrediste; _odrediste = nullptr;
	}
	void postaviKasnjenje(int minuti) {
		_kasnjenje = minuti;
	}
	friend bool operator!(Let&);
	int getTrajanje() {
		return _trajanje;
	}
    friend Let operator+(Let&, int);
	void info() {
		cout << "OZNAKA: " << _oznaka << endl;
		cout << "ODREDISTE: " << _odrediste << endl;
		cout << "IZLAZNA KAPIJA: " <<_brIzlazneKapije << endl;
		cout << "POLIJETANJE U: " <<_vrijemePolijetanja << endl;
		cout << "TRAJANJE: " <<_trajanje << endl;
		cout << "KASNJENJE: " <<_kasnjenje << endl;
	}
	Let& operator+=(int minute) {
		this->_vrijemePolijetanja + minute;
		return *this;
	}
	Vrijeme ocekivanoVrijemePolijetanja() {
		Vrijeme newTime = _vrijemePolijetanja + _kasnjenje;
		return newTime;
	}
	Vrijeme ocekivanoVrijemeSlijetanja() {
		Vrijeme newTime = _vrijemePolijetanja + _kasnjenje + _trajanje;
		return newTime;
	}
	Vrijeme& operator++() {
		return this->_vrijemePolijetanja + 60;
	}
	Vrijeme operator++(int) {
		Vrijeme odlozeno(_vrijemePolijetanja);
		this->_vrijemePolijetanja + 60;
		return odlozeno;
	}
	bool operator<(Let& drugiLet) {
		Let copy = *this;
		return copy._vrijemePolijetanja.prviRanije((drugiLet._vrijemePolijetanja+drugiLet._kasnjenje));
	}
	bool operator>(Let& drugiLet) {
		Let copy = *this;
		return !(copy._vrijemePolijetanja.prviRanije((drugiLet._vrijemePolijetanja + drugiLet._kasnjenje)));
	}
	friend ostream& operator<<(ostream&, Let&);
	Vrijeme getPolijetanje() {
		return _vrijemePolijetanja;
	}
};
bool operator!(Let& nekiLet) {
	return nekiLet._kasnjenje;
}
Let operator+(Let& randomLet, int minute) {
	Let noviLet(randomLet);
	noviLet._vrijemePolijetanja + minute;
	return noviLet;
}
ostream& operator<<(ostream& COUT, Let& nekiLet) {
	if (!(!nekiLet))
		COUT << nekiLet._oznaka << " " << nekiLet._odrediste << "\t" << nekiLet._vrijemePolijetanja << " " << nekiLet.ocekivanoVrijemeSlijetanja() << "\t" << nekiLet._brIzlazneKapije;
	else
		COUT << nekiLet._oznaka << " " << nekiLet._odrediste << "\t" << nekiLet._vrijemePolijetanja << " (Planirano " << nekiLet.ocekivanoVrijemePolijetanja() << ", kasni " << nekiLet._kasnjenje << " min)";
	return COUT;
}


class RasporedLetova
{
	int _brojRegistrovanihLetova;
	const int _maksimalanBrojLetova;
	Let** _letovi;

public:
	RasporedLetova(int maksimalanBrojLetova) : _maksimalanBrojLetova(maksimalanBrojLetova),
		_letovi(new Let*[_maksimalanBrojLetova]), _brojRegistrovanihLetova(0){

	}
	RasporedLetova& operator+=(Let& nekiLet) {
		if (_brojRegistrovanihLetova >= _maksimalanBrojLetova)
			return *this;
		_letovi[_brojRegistrovanihLetova++] = &nekiLet;
		int lokacija = _brojRegistrovanihLetova - 1;
		bool makarJednom = false;
		while (makarJednom) {
			for (int i = 0; i < _brojRegistrovanihLetova; i++) {
				if (_letovi[lokacija]->getPolijetanje().prviRanije(_letovi[i]->getPolijetanje())) {
					swap(_letovi[lokacija], _letovi[i]);
					lokacija = i;
					makarJednom = true;
				}
			}
		}
		return *this;
	}
	void print() {
		for (int i = 0; i < _brojRegistrovanihLetova; i++)
			_letovi[i]->info();
	}

	/*Preklopiti operator "+=" na način da registruje novi let u raspored. Raspored letova u svakom momentu treba biti sortiran
	prema vremenu polijetanja. 
	Voditi računa o maksimalnom broju letova.  
	Za potrebe poređenja vremena polaska letova preklopiti odgovarajuće operatore u klasi Vrijeme.
	*/

	/*Preklopiti operator "-=" na način da ukljanja registrovani let sa oznakom definisanom putem desnog operanda.
	Pri tome sačuvati redoslijed prethodno registrovanih letova. */

	//Preklopiti operator "[]" na način da vraća objekat tipa Let na osnovu proslijeđene pozicije u rasporedu (pozicije kreću od 1).

	/*Preklopiti operator "()" na način da letu sa definisanom oznakom pomjeri vrijeme polijetanja za vrijednost drugog parametra izraženog
	u minutama. */


	//Funkciju koja daje prosječno trajanje svih pohranjenih letova.


	/*Preklopiti operator "<<" koji ispisuje kompletan spisak svih letova, sortiran po očekivanim vremenima polazaka.
	Za potrebe poređenja vremena polaska letova preklopiti odgovarajuće operatore u klasi Vrijeme. */

};

int main()
{
	Vrijeme trenutno(4, 9, 13);
	Vrijeme ranije(2, 9, 13);
	Vrijeme kasnije(16, 9, 13);
	Let noviLet("LB-182", "Stuttgart", 2, trenutno, 120, 0);
	Let noviLet2("LB-183", "Stuttgart", 3, ranije, 120, 0);
	Let noviLet3("LB-184", "Stuttgart", 4, kasnije, 120, 0);
	RasporedLetova danas(5);
	danas += noviLet;
	danas += noviLet2;
	danas += noviLet3;
	danas.print();
	return 0;
}

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
	void setMinute(int minute) {
		_minute += minute;
		while (_minute >= 60) {
			_minute /= 60;
			_sati++;
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
		this->_vrijemePolijetanja.setMinute(minute);
		return *this;
	}


	/*Preklopiti operator + na način da omogućava sabiranje objekata tipa "Let" i cijelog broja, pri
	čemu se kao rezultat dobiva novi objekat tipa "Let", u kojem je vrijeme polijetanja pomjereno
	unaprijed za iznos određen drugim sabirkom (računato u minutama).
	Također preklopiti i operator "+=" koji osigurava da izraz oblika "X += Y uvijek ima isto značenje kao i izraz
	"X = X + Y" */

	/* Funkciju kojom je moguće saznati očekivano vrijeme polijetanja kada se uračuna iznos kašnjenja
	u odnosu na predviđeno vrijeme polijetanja (preklopiti operator + u klasi Vrijeme). */

	//Funkciju koja vraća očekivano vrijeme slijetanja

	/*Preklopiti operator "++" na način da pomijera vrijeme polaska za jedan sat unaprijed.
	Potrebno je podržati i prefiksnu i postfiksnu verziju ovog operatora.*/

	/*Preklopiti relacione operatore "<" i ">" koji ispituju koji let nastupa ranije, odnosno kasnije.
	Operator "<" vraća logičku vrijednost "true" ukoliko polijetanje leta sa lijeve strane nastupa
	prije polijetanje leta sa desne strane, a u suprotnom vraća logičku vrijednost "false".
	Analogno vrijedi za operator ">". Prilikom upoređivanja treba uzeti u obzir i očekivano vrijeme kašnjenja,
	a ne samo planirano vrijeme polijetanja.*/

	/*Preklopiti operator "<<" koji treba da podrži ispis objekata tipa "Let" na ekran. U slučaju da
	se radi o polijetanju bez kašnjenja, ispis bi trebao da izgleda kako slijedi:

	JFK 156 Atalanta    12:50   19:30   5

	Podaci predstavljaju redom: oznaku leta, naziv odredišta, vrijeme polijetanja, očekivano
	vrijeme slijetanja i broj izlazne kapije.

	U slučaju da se radi o letu koji kasni, ispis bi trebao izgledati kako slijedi:

	ZGK 932 Zagreb    15:50 (Planirano 15:30, Kasni 20 min)*/
};

bool operator!(Let& nekiLet) {
	return nekiLet._kasnjenje;
}
Let operator+(Let& randomLet, int minute) {
	Let noviLet(randomLet);
	noviLet._vrijemePolijetanja.setMinute(minute);
	return noviLet;
}


class RasporedLetova
{
	int _brojRegistrovanihLetova;
	const int _maksimalanBrojLetova;
	Let** _letovi;

public:
	RasporedLetova(int maksimalanBrojLetova) : _maksimalanBrojLetova(maksimalanBrojLetova),
		_letovi(new Let*[_maksimalanBrojLetova]), _brojRegistrovanihLetova(0)
	{

	}

	/*Preklopiti operator "+=" na način da registruje novi let u raspored. Raspored letova u svakom momentu treba biti sortiran
	prema vremenu polijetanja. Voditi računa o maksimalnom broju letova.  Za potrebe poređenja vremena polaska letova preklopiti odgovarajuće operatore u klasi Vrijeme.*/

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
	Vrijeme trenutno(1, 9, 13);
	cout << trenutno;
	Let noviLet("LB-182", "Stuttgart", 2, trenutno, 120, 0);
	noviLet.info();
	if (!noviLet)
		cout << "Let kasni!" << endl;
	Let prolongiraniLet = noviLet + 150;
	prolongiraniLet.info();
	prolongiraniLet += 10;
	prolongiraniLet.info();
	return 0;
}

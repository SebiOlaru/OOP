#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Activitate {
	std::string titlu;
	std::string descriere;
	std::string tip;
	int durata;
public:
	Activitate(const string titlu1, const string descriere1, const string tip1, int durata1) :titlu{ titlu1 }, descriere{ descriere1 }, tip{ tip1 }, durata{ durata1 } {}

	Activitate(const Activitate& activitate) :titlu{ activitate.titlu }, descriere{ activitate.descriere }, tip{ activitate.tip }, durata{ activitate.durata } {
		cout << "!!!!!\n";
	}


	string getTitlu() const {
		return titlu;
	}
	string getDescriere() const {
		return descriere;
	}
	string getTip() const {
		return tip;
	}

	int getDurata() const noexcept {
		return durata;
	}
};
/*
Compara dupa titlu
returneaza true daca activitate1.titlu e mai mic decat activitate2.titlu
*/
bool comparareTitlu(const Activitate& activitate1, const Activitate& activitate2);

/*
Compara dupa descriere
returneaza true daca activitate1.descriere e mai mic decat activitate2.descriere
*/
bool comparareDescriere(const Activitate& activitate1, const Activitate& activitate2);

/*
	Compara dupa durata
	*/
bool compara_dupa_durata(const Activitate& activitate1, const Activitate& activitate2);


/*
Compara dupa durata si tip
*/
bool compara_durata_tip(const Activitate& activitate1, const Activitate& activitate2);



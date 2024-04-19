#pragma once
#include "activitate.h"

#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class ActivitateRepo {
protected:
	vector<Activitate> toate_activitatile;

public:
	ActivitateRepo() = default;
	//nu permitem copierea de obiecte
	ActivitateRepo(const ActivitateRepo& activitate) = delete;
	/*
	Salvare activitate
	arunca exceptie daca mai exista o activitate cu acelasi titlu si descriere
	*/
	void planificare_activitati(const Activitate& activitate);

	/*
	Cauta
	arunca exceptie daca nu exista activitatea
	*/
	int cauta_activitate(const string& titlu);

	/*
	returneaza toate activitatile salvate
	*/
	const vector<Activitate>& getAll() const noexcept;

	//sterge activitate dupa denumire
	void sterge_activitate(const string& titlu);

};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class ActivitateRepoException {
	string message;
public:
	ActivitateRepoException(string message) :message{ message } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ActivitateRepoException& exception);
};

ostream& operator<<(ostream& out, const ActivitateRepoException& exception);

void testeRepo();
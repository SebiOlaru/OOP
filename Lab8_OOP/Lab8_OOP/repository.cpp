#include "repository.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void ActivitateRepo::planificare_activitati(const Activitate& activitate)
{
	const string& titlu = activitate.getTitlu();
	if (cauta_activitate(titlu) != -1) {
		throw ActivitateRepoException("Exista deja activitatea cu titlul:" + activitate.getTitlu());
	}
	else toate_activitatile.push_back(activitate);
}


/*
returneaza toate activitatile salvate
*/
const vector<Activitate>& ActivitateRepo::getAll() const noexcept {
	return toate_activitatile;
}


ostream& operator<<(ostream& out, const ActivitateRepoException& exception) {
	out << exception.message;
	return out;
}

int ActivitateRepo::cauta_activitate(const string& titlu)
{
	vector<Activitate> v = toate_activitatile;
	for (int i = 0; i < (int)toate_activitatile.size(); i++)
		if (v[i].getTitlu() == titlu)
			return i;
	return -1;
}

void ActivitateRepo::sterge_activitate(const string& titlu) {
	const int index = cauta_activitate(titlu);
	if (index != -1) {
		auto first = this->toate_activitatile.begin();
		this->toate_activitatile.erase(first + index);
	}
	else { throw ActivitateRepoException("Oferta nu exista\n"); }
}

//Teste

void testAdauga() {
	ActivitateRepo repo;
	repo.planificare_activitati(Activitate{ "a","a","a",4 });
	assert(repo.getAll().size() == 1);
	assert(repo.cauta_activitate("a") != -1);

	repo.planificare_activitati(Activitate{ "b","b","b",4 });
	assert(repo.getAll().size() == 2);

	//nu pot adauga 2 cu aceeasi descriere si titlu
	try {
		repo.planificare_activitati(Activitate{ "a","a","a",4 });
		assert(false);
	}
	catch (const ActivitateRepoException&) {
		assert(true);
	}
	//cauta inexistent
	try {
		int index = repo.cauta_activitate("c");
		assert(index == -1); // Verifică dacă activitatea nu a fost găsită
	}
	catch (const ActivitateRepoException& exception) {
		// Dacă activitatea ar fi fost găsită, nu ar trebui să arunce o excepție
		assert(false);
	}
}

void testStergeActivitate() {
	ActivitateRepo repository;
	repository.planificare_activitati(Activitate{ "aa", "descriere_aa", "tip_aa", 4 });
	repository.planificare_activitati(Activitate{ "bb", "descriere_bb", "tip_bb", 5 });
	repository.planificare_activitati(Activitate{ "cc", "descriere_cc", "tip_cc", 6 });

	// Testăm ștergerea unei activități existente
	repository.sterge_activitate("aa");
	assert(repository.getAll().size() == 2);

	// Testăm aruncarea excepției pentru ștergerea unei activități inexistente
	try {
		repository.sterge_activitate("dd");
		assert(false); // Dacă nu aruncă excepția, testul eșuează
	}
	catch (ActivitateRepoException&) {
		assert(true);
	}
}
void testCauta() {
	ActivitateRepo repository;
	repository.planificare_activitati(Activitate{ "aa", "descriere_aa", "tip_aa", 4 });
	repository.planificare_activitati(Activitate{ "bb", "descriere_bb", "tip_bb", 5 });
	repository.planificare_activitati(Activitate{ "cc", "descriere_cc", "tip_cc", 6 });

	// Testăm căutarea unei activități existente
	auto activitateGasita = repository.cauta_activitate("aa");
	assert(activitateGasita!=-1);

	//arunca exceptie daca nu gaseste
	try {
		int index = repository.cauta_activitate("c");
		assert(index == -1); // Verifică dacă activitatea nu a fost găsită
	}
	catch (const ActivitateRepoException& exception) {
		// Dacă activitatea ar fi fost găsită, nu ar trebui să arunce o excepție
		assert(false);
	}
}
void testActivitateRepoException() {
	ActivitateRepoException exception("Test exception message");
	std::ostringstream oss;
	oss << exception;

	assert(oss.str() == "Test exception message");
}

void testOperatorInserare() {
	// Testăm afișarea unui mesaj de excepție corect într-un stream de ieșire
	stringstream ss;
	ActivitateRepoException ex("Mesaj de eroare");
	ss << ex;
	assert(ss.str() == "Mesaj de eroare");
}


void testeRepo() {
	testAdauga();
	testCauta();
	testStergeActivitate();
	testOperatorInserare();
	testActivitateRepoException();
}
#include "repository.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void ActivitateRepo::planificare_activitati(const Activitate& activitate)
{
	if (exist(activitate)) {
		throw ActivitateRepoException("Exista deja o activitate titlu:" + activitate.getTitlu() + " descriere:" + activitate.getDescriere());
	}
	toate_activitatile.push_back(activitate);
}

bool ActivitateRepo::exist(const Activitate& activitate) const {
	try {
		gaseste_activitate(activitate.getTitlu(), activitate.getDescriere());
		return true;
	}
	catch (ActivitateRepoException&) {
		return false;
	}
}
/*
Cauta
arunca exceptie daca nu exista activitatea
*/
const Activitate& ActivitateRepo::gaseste_activitate(string titlu, string descriere) const {
	for (const auto& activitate : toate_activitatile) {
		if (activitate.getTitlu() == titlu && activitate.getDescriere() == descriere) {
			return activitate;
		}
	}
	//daca nu exista arunc o exceptie
	throw ActivitateRepoException("Nu exista oferta de tip titlu:" + titlu + " descriere:" + descriere);
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


//Teste

void testAdauga () {
	ActivitateRepo repo;
	repo.planificare_activitati(Activitate{ "a","a","a",4 });
	assert(repo.getAll().size() == 1);
	assert(repo.gaseste_activitate("a", "a").getTitlu() == "a");

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
		repo.gaseste_activitate("c", "c");
		assert(false);
	}
	catch (const ActivitateRepoException& exception) {
		stringstream message;
		message << exception;
		assert(message.str().find("exista") >= 0);
	}
}

void testCauta() {
	ActivitateRepo repository;
	repository.planificare_activitati(Activitate{ "aa","aa","aa",4 });
	repository.planificare_activitati(Activitate{ "bb","bb","bb",4});

	auto activitate = repository.gaseste_activitate("aa", "aa");
	assert(activitate.getTitlu() == "aa");
	assert(activitate.getDescriere() == "aa");

	//arunca exceptie daca nu gaseste
	try {
		repository.gaseste_activitate("aa", "bb");
		assert(false);
	}
	catch (ActivitateRepoException&) {
		assert(true);
	}
}

void testeRepo() {
	testAdauga();
	testCauta();
}
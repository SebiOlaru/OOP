#include "planificare_activitate.h"
#include <functional>
#include <algorithm>
#include <assert.h>

vector<Activitate> PlanificareActivitate::generalSort(bool(*relatie_mai_mic)(const Activitate&, const Activitate&)) {
	vector<Activitate> vector{ repository.getAll() };//fac o copie	
	for (size_t i = 0; i < vector.size(); i++) {
		for (size_t j = i + 1; j < vector.size(); j++) {
			if (!relatie_mai_mic(vector[i], vector[j])) {
				//interschimbam
				Activitate auxiliar = vector[i];
				vector[i] = vector[j];
				vector[j] = auxiliar;
			}
		}
	}
	return vector;
}

/*
Adauga o noua activitate
arunca exceptie daca: nu se poate salva, nu este valid
*/
void PlanificareActivitate::addActivitate(const string& titlu, const string& descriere, const string& tip, int durata) {
	Activitate activitate{ titlu,descriere,tip,durata };
	repository.planificare_activitati(activitate);
}

/*
Sorteaza dupa titlu
*/
vector<Activitate> PlanificareActivitate::sortByTitlu() {
	auto copyAll = repository.getAll();
	std::sort(copyAll.begin(), copyAll.end(), comparareTitlu);
	return copyAll;
}

/*
Sorteaza dupa descriere
*/
vector<Activitate> PlanificareActivitate::sortByDescriere() {
	return generalSort(comparareDescriere);
}


/*
Sorteaza dupa tip+durata
*/
vector<Activitate> PlanificareActivitate::sortByTipDurata() {
	return generalSort([](const Activitate& activitate1, const Activitate& activitate2) {
		if (activitate1.getTip() == activitate2.getTip()) {
			return activitate1.getDurata() < activitate2.getDurata();
		}
	return activitate1.getTip() < activitate2.getTip();
		});
}


/*
Cauta activitate dupa titlu
*/
vector<Activitate> PlanificareActivitate::cautaDupaTitlu(const string& titlu) {
	vector<Activitate> rezultat;
	for (const auto& activitate : repository.getAll()) {
		if (activitate.getTitlu() == titlu) {
			rezultat.push_back(activitate);
		}
	}
	if (rezultat.empty()) {
		std::cout << "Nu s-a gasit nicio activitate cu titlul '" << titlu << std::endl;
	}
	else {
		std::cout << "Activitatile cu titlul '" << titlu << "' sunt:" << std::endl;
		for (const auto& activitate : rezultat) {
			std::cout << activitate.getDescriere() << " " << activitate.getTip() << " " << activitate.getDurata() << std::endl;
		}
	}
	return rezultat;
}

vector<Activitate> PlanificareActivitate::filtrare_descriere(const string& descriere)
{
	vector<Activitate> rezultat;
	vector<Activitate> lista = repository.getAll();
	std::copy_if(lista.begin(), lista.end(), back_inserter(rezultat),
		[descriere](Activitate& oferta) {
			return oferta.getDescriere() == descriere;
		});
	return rezultat;
}

vector<Activitate> PlanificareActivitate::filtrareTip(const string& tip)
{
	vector<Activitate> rezultat;
	vector<Activitate> lista = repository.getAll();
	std::copy_if(lista.begin(), lista.end(), back_inserter(rezultat),
		[tip](Activitate& activitate) {
			return activitate.getTip() == tip;
		});
	return rezultat;
}

void testAdaugaService() {
	ActivitateRepo repository;
	PlanificareActivitateValidator validare;
	PlanificareActivitate service{ repository,validare };
	service.addActivitate("a", "a","a", 6);
	assert(service.getAll().size() == 1);

	
}


void testSortare() {
	ActivitateRepo repository;
	PlanificareActivitateValidator validare;
	PlanificareActivitate planificare{ repository,validare };
	planificare.addActivitate("z", "z","a", 6);
	planificare.addActivitate("b", "a","z", 60);
	planificare.addActivitate("c", "a","x", 600);

	auto first = planificare.sortByTitlu()[0];
	assert(first.getTitlu() == "b");

	first = planificare.sortByDescriere()[0];
	assert(first.getDescriere() == "a");

	first = planificare.sortByTipDurata()[0];
	assert(first.getDurata() == 6);

}

void testCautaDupaTitlu() {
	ActivitateRepo repository;
	PlanificareActivitateValidator validare;
	PlanificareActivitate planificare{ repository,validare };
	planificare.addActivitate("a", "descriere1", "tip1", 10);
	planificare.addActivitate("b", "descriere2", "tip2", 20);
	planificare.addActivitate("c", "descriere3", "tip3", 30);

	// Cautăm activitatele cu titlul "a"
	auto rezultat = planificare.cautaDupaTitlu("a");
	assert(rezultat.size() == 1);
	assert(rezultat[0].getTitlu() == "a");

	// Cautăm activitatele cu titlul "d" (care nu există)
	rezultat = planificare.cautaDupaTitlu("d");
	assert(rezultat.empty());
}

void testFiltrare() {
	ActivitateRepo repo;
	PlanificareActivitateValidator validare;
	PlanificareActivitate srv{ repo ,validare };
	srv.addActivitate("aa", "descriere", "tip", 450);
	srv.addActivitate("bb", "descriere2", "tip2", 1450);
	srv.addActivitate("cc", "descriere2", "tip", 150);
	assert(srv.filtrare_descriere("descriere").size() == 1);
	assert(srv.filtrare_descriere("descriere2").size() == 2);
	assert(srv.filtrareTip("tip").size() == 2);
	assert(srv.filtrareTip("tip9").size() == 0);
}

void testePlanificare() {
	testAdaugaService();
	testSortare();
	testCautaDupaTitlu();
	testFiltrare();
}

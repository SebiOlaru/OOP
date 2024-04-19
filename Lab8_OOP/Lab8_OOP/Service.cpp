#include "Service.h"
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <string.h>
#include <map>
#include <string>
using namespace std;

///PENTRU PROGRAM

void Service::filtreazaCount(std::map<std::string, std::vector<Activitate>>& dictionar) const noexcept
{
	for (Activitate activitate : program_lista.program)
	{
		std::string tip = activitate.getTip();
		auto it = dictionar.find(tip);
		if (it == dictionar.end())
		{
			std::vector<Activitate> oferte;
			oferte.push_back(activitate);
			dictionar.insert({ tip, oferte });
		}
		else
			dictionar[tip].push_back(activitate);
	}
}


void Service::adaugaProgram(string titlu) {
	vector<Activitate> vector{ repo.getAll() };
	int ok = 0;
	for (int i = 0; i < vector.size(); i++)
	{
		Activitate aux = vector[i];
		if (aux.getTitlu() == titlu)
		{
			ok = 1;
			program_lista.adauga_program(aux);
		}
	}
	if (ok == 0) throw exception();
}

size_t Service::adaugaRandom(int numar) {
	program_lista.adauga_random(repo.getAll(), numar);
	return program_lista.get_all_program().size();
}

void Service::golesteProgram() {
	program_lista.goleste_program();
}
const vector<Activitate>& Service::getAllProgram() {
	if (program_lista.get_all_program().size() == 0) throw exception();
	return program_lista.get_all_program();
}

void Service::salveazaProgram(string fisier) {
	ofstream fout(fisier);
	vector<Activitate>lista = program_lista.program;
	for (auto& element : lista) {
		fout << element.getTitlu() << " | " << element.getDescriere() << " | " << element.getDurata() << " | " << element.getTip() << '\n';
	}
	fout.close();

}


///PENTRU ADAUGARE SIMPLA
/*
Adauga o noua Activitate
arunca exceptie daca: nu se poate salva, nu este valid
*/
void Service::adaugaActivitate(const string& titlu, const string& descriere, const string& tip, int durata)
{
	Activitate activitate{ titlu, descriere,tip, durata};
	validator.validate(activitate);
	repo.planificare_activitati(activitate);
}

void Service::stergeActivitate(const string& titlu)
{
	repo.sterge_activitate(titlu);
}


vector<Activitate> Service::sortare_dupa_titlu()
{
	//return generalSort(cmpNrInm);
	vector<Activitate> lista = repo.getAll();
	sort(lista.begin(), lista.end(), comparareTitlu);
	return lista;
}

vector<Activitate> Service::sortare_dupa_descriere()
{
	//return generalSort(cmpTip);
	vector<Activitate> lista = repo.getAll();
	sort(lista.begin(), lista.end(), comparareDescriere);
	return lista;
}

/*
Sorteaza dupa durata si tip
*/
vector<Activitate> Service::sortare_dupa_durata_tip()
{
	vector<Activitate> lista = repo.getAll();
	sort(lista.begin(), lista.end(), compara_durata_tip);
	return lista;
 
}

vector<Activitate> Service::filtrare_descriere(const string& descriere)
{
	vector<Activitate> rezultat;
	vector<Activitate> lista = repo.getAll();
	std::copy_if(lista.begin(), lista.end(), back_inserter(rezultat),
		[descriere](Activitate& oferta) {
			return oferta.getDescriere() == descriere;
		});
	return rezultat;
}

vector<Activitate> Service::filtrareTip(const string& tip)
{
	vector<Activitate> rezultat;
	vector<Activitate> lista = repo.getAll();
	std::copy_if(lista.begin(), lista.end(), back_inserter(rezultat),
		[tip](Activitate& activitate) {
			return activitate.getTip() == tip;
		});
	return rezultat;
}



void testAdaugaSrv() {
	ActivitateRepo repo;
	PlanificareActivitateValidator validare;
	Service srv{ repo,validare };
	srv.adaugaActivitate("turistica", "Cluj", "familie", 1000);
	assert(srv.getAll().size() == 1);

	//adaug ceva invalid
	try {
		srv.adaugaActivitate("", "Cluj", "familie", 100); assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
}

void testStergeSrv() {
	ActivitateRepo repo;
	PlanificareActivitateValidator validare;
	Service srv{ repo ,validare };
	srv.adaugaActivitate("turistica", "Cluj", "familie", 100);
	assert(srv.getAll().size() == 1);
	srv.adaugaActivitate("noua", "Bucuresti", "familie", 1500);
	assert(srv.getAll().size() == 2);
	srv.stergeActivitate("noua");
	assert(srv.getAll().size() == 1);

}

void testFiltrare() {
	ActivitateRepo repo;
	PlanificareActivitateValidator validare;
	Service srv{ repo ,validare };
	srv.adaugaActivitate("aa", "descriere", "tip", 450);
	srv.adaugaActivitate("bb", "descriere2", "tip2", 1450);
	srv.adaugaActivitate("cc", "descriere2", "tip", 150);
	assert(srv.filtrare_descriere("descriere").size() == 1);
	assert(srv.filtrare_descriere("descriere2").size() == 2);
	assert(srv.filtrareTip("tip").size() == 2);
	assert(srv.filtrareTip("tip9").size() == 0);
}

void testSortare()
{
	ActivitateRepo repo;
	PlanificareActivitateValidator validare;
	Service srv{ repo ,validare };
	srv.adaugaActivitate("aa", "adescriere", "tip", 450);
	srv.adaugaActivitate("bb", "descriere2", "tip2", 1450);
	srv.adaugaActivitate("cc", "descriere2", "tip", 150);

	auto firstO = srv.sortare_dupa_titlu()[0];
	assert(firstO.getTitlu() == "aa");

	firstO = srv.sortare_dupa_descriere()[0];
	assert(firstO.getDescriere() == "adescriere");

	firstO = srv.sortare_dupa_durata_tip()[0];
	assert(firstO.getDurata() == 150);
}

void testProgram() {
	ActivitateRepo rep;
	PlanificareActivitateValidator val;
	Service srv{ rep,val };

	srv.adaugaActivitate("aa", "descriere", "tip", 450);
	srv.adaugaActivitate("bb", "descriere2", "tip2", 1450);
	srv.adaugaActivitate("cc", "descriere2", "tip", 150);

	srv.adaugaProgram("aa");
	try
	{
		srv.adaugaProgram("nu_exista");
	}
	catch (exception&) { assert(true); }

	srv.adaugaRandom(2);
	assert(srv.getAllProgram().size() == 3);
	srv.golesteProgram();
}

void testSalveaza() {
	ActivitateRepo repo;
	PlanificareActivitateValidator validare;
	Service srv{ repo ,validare };

	srv.adaugaActivitate("aa", "descriere", "tip", 450);
	srv.adaugaActivitate("bb", "descriere2", "tip2", 1450);
	srv.adaugaActivitate("cc", "descriere2", "tip", 150);

	srv.adaugaProgram("aa");
	srv.adaugaProgram("bb");

	srv.salveazaProgram("test.html");

	ifstream fin("test.html");
	const Activitate oferta1("aa", "descriere", "tip", 450);
	const Activitate oferta2("bb", "descriere2", "tip2", 1450);
	fin.close();

}

void testFiltreazaCount() {
	ActivitateRepo repo;
	PlanificareActivitateValidator validare;
	Service srv{ repo ,validare };

	srv.adaugaActivitate("turistica", "Cluj", "familie", 1000);
	srv.adaugaActivitate("culturala", "Bucuresti", "cultural", 1500);
	srv.adaugaActivitate("sportiva", "Brasov", "sport", 1200);

	srv.adaugaProgram("turistica");
	srv.adaugaProgram("culturala");
	srv.adaugaProgram("sportiva");

	std::map<std::string, std::vector<Activitate>> dictionar;
	srv.filtreazaCount(dictionar);

	assert(dictionar.size() == 3); // Trebuie să fie 3 categorii distincte
	assert(dictionar["familie"].size() == 1);
	assert(dictionar["cultural"].size() == 1);
	assert(dictionar["sport"].size() == 1);
}


void testeSrv() {
	testAdaugaSrv();
	testFiltrare();
	testSortare();
	testStergeSrv();
	testProgram();
	testSalveaza();
	testFiltreazaCount();
}
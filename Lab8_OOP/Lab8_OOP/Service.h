#pragma once

#include "activitate.h"
#include "repository.h"
#include <string>
#include <vector>
#include "Program.h"
#include <functional>
#include "validator.h"
using std::vector;
using std::function;
using std::string;

class Service {
private:
	ActivitateRepo& repo;
	PlanificareActivitateValidator& validator;
    Program program_lista;

    /*
     Functie de sortare generala
     relatie_mai_mic - functie care compara 2 oferte, verifica daca are loc relatia mai mic
     returneaza o lista sortata dupa criteriu dat ca paramatru
    */
    vector<Activitate> generalSort(bool (*relatie_mai_mic)(const Activitate&, const Activitate&));
    /*
    Functie generala de filtrare
    returneaza doar ofertele care trec de filtru (fct(oferta)==true)
    */
    vector<Activitate> filtreaza(function<bool(const Activitate&)> functie);

public:
	Service(ActivitateRepo& repo, PlanificareActivitateValidator& validator) noexcept : repo{ repo }, validator{ validator } {}
	//nu permitem copierea de obiecte
	Service(const Service& altele) = delete;

	//////////PENTRU PROGRAM
	//Adauga o oferta cu denumirea denumire in program
	void adaugaProgram(string denumire);

	//Adauga un numar random de oferte in program
	size_t adaugaRandom(int numar);

	//Elimina toate activitatile din program
	void golesteProgram();

	//Returneaza un vector cu toate activitatile din program
	const vector<Activitate>& getAllProgram();

	void salveazaProgram(string fisier);

	void filtreazaCount(std::map<std::string, std::vector<Activitate>>& dictionar) const noexcept;

	//////////PENTRU OPERATIILE ORIGINALE
	/*
	 returneaza toate activitatile in ordinea in care au fost adaugate
	*/
	const vector<Activitate>& getAll() noexcept { return repo.getAll(); }

	/*
	Adauga o noua activitate
	arunca exceptie daca: nu se poate salva, nu este valid
	*/
	void adaugaActivitate(const string& titlu, const string& descriere, const string& tip, int durata);

	void stergeActivitate(const string& titlu);

	vector<Activitate> sortare_dupa_titlu();

	vector<Activitate> sortare_dupa_descriere();

	vector<Activitate> sortare_dupa_durata_tip();

	vector<Activitate> filtrare_descriere(const string& descriere);

	vector<Activitate> filtrareTip(const string& tip);
};

void testeSrv();

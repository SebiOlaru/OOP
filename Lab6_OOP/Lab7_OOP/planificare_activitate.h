#pragma once

#include "activitate.h"
#include "repository.h"
#include <string>
#include <vector>

#include <functional>
#include "validator.h"

using std::vector;
using std::function;

class PlanificareActivitate {
	ActivitateRepo& repository;
	PlanificareActivitateValidator& validare;

	/*
	 Functie de sortare generala
	 maiMareF - functie care compara doua activitati, verifica daca are loc relatia mai mare
			  - poate fi orice functie (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii PlanificareActivitate)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
	 returneaza o lista sortata dupa criteriu dat ca paramatru
	*/
	vector<Activitate> generalSort(bool (*relatie_mai_mic)(const Activitate&, const Activitate&));
	/*
	Functie generala de filtrare
	fct - poate fi o functie
	fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar ofertele care trec de filtru (fct(oferta)==true)
	*/
	vector<Activitate> filtreaza(function<bool(const Activitate&)> functie);
public:
	PlanificareActivitate(ActivitateRepo& repo, PlanificareActivitateValidator& validare)noexcept :repository{ repo }, validare{ validare } {
	}
	//nu permitem copierea de obiecte PlanificareActivitate
	PlanificareActivitate(const PlanificareActivitate& planificare) = delete;
	/*
	 returneaza toate activitatile in ordinea in care au fost adaugate
	*/
	const vector<Activitate>& getAll() noexcept {
		return repository.getAll();
	}
	/*
	Adauga o noua activitate
	arunca exceptie daca: nu se poate salva, nu este valid
	*/
	void addActivitate(const string& titlu, const string& descriere, const string& tip, int durata);

	/*
	Sorteaza dupa titlu
	*/
	vector<Activitate> sortByTitlu();

	/*
	Sorteaza dupa descriere
	*/
	vector<Activitate> sortByDescriere();


	/*
	Sorteaza dupa tip+durata
	*/
	vector<Activitate> sortByTipDurata();

	/*
	Cauta activitate dupa titlu
	*/
	vector<Activitate> cautaDupaTitlu(const string& titlu);
		
	vector<Activitate> filtrare_descriere(const string& descriere);

	vector<Activitate> filtrareTip(const string& tip);
	
};
void testePlanificare();
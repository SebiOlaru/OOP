#pragma once
#include "activitate.h"
#include "planificare_activitate.h"

class ConsoleUI{
	PlanificareActivitate& planificare;
	/*
	Citeste datele de la tastatura si adauga o activitate
	arunca exceptie daca: nu se poate salva, nu e valid
	*/
	void adaugaUI();

	void cautaUI();
	/*
	Tipareste o lista de activitati la consola
	*/
	void tipareste(const vector<Activitate>& oferte);
public:
	 ConsoleUI(PlanificareActivitate& planificare) :planificare{ planificare } {
	}
	//nu permitem copierea obiectelor
	ConsoleUI(const ConsoleUI& oferta_turistica) = delete;

	void start();
};
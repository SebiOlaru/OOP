#pragma once
#pragma once
#include "activitate.h"
#include <vector>
#include <algorithm>
#include <random> 
#include <chrono>
#include <map>
#include <string>
using std::map;
using std::vector;
class Program {
	friend class Service;
private:
	vector<Activitate> program;
	//map<int, int> frecventa;
public:
	Program() = default;

	//Adauga o activitate in program
	void adauga_program(const Activitate& a);

	//Elimina toate activitatile din program
	void goleste_program() noexcept;

	//Adauga un numar random de activitati in program
	void adauga_random(vector<Activitate> oferte, int n);

	//un vector cu toate activitati din program
	const vector<Activitate>& get_all_program() noexcept;

	void valideaza_program(Activitate& oferta);
};
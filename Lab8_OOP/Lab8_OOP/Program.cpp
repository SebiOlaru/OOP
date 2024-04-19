#include "Program.h"
#include <exception>
#include <iostream>
#include <map>
#include <string>

using namespace std;
using std::shuffle;


void Program::adauga_program(const Activitate& activitate) {
	program.push_back(activitate);
}
void Program::goleste_program() noexcept {
	program.clear();
}

void Program::adauga_random(vector<Activitate> activitati, int n)
{
	shuffle(activitati.begin(), activitati.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul masini
	const size_t init_size = program.size();
	while (program.size() < n + init_size && activitati.size() > 0) {
		program.push_back(activitati.back());
		activitati.pop_back();
	}
}
const vector<Activitate>& Program::get_all_program() noexcept {
	return program;
}
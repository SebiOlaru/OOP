#include "console.h"
#include "activitate.h"
#include "repository.h"
#include "validator.h"


void testAll() {
	testeRepo();
	testePlanificare();
	testValidator();
}

int main() {
	testAll();

	ActivitateRepo repository;
	PlanificareActivitateValidator validare;
	PlanificareActivitate planificare{ repository,validare };
	
	ConsoleUI ui{ planificare };
	ui.start();
}
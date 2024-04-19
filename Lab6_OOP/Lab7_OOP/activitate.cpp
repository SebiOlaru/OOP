#include "activitate.h"


bool comparareTitlu(const Activitate& activitate1, const Activitate& activitate2) {
	return activitate1.getTitlu() < activitate2.getTitlu();
}

bool comparareDescriere(const Activitate& activitate1, const Activitate& activitate2) {
	return activitate1.getDescriere() < activitate2.getDescriere();
}

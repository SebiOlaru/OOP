#include "activitate.h"


bool comparareTitlu(const Activitate& activitate1, const Activitate& activitate2) {
	return activitate1.getTitlu() < activitate2.getTitlu();
}

bool comparareDescriere(const Activitate& activitate1, const Activitate& activitate2) {
	return activitate1.getDescriere() < activitate2.getDescriere();
}

bool compara_durata_tip(const Activitate& activitate1, const Activitate& activitate2)
{
	if (activitate1.getDurata() == activitate2.getDurata()) return activitate1.getTip() < activitate2.getTip();
	else return activitate1.getDurata() < activitate2.getDurata();
}
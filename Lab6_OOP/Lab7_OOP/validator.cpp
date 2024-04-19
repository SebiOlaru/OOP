#include "validator.h"
#include <assert.h>
#include <sstream>

void PlanificareActivitateValidator::validate(const Activitate& activitate) {
	vector<string> messages;
	if (activitate.getDurata() < 0) messages.push_back("Durata negativa!!!");
	if (activitate.getTitlu().size() == 0) messages.push_back("Titlu vid!!!");
	if (activitate.getDescriere().size() == 0) messages.push_back("Descriere vida!!!");
	if (activitate.getTip().size() == 0) messages.push_back("Tip vid!!!");
	if (messages.size() > 0) {
		throw ValidateException(messages);
	}
}

ostream& operator<<(ostream& out, const ValidateException& exceptie) {
	for (const auto& message : exceptie.messages) {
		out << message << " ";
	}
	return out;
}

void testValidator() {
	PlanificareActivitateValidator validator;
	Activitate activitate{ "","","", - 1};
	try {
		validator.validate(activitate);
	}
	catch (const ValidateException& exceptie) {
		std::stringstream sout;
		sout << exceptie;
		auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}

}
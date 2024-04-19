#pragma once
#include <string>
#include "activitate.h"
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	vector<string> messages;
public:
	ValidateException(const vector<string>& errors) :messages{ errors } {}
	//functie friend (vreau sa folosesc membru privat messages)
	friend ostream& operator<<(ostream& out, const ValidateException& exception);
};

ostream& operator<<(ostream& out, const ValidateException& exception);

class PlanificareActivitateValidator {
public:
	void validate(const Activitate& oferta);
};

void testValidator();
#include <iostream>
#include "UI.h"
#include "activitate.h"
#include "repository.h"
#include "Service.h"
#include "Validator.h"

using std::cout;

void testAll() {
    testValidator();
    testeSrv();
    testeRepo();
}

void run()
{
    ActivitateRepo repo;
    PlanificareActivitateValidator validare;
    Service srv{ repo ,validare };
    UI ui{ srv };
    ui.start();
}

int main() {
    testAll();
    run();
    return 0;
}
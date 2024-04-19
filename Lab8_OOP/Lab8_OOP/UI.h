#pragma once

#include "Service.h"
#include "activitate.h"

class UI {
private:
    Service& service;
    /*
    Citeste datele de la tastatura si adauga Activitate
    arunca exceptie daca: nu se poate salva, nu e valid
    */
    void ui_adaugaActivitate();
    void ui_stergeActivitate();
    void tipareste(const vector<Activitate>& activitati);

    void ui_adaugaProgram();
    void ui_printProgram();
    void ui_adaugaRandom();
    void ui_golesteProgram();
    void ui_salveazaProgram();
    void ui_filtreazaCount() const;
public:
    
    UI(Service& service) noexcept : service{ service } {};
    //nu permitem copierea obiectelor
    UI(const UI& altele) = delete;

    void start();
};

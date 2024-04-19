#include "console.h"

#include "activitate.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;

void ConsoleUI::tipareste(const vector<Activitate>& activitati) {
	cout << "Activitati:\n";
	for (const auto& activitate : activitati) {
		cout << ' ' << activitate.getTitlu() << ' ' << activitate.getDescriere() <<' ' << activitate.getTip() <<' ' << activitate.getDurata() << '\n';
	}
	cout << "Sfarsit lista activitati\n";
}

void ConsoleUI::adaugaUI() {
	string titlu, descriere, tip;
	int pret;
	cout << "Dati titlul activitatii:";
	cin >> titlu;
	cout << "Dati descrierea activitatii:";
	cin >> descriere;
	cout << "Dati tipul activitatii:";
	cin >> tip;
	cout << "Dati pretul activitatii:";
	cin >> pret;
	planificare.addActivitate(titlu, descriere,tip, pret);
	cout << "Adaugat cu succes\n";
}

void ConsoleUI::cautaUI() {
	string titlu;
	cout << "Dati titlul activitatii:";
	cin >> titlu;
	planificare.cautaDupaTitlu(titlu);
}

void ConsoleUI::start() {
	while (true) {
		cout << "Meniu:\n";
		cout << "1 adauga activitate\n2 tipareste activitati\n3 sorteaza dupa titlu\n4 sorteaza dupa descriere\n5 sorteaza dupa tip+durata\n6 Cautare\n7.Filtrare dupa descriere\n8 Filtrare dupa tip\n0 Iesire\nDati comanda:";
		int cmd;
		string descriere, tip;
		cin >> cmd;
		try {
			switch (cmd) {
			case 1:
				adaugaUI();
				break;
			case 2:
				tipareste(planificare.getAll());
				break;
			case 3:
				tipareste(planificare.sortByTitlu());
				break;
			case 4:
				tipareste(planificare.sortByDescriere());
				break;
			case 5:
				tipareste(planificare.sortByTipDurata());
				break;
			case 6:
				cautaUI();
				break;
			case 7:
				cout << "Descrierea dupa care doriti sa filtrati:";
				cin >> descriere;
				tipareste(planificare.filtrare_descriere(descriere));
				break;
			case 8:
				cout << "Tipul dupa care doriti sa filtrati:";
				cin >> tip;
				tipareste(planificare.filtrareTip(tip));
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida\n";
			}
		}
		catch (const ActivitateRepoException& ex) {
			cout << ex << '\n';
		}
		catch (const ValidateException& ex) {
			cout << ex << '\n';
		}
	}
}

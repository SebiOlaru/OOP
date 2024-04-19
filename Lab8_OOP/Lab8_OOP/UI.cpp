#include "UI.h"
#include "activitate.h"
#include <iostream>
#include <string>
#include <exception>
#include <map>

using namespace std;
using std::cout;
using std::cin;

void UI::ui_filtreazaCount() const
{
	std::map<std::string, std::vector<Activitate>> dictionar;
	service.filtreazaCount(dictionar);

	for (auto cheie : dictionar)
		std::cout << cheie.first << " : " << cheie.second.size() << '\n';
}

void UI::ui_salveazaProgram() {
	string fisier;
	cout << "Nume fisier:";
	cin >> fisier;
	if (fisier.size() > 4)
	{
		string extensie = fisier.substr(fisier.size() - 5, 5);
		if (extensie == ".html") {
			service.salveazaProgram(fisier);
			cout << "Export efectuat!\n";
			cout << service.getAllProgram().size() << endl;
		}
		else { cout << "Nu ati dat un fisier html!!!\n"; }
	}
	else cout << "Nu ati dat un fisier html!!!\n";
}

void UI::ui_adaugaProgram() {
	string titlu;
	cout << "Titlul activitatii: ";
	cin >> titlu;
	try
	{
		service.adaugaProgram(titlu);
		cout << "Activitate adaugata cu succes in program!\n";
		cout << service.getAllProgram().size() << endl;
	}
	catch (exception&) { cout << "Nu exista activitatea cu acest titlu sau ea a fost deja adaugata!\n"; }
}

void UI::ui_adaugaRandom() {
	string n;
	int numar;
	cout << "Nr. de activitati de adaugat in lista: ";
	cin >> numar;
	try
	{
		n = stoi(n);
		service.adaugaRandom(numar);
		cout << "Activitate adaugata cu succes in program!\n";
		cout << service.getAllProgram().size() << endl;
	}
	catch (exception&) { cout << "Trebuie sa introduceti un numar intreg!\n\n"; }
}

void UI::ui_golesteProgram() {
	service.golesteProgram();
}

void UI::ui_adaugaActivitate()
{
	string titlu, descriere, tip;
	int durata;
	cout << "Titlul activitatii:";
	cin >> titlu;
	cout << "Descrierea activitatii:";
	cin >> descriere;
	cout << "Tipul activitatii:";
	cin >> tip;
	cout << "Durata:";
	cin >> durata;
	service.adaugaActivitate(titlu, descriere, tip, durata);
	cout << "Adaugat cu succes\n";
}

void UI::ui_stergeActivitate()
{
	string titlu;
	cout << "Titlul activitatii pe care doriti sa o stergeti:";
	cin >> titlu;
	service.stergeActivitate(titlu);
	cout << "Sters cu succes\n";
}

void UI::tipareste(const vector<Activitate>& activitati) {
	cout << "Activitatile sunt:\n";
	for (const auto& activitate : activitati) {
		cout << activitate.getTitlu() << " | " << activitate.getDescriere() << " | " << activitate.getTip() << " | " << activitate.getDurata() << '\n';
	}
}

void UI::start()
{
	while (true)
	{
		cout << "Meniu:\n";
		cout << "1 Adauga o activitate\n2 Sterge o activitate\n3 Filtreaza activitatile dupa descriere\n4 Filtreaza activitatile dupa tip\n5 Sorteaza dupa titlu\n6 Sorteaza dupa descriere\n7 Sorteaza dupa durata si tip\n8 Tipareste toate activitatile\n";
		cout << "10 Adauga o activitate in wishlist\n11 Goleste wishlist\n12 Genereaza un wishlist\n13 Export\n14 Afiseaza wishlist\n15 Filtreaza dupa nr de produse din cosul de cumparaturi\n0 Iesire\nDati comanda:";
		int cmd;
		string descriere, tip;
		cin >> cmd;
		try {
			switch (cmd) {
			case 1:
				ui_adaugaActivitate();
				break;
			case 2:
				ui_stergeActivitate();
				break;
			case 3:
				cout << "Descrierea dupa care doriti sa filtrati:";
				cin >> descriere;
				tipareste(service.filtrare_descriere(descriere));
				break;
			case 4:
				cout << "Tipul dupa care doriti sa filtrati:";
				cin >> tip;
				tipareste(service.filtrareTip(tip));
				break;
			case 5:
				tipareste(service.sortare_dupa_titlu());
				break;
			case 6:
				tipareste(service.sortare_dupa_descriere());
				break;
			case 7:
				tipareste(service.sortare_dupa_durata_tip());
				break;
			case 8:
				tipareste(service.getAll());
				break;
			case 10:
				ui_adaugaProgram();
				break;
			case 11:
				ui_golesteProgram();
				break;
			case 12:
				ui_adaugaRandom();
				break;
			case 13:
				ui_salveazaProgram();
				break;
			case 14:
				try {
					tipareste(service.getAllProgram());
				}
				catch (exception&) { cout << "Nu sunt oferte programate in wishlist!\n"; }
				break;
			case 15:
				ui_filtreazaCount();
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
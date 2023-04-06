#include "Consola.h"

using std::cout;
using std::cin;
using std::string;
using std::ws;

void Consola::printMenu() {
	cout << "Alegeti una dintre urmatoarele optiuni: \n";
	cout << "0. Exit.\n";
	cout << "1. Afisare discipline\n";
	cout << "2. Adaugare disciplina\n";
	cout << "3. Stergere disciplina\n";
	cout << "4. Modificare disciplina\n";
	cout << "5. Filtrare discipline\n";
	cout << "6. Sortare discipline\n";
	cout << "Optiunea dvs: ";
}

void Consola::printDisciplineUI(DynamicArray<Disciplina> discipline) {
	if (discipline.size() == 0)
		cout << "Nu exista nicio disciplina in contract.\n";
	else {
		cout << "---------------------------------------------------------------------------------------\n";
		printf("%15s%15s%15s%20s%20s\n", "ID", "Denumire", "Ore", "Tip", "Cadru Didactic");
		//cout << "    ID      Denumire        Ore        Tip            Cadru Didactic    \n";
		for (int i = 0; i < discipline.size(); i++) {
			printf("%15s%15s%15d%20s%20s\n", discipline[i].getId().c_str(), discipline[i].getDenumire().c_str(), discipline[i].getOre(), discipline[i].getTip().c_str(), discipline[i].getCadruDidactic().c_str());
			//cout << "  " << d.getId() << "     " << d.getDenumire() << "            " << d.getOre() << "       " << d.getTip() << "    " << d.getCadruDidactic() << "\n";
		}
		cout << "---------------------------------------------------------------------------------------\n";
	}
}
void Consola::addDisciplinaUI() {
	int ore;
	string id, denumire, tip, cadruDidactic;
	cout << "Introduceti id-ul disciplinei: ";
	cin >> id;
	cout << "Introduceti denumirea disciplinei: ";
	cin >> denumire;
	cout << "Introduceti numarul de ore pe saptamana pentru aceasta disciplina: ";
	cin >> ore;
	
	while (cin.fail()) {
		cout << "Va rog introduceti un numar intreg\n";
		cin.clear();
		cin.ignore(256, '\n');   // ignore the line change
		cin >> ore;
	}
	
	cout << "Introduceti tipul disciplinei: ";
	cin >> tip;
	cout << "Introduceti cadrul didactic ce preda aceasta disciplina: ";
	//cin >> cadruDidactic;
	getline(cin >> ws, cadruDidactic);

	srv.addDisciplina(id, denumire, ore, tip, cadruDidactic);
	cout << "Disciplina (" << id  << ") a fost adaugata cu succes!\n";
}
void Consola::deleteDisciplinaUI() {
	string id;
	cout << "Introduceti id-ul disciplinei pe care doriti sa o stergeti: ";
	cin >> id;
	srv.deleteDisciplinaSrv(id);
	cout << "Disciplina (" << id << ") a fost stearsa cu succes!\n";
}
void Consola::updateDisciplinaUI() {
	int ore;
	string id, denumire, tip, cadruDidactic;
	cout << "Introduceti id-ul disciplinei pe care doriti sa o modificati: ";
	cin >> id;
	cout << "Introduceti noua denumire a disciplinei: ";
	cin >> denumire;
	cout << "Introduceti noul numar de ore pe saptamana pentru aceasta disciplina: ";
	cin >> ore;

	while (cin.fail()) {
		cout << "Va rog introduceti un numar intreg\n";
		cin.clear();
		cin.ignore(256, '\n');  
		cin >> ore;
	}

	cout << "Introduceti noul tip al disciplinei: ";
	cin >> tip;
	cout << "Introduceti noul cadru didactic ce preda aceasta disciplina: ";
	getline(cin >> ws, cadruDidactic);
	srv.updateDisciplina(id, denumire, ore, tip, cadruDidactic);
	cout << "Disciplina (" << id << ") a fost modificata cu succes!\n";
}

void Consola::filtrareDisciplineUI() {
	cout << "Introduceti criteriul dupa care doriti sa filtrati: \n";
	cout << "1. Numarul de ore din saptamana\n";
	cout << "2. Cadru didactic\n";
	int option;
	cin >> option;
	if (option == 1) {
		int inceput, sfarsit;
		cout << "Introduceti limita inferioara de ore: ";
		cin >> inceput;

		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> inceput;
		}

		cout << "Introduceti limita superioara de ore: ";
		cin >> sfarsit;

		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> sfarsit;
		}

		DynamicArray<Disciplina> rez = srv.filtrareOre(inceput, sfarsit);
		printDisciplineUI(rez);
	}
	else if (option == 2) {
		string cadruDidactic;
		cout << "Introduceti numele cadrului didactic dupa care doriti sa filtrati: ";
		getline(cin >> ws, cadruDidactic);
		DynamicArray<Disciplina> rez = srv.filtrareCadruDidactic(cadruDidactic);
		printDisciplineUI(rez);
	}
	else {
		cout << "Nu ati introdus o optiune valida.\n";
	}
}

void Consola::sortareDisciplineUI() {
	cout << "Alegeti dupa ce doriti sa sortati: \n";
	cout << "1. Denumire\n";
	cout << "2. Numarul de ore\n";
	cout << "3. Tip + cadru didactic\n";
	cout << "Optiunea dvs: ";

	int option;
	cin >> option;
	while (cin.fail()) {
		cout << "Va rog introduceti un numar intreg valid\n";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> option;
	}
	if (option == 1) {
		cout << "Alegeti cum doriti sa sortati: \n";
		cout << "1. Crescator\n";
		cout << "2. Descrescator\n";
		cout << "Optiunea dvs: ";
		cin >> option;
		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg valid\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> option;
		}
		bool reverse = false;
		if (option == 2)
			reverse = true;
		printDisciplineUI(srv.sortByDenumire(reverse));
	}
	else if (option == 2) {
		cout << "Alegeti cum doriti sa sortati: \n";
		cout << "1. Crescator\n";
		cout << "2. Descrescator\n";
		cout << "Optiunea dvs: ";
		cin >> option;
		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg valid\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> option;
		}
		bool reverse = false;
		if (option == 2)
			reverse = true;
		printDisciplineUI(srv.sortByOre(reverse));
	}
	else if (option == 3) {
		cout << "Alegeti cum doriti sa sortati: \n";
		cout << "1. Crescator\n";
		cout << "2. Descrescator\n";
		cout << "Optiunea dvs: ";
		cin >> option;
		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg valid\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> option;
		}
		bool reverse = false;
		if (option == 2)
			reverse = true;
		printDisciplineUI(srv.sortByTipCadruDidactic(reverse));
	}
	else {
		cout << "Nu ati introdus o optiune valida.";
	}
}

void Consola::run() {
	while (true) {
		printMenu();
		int optiune;
		cin >> optiune;
		while (cin.fail()) {
			cout << "Va rog introduceti un numar intreg\n";
			cin.clear();
			cin.ignore(256, '\n'); 
			cin >> optiune;
		}
		try {
			switch (optiune){
			case 1:
				printDisciplineUI(srv.getAll());
				break;
			case 2:
				addDisciplinaUI();
				break;
			case 3:
				deleteDisciplinaUI();
				break;
			case 4:
				updateDisciplinaUI();
				break;
			case 5:
				filtrareDisciplineUI();
				break;
			case 6:
				sortareDisciplineUI();
				break;
			case 0:
				return;
			default:
				cout << "Ati introdus o comanda invalida.\n";
			}
		}
		catch (const RepoExceptions& ex) {
			cout << ex << '\n';
		}
		catch (const ValidateExceptions& ex) {
			cout << ex << '\n';
		}
		catch (const ServiceExceptions& ex) {
			cout << ex << '\n';
		}
	}
}
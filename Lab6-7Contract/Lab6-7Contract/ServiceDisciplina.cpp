#include "ServiceDisciplina.h"

//#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using std::vector;
using std::string;
using std::ostream;


void ServiceDisciplina::addDisciplina(const string& id, const string& denumire, int ore, const string& tip, const string& cadruDidactic) {
	Disciplina d( id, denumire, ore, tip, cadruDidactic );
	validator.validate(d);
	repo.store(d);
}

void ServiceDisciplina::deleteDisciplinaSrv(const string& id) {
	DynamicArray<Disciplina> discipline = repo.getAll();
	bool gasit = 0;
	for (int i = 0; i < discipline.size(); i++)
		if (discipline[i].getId() == id) {
			repo.deleteDisciplina(discipline[i]);
			gasit = 1;
			break;
		}
	if (!gasit) {
		throw ServiceExceptions("Nu exista disciplina cu acest id.");
	}
}

void ServiceDisciplina::updateDisciplina(const string& id, const string& denumireNou, int oreNou, const string& tipNou, const string& cadruDidacticNou) {
	Disciplina dNou{id, denumireNou, oreNou, tipNou, cadruDidacticNou};
	validator.validate(dNou);
	repo.update(dNou);
}

DynamicArray<Disciplina> ServiceDisciplina::filtrare(function<bool(const Disciplina&)> fct) {
	DynamicArray<Disciplina> rez(5);
	DynamicArray<Disciplina> v = repo.getAll();
	for (int i = 0; i < v.size(); i++){
		if (fct(v.get(i))) {
			rez.push_back(v.get(i));
		}
	}
	return rez;
}

DynamicArray<Disciplina> ServiceDisciplina::filtrareOre(int nrOreInceput, int nrOreSfarsit) {
	return filtrare([nrOreInceput, nrOreSfarsit](const Disciplina& d){
		return d.getOre() >= nrOreInceput && d.getOre() <= nrOreSfarsit;
	});
}

DynamicArray<Disciplina> ServiceDisciplina::filtrareCadruDidactic(const string& cadruDidactic) {
	return filtrare([cadruDidactic](const Disciplina& d) {
		return d.getCadruDidactic() == cadruDidactic;
	});
}

ostream& operator<<(ostream& out, const ServiceExceptions& ex) {
	out << ex.msg;
	return out;
}


DynamicArray<Disciplina> ServiceDisciplina::generalSort(int(*maiMicF)(const Disciplina&, const Disciplina&)) {
	DynamicArray<Disciplina> v{ repo.getAll() };
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (maiMicF(v[i], v[j]) == 1) {
				Disciplina aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

DynamicArray<Disciplina> ServiceDisciplina::sortByDenumire(bool reverse = false) {
	if (reverse) {
		return generalSort([](const Disciplina& d1, const Disciplina& d2) {
			if (d1.getDenumire() < d2.getDenumire())
				return 1;
			return 0;
			});
	}
	return generalSort([](const Disciplina& d1, const Disciplina& d2) {
		if (d1.getDenumire() > d2.getDenumire())
			return 1;
		return 0;
	});
}


DynamicArray<Disciplina> ServiceDisciplina::sortByOre(bool reverse = false) {
	if (reverse) {
		return generalSort([](const Disciplina& d1, const Disciplina& d2) {
			if (d1.getOre() < d2.getOre())
				return 1;
			return 0;
			});
	}
	return generalSort([](const Disciplina& d1, const Disciplina& d2) {
		if (d1.getOre() > d2.getOre())
			return 1;
		return 0;
		});
}

DynamicArray<Disciplina> ServiceDisciplina::sortByTipCadruDidactic(bool reverse = false) {
	if (reverse) {
		return generalSort([](const Disciplina& d1, const Disciplina& d2) {
			if (d1.getTip() < d2.getTip() || d1.getTip() == d2.getTip() && d1.getCadruDidactic() < d2.getCadruDidactic())
				return 1;
			return 0;
			});
	}
	return generalSort([](const Disciplina& d1, const Disciplina& d2) {
		if (d1.getTip() > d2.getTip() || d1.getTip() == d2.getTip() && d1.getCadruDidactic() > d2.getCadruDidactic())
			return 1;
		return 0;
		});
}

#pragma once
#include "RepoDisciplina.h"
#include "ValidatorDisciplina.h"
#include "Disciplina.h"

#include <functional>
//#include <vector>

using std::function;

class ServiceExceptions {
	string msg;
public:
	ServiceExceptions(string m) :msg{ m } {}
	friend ostream& operator<<(ostream& out, const ServiceExceptions& ex);
};


class ServiceDisciplina
{
private:
	RepoDisciplina& repo;
	ValidatorDisciplina& validator;

public:
	ServiceDisciplina(RepoDisciplina& repo, ValidatorDisciplina& validator):repo{repo},validator{validator}{
	}
	ServiceDisciplina(const ServiceDisciplina& ot) = delete;

	const DynamicArray<Disciplina>& getAll() {
		return repo.getAll();
	}

	void addDisciplina(const string& id, const string& denumire, int ore, const string& tip, const string& cadruDidactic);

	void deleteDisciplinaSrv(const string& id);

	void updateDisciplina(const string& id, const string& denumireNou, int oreNou, const string& tipNou, const string& cadruDidacticNou);

	DynamicArray<Disciplina> filtrare(function<bool(const Disciplina&)> fct);

	DynamicArray<Disciplina> filtrareOre(int nrOreInceput, int nrOreSfarsit);

	DynamicArray<Disciplina> filtrareCadruDidactic(const string& cadruDidactic);

	DynamicArray<Disciplina> generalSort(int(*maiMicF)(const Disciplina&, const Disciplina&));

	DynamicArray<Disciplina> sortByDenumire(bool reverse);

	DynamicArray<Disciplina> sortByTipCadruDidactic(bool reverse);

	DynamicArray<Disciplina> sortByOre(bool reverse);
};

ostream& operator<<(ostream& out, const ServiceExceptions& ex);


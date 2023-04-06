#include "RepoDisciplina.h"

#include <iostream>
#include <sstream>

using std::string;


void RepoDisciplina::store(const Disciplina& d) {
	if (exists(d)) {
		throw RepoExceptions("Exista deja disciplina cu id: " + d.getId());
	}
	discipline.push_back(d);
}

void RepoDisciplina::deleteDisciplina(const Disciplina& d) {
	if (!exists(d)) {
		throw RepoExceptions("Nu exista disciplina cu id: " + d.getId());
	}

	if (discipline.size() == 1) {
		discipline.remove_element(0);
	}
	else {
		int index = -1;
		for (int i = 0; i < discipline.size() && index == -1; i++) {
			if (discipline[i].getId() == d.getId())
				index = i;
		}
		discipline.remove_element(index);
	}
}

void RepoDisciplina::update(const Disciplina& d) {
	if (!exists(d)) {
		throw RepoExceptions("Nu exista disciplina cu id: " + d.getId());
	}
	int poz = 0;
	for (int i = 0; i < discipline.size(); i++) {
		if (discipline[i].getId() == d.getId()) {
			break;
		}
		poz++;
	}
	discipline[poz] = d;
}

const Disciplina& RepoDisciplina::find(string id) {
	for (int i = 0; i < discipline.size(); i++) {
		if (discipline[i].getId() == id)
			return discipline[i];
	}
	throw RepoExceptions("Nu exista disciplina cu id: " + id);}

const DynamicArray<Disciplina>& RepoDisciplina::getAll() {
	return discipline;
}

bool RepoDisciplina::exists(const Disciplina& d) {
	try {
		find(d.getId());
		return true;
	}
	catch (RepoExceptions&) {
		return false;}
}

ostream& operator<<(ostream& out, const RepoExceptions& ex) {
	out << ex.msg;
	return out;
}
#include "IncAutomata.h"

IncAutomata::IncAutomata() {
	std::ifstream in;
	in.open("./Automatas/inc");
	read(in);
	name = "increment";
}

void IncAutomata::freeTree() {
	elems = std::set<std::vector<State*>>();
}

bool IncAutomata::addElem(std::vector<State*>& elem) {
	bool b = (elems.find(elem) == elems.end());
	if (b)
		elems.insert(elem);
	return b;
}

void IncAutomata::preprocess(const std::vector<State*>& elem, std::vector<State*>& elemRez) {
	//int c = 0;
	//for (int i = 0; i < elem.size(); i++)
	//	if (elem[i]->name == "t")
	//		c++;
	//if (c > 0)
	//	elemRez = std::vector<State*>(c, &states["t"]);
	//else
	//	elemRez = std::vector<State*>(1, &states["e"]);
	elemRez = elem;
}

void IncAutomata::preprocess(std::vector<State*>& elem) {
	preprocess(elem, elem);
}
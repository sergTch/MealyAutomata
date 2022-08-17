#include "Grigorchuk.h"

Grigorchuk::Grigorchuk(){
	std::ifstream in;
	in.open("./Automatas/Grigorchuk");
	read(in);
	name = "Grigorchuk";
	a = &states["a"];
	b = &states["b"];
	c = &states["c"];
	d = &states["d"];
	e = &states["e"];
}

void Grigorchuk::preprocess(const std::vector<State*>& elem, std::vector<State*>& elemRez){
	elemRez = std::vector<State*>(1, e);

	for (int i = 0; i < elem.size(); i++) {
		if (elem[i] == e)
			continue;
		
		if (elemRez.back() == elem[i])
			if (elemRez.size() == 1)
				elemRez.back() = e;
			else elemRez.pop_back();

		else if (elemRez.back() == e)
			elemRez.back() = elem[i];
		
		else if (elemRez.back() == a)
			elemRez.push_back(elem[i]);

		else if (elem[i] == a)
			elemRez.push_back(a);

		else {
			if (b != elemRez.back() && b != elem[i])
				elemRez.back() = b;
			else if (c != elemRez.back() && c != elem[i])
				elemRez.back() = c;
			else if (d != elemRez.back() && d != elem[i])
				elemRez.back() = d;
		}
	}
	if (elemRez.size() == 1 && elemRez[0] == e)
		elemRez.resize(0);
}

void Grigorchuk::preprocess(std::vector<State*>& elem){
	std::vector<State*> elemRez = std::vector<State*>(1, e);
	preprocess(elem, elemRez);
	elem = elemRez;
}

bool Grigorchuk::addElem(std::vector<State*>& elem){
	return elem.size() > 1;
}

bool Grigorchuk::checkElem(std::vector<State*>& elem) {
	return (elem.size() == 1 && elem[0] == e) || elem.size() == 0;
}

void Grigorchuk::freeTree(){
}

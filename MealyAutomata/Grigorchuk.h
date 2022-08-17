#pragma once
#include "Automata.h"
class Grigorchuk :
	public Automata
{
private:
	State *a, *b, *c, *d, *e;
public:
	Grigorchuk();

	void preprocess(const std::vector<State*>& elem, std::vector<State*>& elemRez);
	void preprocess(std::vector<State*>& elem);
	bool addElem(std::vector<State*>& elem);
	bool checkElem(std::vector<State*>& elem);
	void freeTree();
};


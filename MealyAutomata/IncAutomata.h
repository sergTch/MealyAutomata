#pragma once
#include "Automata.h"
#include <set>
class IncAutomata :
	public Automata
{
private:
	std::set<std::vector<State*>> elems;
public:
	IncAutomata();
	
	void preprocess(const std::vector<State*>& elem, std::vector<State*>& elemRez);
	void preprocess(std::vector<State*>& elem);
	bool addElem(std::vector<State*>& elem);
	void freeTree();
};


#pragma once
#include "Automata.h"
class TrAutomata :
	public Automata
{
private:
	State* a, * b, * c, * e;
public:
	TrAutomata();

	bool getNextIndecies(std::vector<int>& indecies, int namesSize);
	int64_t getCountByLen(int len, int namesSize);

	void preprocess(const std::vector<State*>& elem, std::vector<State*>& elemRez);
	void preprocess(std::vector<State*>& elem);
	bool addElem(std::vector<State*>& elem);
	void freeTree();
};


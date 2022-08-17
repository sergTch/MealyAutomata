#include "TrAutomata.h"

TrAutomata::TrAutomata()
{
	std::ifstream in;
	in.open("./Automatas/tr");
	read(in);
	name = "tr";
	a = &states["a"];
	b = &states["b"];
	c = &states["c"];
	e = &states["e"];
}

bool TrAutomata::getNextIndecies(std::vector<int>& indecies, int namesSize)
{
	if (indecies[0] == -1) {
		for (int i = 0; i < indecies.size(); i++)
			indecies[i] = i % 3;
		return true;
	}

	for (int i = indecies.size() - 1; i > 0; i--)
		indecies[i] = (indecies[i] - indecies[i - 1] + 6) % 3;

	indecies[1]++;
	for (int i = 1; i < indecies.size() - 1; i++) {
		if (indecies[i] == 3) {
			indecies[i] = 1;
			indecies[i + 1]++;
		}
	}

	for (int i = 1; i < indecies.size(); i++)
		indecies[i] = (indecies[i - 1] + indecies[i]) % 3;

	if (indecies.back() >= 3)
		indecies.back() %= 3;
	return true;
}

int64_t TrAutomata::getCountByLen(int len, int namesSize)
{
	return pow(2, len - 1);
}

void TrAutomata::preprocess(const std::vector<State*>& elem, std::vector<State*>& elemRez)
{
	elemRez = std::vector<State*>(1, e);

	for (int i = 0; i < elem.size(); i++) {
		if (elem[i] == e)
			continue;

		if (elemRez.back() == elem[i])
			if (elemRez.size() == 1)
				elemRez.back() = e;
			else elemRez.pop_back();
		else if (elemRez.back() != e)
			elemRez.push_back(elem[i]);
		else elemRez.back() = elem[i];
	}
	if (elemRez.size() == 1 && elemRez[0] == e)
		elemRez.resize(0);
}

void TrAutomata::preprocess(std::vector<State*>& elem)
{
	std::vector<State*> elemRez = std::vector<State*>(1, e);
	preprocess(elem, elemRez);
	elem = elemRez;
}

bool TrAutomata::addElem(std::vector<State*>& elem)
{
	return elem.size() > 1;
}

void TrAutomata::freeTree()
{
}

#pragma once
#include "Automata.h"

class Node
{
private:
	Automata* automata;
public:
	std::vector<State*> elem;
	std::vector<Node*> next;
	Node* prev;

	Node();
	Node(Automata* automata);
	Node(Automata* automata, const std::string& s);
	Node(Automata* automata, const std::vector<State*>& s);
	~Node();

	int fillNext(int max);

	int depth();
	void write(std::ostream& out, int space);
};


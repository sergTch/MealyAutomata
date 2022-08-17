#include "ElemTree.h"
#include <set>
#include <queue>
#include <cmath>
#include <algorithm>

Node::Node() {
	automata = NULL;
	elem = std::vector<State*>(0);
	next = std::vector<Node*>(0);
	prev = NULL;
}

Node::Node(Automata* a) {
	automata = a;
	elem = std::vector<State*>(0);
	next = std::vector<Node*>(0);
	prev = NULL;
}

Node::Node(Automata* a, const std::string& s) {
	automata = a;
	a->getStates(s, elem);
	a->preprocess(elem);
	next = std::vector<Node*>(0);
	prev = NULL;
}

Node::Node(Automata* a, const std::vector<State*>& s) {
	automata = a;
	elem = s;
	a->preprocess(elem);
	next = std::vector<Node*>(0);
	prev = NULL;
}

Node::~Node() {
	for (int i = 0; i < next.size(); i++)
		delete next[i];
}

int Node::fillNext(int max) {
	automata->freeTree();

	std::queue<Node*> que = std::queue<Node*>();
	if (automata->addElem(this->elem))
		que.push(this);
	Node* node;

	int t, count = 1;

	while (!que.empty() && count < max) {
		node = que.front();
		node->next = std::vector<Node*>(automata->alphabetSize);
		for (int i = 0; i < automata->alphabetSize; i++) {
			node->next[i] = new Node(automata);
			node->next[i]->elem = node->elem;
			node->next[i]->prev = this;
			t = i;

			for (int j = 0; j < node->elem.size(); j++) {
				node->next[i]->elem[j] = node->elem[j]->transition[t];
				t = node->elem[j]->output[t];
			}

			automata->preprocess(node->next[i]->elem);

			count++;
			if (automata->addElem(node->next[i]->elem))
				que.push(node->next[i]);
		}
		que.pop();
	}
	return count;
}

int Node::depth() {
	int t = 1;
	for (int i = 0; i < next.size(); i++)
		t = std::max(t, 1 + next[i]->depth());
	return t;
}

void Node::write(std::ostream& out, int space) {
	int len = (elem.size() + 1)/2*2, n = automata->alphabetSize;

	std::string empty = std::string(len, ' ');
	std::string elemStr;
	std::string spaces;

	std::queue<Node*> que;
	que.push(this);

	int t = 1, d = depth();

	while (t * (len + 1) * n < space && t * n < std::pow(n,d))
		t*=n;

	space = t * len + t;
	std::cout << "\n";

	for (int i = 1; i <= t; i *= n) {
		bool finish = true;
		spaces = std::string((space / i - len) / 2,' ');
		for (int j = 0; j < i; j++) {
 			if (que.front() != NULL) {
				for (int k = 0; k < n; k++)
					if (que.front()->next.size() <= k)
						que.push(NULL);
					else { que.push(que.front()->next[k]); finish = false; }
				automata->StatesToStr(que.front()->elem, elemStr);
				for (int k = 0; k < (len - elemStr.size()) / 2; k++)
					std::cout << " ";
				std::cout << spaces << elemStr;
				for (int k = 0; k < (len - elemStr.size() + 1) / 2; k++)
					std::cout << " ";
				if (i == t)
					std::cout << " ";
				std::cout << spaces;
			}
			else {
				for (int k = 0; k < n; k++)
					que.push(NULL);
				std::cout << spaces << empty;
				if (i == t)
					std::cout << " ";
				std::cout << spaces;
			}
			que.pop();
			std::cout << "";
		}
		std::cout << "\n\n";
		if (finish)
			break;
	}
}
#include "Automata.h"
#include <set>
#include <algorithm>
#include <queue>
#include <math.h>
#include <string>

void Automata::read(std::istream& in) {
	in >> alphabetSize;
	cout << alphabetSize << endl;
	std::string strNames;
	in >> strNames;
	cout << strNames << endl;
	
	names = std::vector<std::string>();
	
	for (int i = 0; i < strNames.size(); i++) {
		names.push_back(std::string(1, strNames[i]));
	}
	
	states = std::map<std::string, State>();

	for (const auto& name: names) {
		states.emplace(std::make_pair(name, State(name, alphabetSize)));
	}

	for (int i = 0; i < names.size(); i++) {
		std::string name, transition;
		State* state;
		in >> name;
		cout << name << endl;
		state = &states[name];
		for (int i = 0; i < alphabetSize; i++) {
			in >> state->output[i];
			cout << state->output[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < alphabetSize; i++) {
			in >> transition;
			cout << state->output[i] << " ";
			state->transition[i] = &states[transition];
		}
		cout << endl;
	}
	cout << endl;
}

void Automata::write(std::ostream& out) {
	out << alphabetSize << std::endl;
	for (int i = 0; i < names.size(); i++)
		out << names[i];
	out << std::endl;

	for (int i = 0; i < names.size(); i++) {
		out << names[i];
		State *state = &states[names[i]];
		for (int i = 0; i < alphabetSize; i++)
			out << state->output[i];
		for (int i = 0; i < alphabetSize; i++) {
			out << state->transition[i];
		}
	}
}

void Automata::writeElem(const std::vector<State*>& elem, std::ostream& out){
	for (int i = 0; i < elem.size(); i++)
		out << elem[i]->name;
	out << std::endl;
}

void Automata::preprocess(const std::vector<State*>& elem, std::vector<State*>& elemRez){
	elemRez = elem;
}

void Automata::preprocess(std::vector<State*>& elem){
}

bool Automata::addElem(std::vector<State*>& statesVec){
	return false;
}

bool Automata::checkElem(std::vector<State*>& statesVec) {
	return true;
}


void Automata::freeTree() {
}

spMatrix Automata::genMatrix(int len)
{
	size_t n = pow(alphabetSize, len), t, k;
	spMatrix M(n);
	vector<int> input(len), output(len);

	for (size_t i = 0; i < n; i++) {
		input = NToStr(i, len);

		for (auto st = states.begin(); st != states.end(); st++) {
			process(&st->second, input, output);

			t = strToN(output);
			M[i][t]++;
			M[t][i]++;
		}
	}
	cout << endl;

	return M;
}

size_t Automata::strToN(const std::vector<int>& str) {
	size_t n = 0;

	for (int i = str.size() - 1; i >= 0; i--) {
		n *= alphabetSize;
		n += str[i];
	}

	return n;
}

std::vector<int> Automata::NToStr(size_t n, size_t len) {
	std::vector<int> str;
	
	while (len--) {
		str.push_back(n % alphabetSize);
		n /= alphabetSize;
	}

	return str;
}

spMatrix Automata::genMatrix(int len, int n)
{
	auto str = NToStr(n, len);
	return genMatrix(str);
}

spMatrix Automata::genMatrix(const std::vector<int>& str)
{
	int len = str.size();
	size_t n = pow(alphabetSize, len), t, k;
	vector<int> input(len), output(len);
	vector<int> numbers(n, -1), done(n);

	t = strToN(str);
	k = 0;

	std::queue<size_t> que;
	que.push(t);
	numbers[t] = k++;
	done[t] = 1;

	while (!que.empty()) {
		input = NToStr(que.front(), len);
		que.pop();

		for (auto st = states.begin(); st != states.end(); st++) {
			process(&st->second, input, output);
			t = strToN(output);

			if (numbers[t] == -1) {
				numbers[t] = k++;
				que.push(t);
			}
		}
	}

	spMatrix M(k);
	t = strToN(str);
	que.push(t);
	//for (int i = 0; i < n; i++)
	//	numbers[i] = i;

	while (!que.empty()) {
		k = que.front();
		input = NToStr(k, len);
		que.pop();

		for (auto st = states.begin(); st != states.end(); st++) {
			process(&st->second, input, output);
			t = strToN(output);

			M[numbers[t]][numbers[k]]++;
			M[numbers[k]][numbers[t]]++;

			if (!done[t]) {
				que.push(t);
				done[t] = 1;
			}
		}
	}

	return M;
}

void Automata::process(const std::string& seq, const std::vector<int>& input, std::vector<int>& output) {
	std::vector<State*> states;
	getStates(seq, states);
	process(states, input, output);
}


State* Automata::process(const State* state, const std::vector<int>& input, std::vector<int>& output) {
	output = input;
	State* next = nullptr;

	for (int i = 0; i < output.size(); i++) {
		next = state->transition[output[i]];
		output[i] = state->output[output[i]];
		state = next;
	}

	return next;
}

void Automata::process(const std::vector<State*>& statesVec, const std::vector<int>& input, std::vector<int>& output) {
	output = input;
	for (int t = 0; t < statesVec.size(); t++) {
		State* state = statesVec[t];
		State* next;

		for (int i = 0; i < output.size(); i++) {
			std::cout << state->name;
			next = state->transition[output[i]];
			output[i] = state->output[output[i]];
			state = next;
		}
	}
}

void Automata::StatesToStr(const std::vector<State*>& statesVec, std::string& seq) {
	seq = "";
	for (int t = 0; t < statesVec.size(); t++)
		seq += statesVec[t]->name;
}

void Automata::getStates(const std::string& seq, std::vector<State*>& statesVec) {
	if (statesVec.size() != seq.length())
		statesVec.resize(seq.length());

	for (int t = 0; t < seq.size(); t++)
		statesVec[t] = &states[std::string(1, seq[t])];
}

int64_t Automata::neutral(const  std::string& seq) {
	std::vector<State*> states;
	getStates(seq, states);
	return neutral(states);
}

int64_t Automata::neutral(const std::vector<State*>& statesVec) {
	std::queue<std::vector<State*>> que = std::queue<std::vector<State*>>();
	std::vector<State*> next, newNext;
	preprocess(statesVec, next);
	freeTree();
	if (addElem(next))
		que.push(next);
	int t, count = 1;

	while (!que.empty()) {
		std::vector<State*>& elem = que.front();
		next = elem;
		for (int i = 0; i < alphabetSize; i++) {
			t = i;
			
			for (int j = 0; j < elem.size(); j++) {
				next[j] = elem[j]->transition[t];
				t = elem[j]->output[t];
			}
			
			if (t != i)
				return -1;

			preprocess(next, newNext);
			count++;
			
			if (addElem(newNext))
				que.push(newNext);
			else if (!checkElem(newNext))
				return -1;
		}
		que.pop();
	}
	return 1;
}

int64_t Automata::treeSize(const std::vector<State*>& statesVec) {
	std::queue<std::vector<State*>> que = std::queue<std::vector<State*>>();
	std::vector<State*> next, newNext;
	preprocess(statesVec, next);
	freeTree();
	if (addElem(next))
		que.push(next);
	int t, count = 1;

	while (!que.empty()) {
		std::vector<State*>& elem = que.front();
		next = elem;
		for (int i = 0; i < alphabetSize; i++) {
			t = i;
			for (int j = 0; j < elem.size(); j++) {
				next[j] = elem[j]->transition[t];
				t = elem[j]->output[t];
			}
			preprocess(next, newNext);
			count++;
			if (addElem(newNext))
				que.push(newNext);
		}
		que.pop();
	}
	return count;
}

int64_t Automata::treeSize(const  std::string& seq) {
	std::vector<State*> states;
	getStates(seq, states);
	return treeSize(states);
}

int64_t Automata::elemsInTree(const std::vector<State*>& statesVec) {
	std::queue<std::vector<State*>> que = std::queue<std::vector<State*>>();
	std::vector<State*> next, newNext;
	preprocess(statesVec, next);
	freeTree();
	if (addElem(next))
		que.push(next);
	int t, count = next.size();

	while (!que.empty()) {
		std::vector<State*>& elem = que.front();
		next = elem;
		for (int i = 0; i < alphabetSize; i++) {
			t = i;
			for (int j = 0; j < elem.size(); j++) {
				next[j] = elem[j]->transition[t];
				t = elem[j]->output[t];
			}
			preprocess(next, newNext);
			count += newNext.size();
			if (addElem(newNext))
				que.push(newNext);
		}
		que.pop();
	}
	return count;
}

int64_t Automata::elemsInTree(const  std::string& seq) {
	std::vector<State*> states;
	getStates(seq, states);
	return elemsInTree(states);
}

int64_t Automata::elemsOnLevel(const std::vector<State*>& statesVec, int lvl) {
	std::queue<std::pair<std::vector<State*>, int>> que = std::queue<std::pair<std::vector<State*>, int>>();
	std::vector<State*> next, newNext;
	preprocess(statesVec, next);
	freeTree();
	//if (addElem(next))
		que.push(std::pair<std::vector<State*>, int>(next, lvl));
	int curlvl, t, count = 0;

	while (!que.empty()) {
		std::vector<State*>& elem = que.front().first;
		curlvl = que.front().second;

		next = elem;
		for (int i = 0; i < alphabetSize; i++) {
			t = i;
			for (int j = 0; j < elem.size(); j++) {
				next[j] = elem[j]->transition[t];
				t = elem[j]->output[t];
			}

			preprocess(next, newNext);
			if (curlvl > 1) {
				//if (addElem(newNext))
					que.push(std::pair<std::vector<State*>, int>(newNext, curlvl - 1));
			}
			else {
				count += newNext.size();
			}
		}
		que.pop();
	}
	return count;
}

int64_t Automata::elemsOnLevel(const  std::string& seq, int lvl) {
	std::vector<State*> states;
	getStates(seq, states);
	return elemsOnLevel(states, lvl);
}

int64_t Automata::elemsOnLevel(const  std::string& seq) {
	return elemsOnLevel(seq, 3);
}

bool Automata::getNextIndecies(std::vector<int>& indecies, int namesSize) {
	indecies[0]++;
	for (int j = 0; j < indecies.size() - 1; j++) {
		if (indecies[j] == namesSize) {
			indecies[j] = 0;
			indecies[j + 1]++;
		}
	}
	return indecies.back() < namesSize;
}

int64_t Automata::getCountByLen(int len, int namesSize) {
	return pow(namesSize, len);
}

void Automata::estimate(int t, int64_t(Automata::* f)(const std::string&)) {
	std::string s = "";
	estimate(t, f, names, s);
}

void Automata::estimate(int t, int64_t (Automata::* f)(const std::string&), std::vector<std::string>& names, std::string& spliter) {
	std::string fname = "";
	std::string alph = "";
	int64_t(Automata:: * eInT)(const std::string&) = &Automata::elemsInTree;
	int64_t(Automata:: * neut)(const std::string&) = &Automata::neutral;
	int64_t(Automata:: * trSz)(const std::string&) = &Automata::treeSize;
	int64_t(Automata:: * eOnL)(const std::string&) = &Automata::elemsOnLevel;
	if (f == eInT)
		fname = "elemsInTree";
	if (f == neut)
		fname = "neutral";
	if (f == trSz)
		fname = "treeSize";
	if (f == eOnL)
		fname = "elemsOnLevel";

	for (int i = 0; i < names.size(); i++)
		alph += names[i];

	system(("mkdir estimdata\\data\\" + name).data());
	system(("mkdir estimdata\\data\\" + name + "\\" + fname).data());
	system(("mkdir estimdata\\data\\" + name + "\\" + fname + "\\" + alph).data());
	fname = name + "\\" + fname + "\\" + alph + "\\" + std::to_string(t);
	
	std::vector<int> indecies(t, 0);
	indecies[0] = -1;
	std::string elem(t + (t - 1) * spliter.size(), '_');

	for (int i = 0; i < t - 1; i++) {
		for (int j = 0; j < spliter.size(); j++) {
			elem[i * (spliter.size() + 1) + 1 + j] = spliter[j];
		}
	}

	std::map<int64_t, int64_t> rezults;
	std::vector<std::string> max_results;

	int64_t max = -1;
	int64_t elems = getCountByLen(t, names.size());
	int64_t rez;
	int64_t percentage = 0;
	std::cout << "0%";

	for (int64_t i = 0; i < elems; i++) {
		if (percentage < 1000 * (i + 1) / elems) {
			percentage = 1000 * (i + 1) / elems;
			std::cout << "\r" << percentage / 10 << "." << percentage % 10 << "%";
		}
		
		if (!getNextIndecies(indecies, names.size()))
			break;

		for (int j = 0; j < t; j++)
			elem[(spliter.size() + 1) * j] = names[indecies[j]][0];

		rez = (this->*f)(elem);

		if (rez > max) {
			max = rez;
			max_results = std::vector<std::string>();
		}

		if (rez == max)
			max_results.push_back(elem);

		rezults[rez]++;
	}

	std::cout << std::endl;

	std::ofstream out("./estimdata/data/" + fname);
	out << (t - 1) * spliter.size() + t << std::endl;

	for (auto i = rezults.begin(); i != rezults.end(); i++)
		out << i->first << " " << i->second << std::endl;

	out << std::endl;
	for (auto i = max_results.begin(); i != max_results.end(); i++)
		out << *i << std::endl;

	system(("python ./estimdata/analyze_file.py ./estimdata/data/" + fname).data());
}
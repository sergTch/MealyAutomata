#pragma once
#include "State.h"
#include <map>
#include <iostream>
#include <fstream>
#include "spMatrix.h"

class Automata
{
public:
	std::string name = "automata";

	int alphabetSize;
	std::map<std::string, State> states;
	std::vector<std::string> names;

	State* process(const State* state, const std::vector<int>& input, std::vector<int>& output);
	void process(const std::vector<State*>& statesVec, const std::vector<int>& input, std::vector<int>& output);
	void process(const std::string& seq, const std::vector<int>& input, std::vector<int>& output);

	int64_t neutral(const std::vector<State*>& statesVec);
	int64_t neutral(const std::string& seq);

	int64_t treeSize(const std::vector<State*>& statesVec);
	int64_t treeSize(const std::string& seq);
	
	int64_t elemsInTree(const std::vector<State*>& statesVec);
	int64_t elemsInTree(const std::string& seq);

	int64_t elemsOnLevel(const std::vector<State*>& statesVec, int lvl);
	int64_t elemsOnLevel(const std::string& seq, int lvl);
	int64_t elemsOnLevel(const std::string& seq);

	virtual bool getNextIndecies(std::vector<int>& indecies, int namesSize);
	virtual int64_t getCountByLen(int len, int namesSize);
	void estimate(int n, int64_t(Automata::* f)(const std::string&));
	void estimate(int n, int64_t(Automata::* f)(const std::string&), std::vector<std::string>& names, std::string& spliter);

	void StatesToStr(const std::vector<State*>& statesVec, std::string& seq);
	void getStates(const std::string& seq, std::vector<State*>& statesVec);
	void read(std::istream& in);
	void write(std::ostream& out);
	void writeElem(const std::vector<State*>& elem, std::ostream& out);

	virtual void preprocess(const std::vector<State*>& elem, std::vector<State*>& elemRez);
	virtual void preprocess(std::vector<State*>& elem);
	virtual bool addElem(std::vector<State*>& statesVec);
	virtual bool checkElem(std::vector<State*>& statesVec);
	virtual void freeTree();

	size_t strToN(const std::vector<int>& elem);
	std::vector<int> NToStr(size_t n, size_t len);


	spMatrix genMatrix(int n);
	spMatrix genMatrix(const std::vector<int>& str);
	spMatrix genMatrix(int len, int n);
};

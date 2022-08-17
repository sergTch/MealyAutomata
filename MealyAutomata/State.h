#pragma once
#include <vector>
#include <string>

class State
{
public:
	State() = default;
	State(const std::string& name, size_t size);

public:
	std::string name;
	std::vector<int> output;
	std::vector<State*> transition;
};

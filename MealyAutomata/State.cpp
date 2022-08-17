#include "State.h"

State::State(const std::string& name, size_t size)
	: name(name)
	, output(size)
	, transition(size)
{
}

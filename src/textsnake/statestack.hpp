#pragma once
#include "userinput.hpp"
#include <memory>
#include "state.hpp"
#include "pendingstackaction.hpp"
#include <utility>

class StateStack
{
private:
	std::vector<std::unique_ptr<State>> toDelete;
	std::vector<std::unique_ptr<State>> states;
	bool stackModified;

	StateStack() = default;
	~StateStack() = default;

	std::size_t GetLastIndex() const;

public:
	void Clear();

	void PushState(std::unique_ptr<State>&& state);
	void PopState();
	std::size_t StateCount() const;

	void Update(unsigned const elapsedMs);

	static StateStack & GetInstance();
};


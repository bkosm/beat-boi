#pragma once
#include <memory>
#include <stack>
#include "State.h"

typedef std::unique_ptr<State> StateRef;

class StateMaschine
{
public:
	StateMaschine() = default;
	~StateMaschine() = default;

	void addState(StateRef new_state, bool is_replacing);
	void removeState();
	void processStateChanges();

	StateRef& getActiveState();

private:
	StateRef newState_;
	std::stack<StateRef> states_;

	bool isRemoving_{}, isAdding_{}, isReplacing_{};
};
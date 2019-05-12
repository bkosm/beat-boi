#include "pch.h"
#include "StateMaschine.h"

void StateMaschine::addState(StateRef new_state, const bool is_replacing)
{
	isAdding_ = true;
	isReplacing_ = is_replacing;
	newState_ = std::move(new_state);
}

void StateMaschine::removeState()
{
	isRemoving_ = true;
}

void StateMaschine::processStateChanges()
{
	if (isRemoving_ && !states_.empty())
	{
		states_.pop();

		if (!states_.empty())
		{
			states_.top()->resume();
		}

		isRemoving_ = false;
	}
	if (isAdding_)
	{
		if (!states_.empty())
		{
			if (isReplacing_)
			{
				states_.pop();
			}
			else
			{
				states_.top()->pause();
			}
		}

		states_.push(std::move(newState_));
		states_.top()->init();
		isAdding_ = false;
	}
}

StateRef& StateMaschine::getActiveState()
{
	return states_.top();
}
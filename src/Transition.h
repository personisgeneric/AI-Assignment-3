#pragma once
#ifndef __TRANSITION__
#define __TRANSITION__
#include "Condition.h"
#include "State.h"

class Transition
{
public:
	Transition(Condition* condition, State* target_state);
	~Transition();

	// getters
	bool isTriggered() const;
	Condition* getCondition() const;

	// setters
	void setTargetState(State* state);
	void setIsTriggered(bool state);
	void setCondition(Condition* condition);

private:
	Condition* m_condition;
	State* m_targetState;
	bool m_isTriggered;
}
#endif


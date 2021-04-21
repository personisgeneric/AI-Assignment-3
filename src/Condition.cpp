#include "Condition.h"

Condition::Condition(bool condition)
{
SetCondition(condition);
}

Condition::~Condition()
= default;

bool Condition::Test()
{
	return m_condition;
}

void Condition::SetCondition(const bool condition)
{
	m_condition = condition;
}
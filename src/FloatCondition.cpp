#include "FloatCondition.h"

FloatCondition::FloatCondition(const float min_value, const float max_value)
{
	m_minValue = min_value;
	m_maxValue = max_value;
}

FloatCondition::~FloatCondition()
= default;

void FloatCondition::setTestValue(const float value)
{
	m_testValue = value;
}

bool FloatCondition::Test()
{
	return (m_minValue <= m_testValue) && (m_testValue <= m_maxValue);
}
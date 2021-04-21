#pragma once
#ifndef __PATROL__
#define __PATROL__
#include "Action.h"

class Patrol : public Action
{
public:
	Patrol() = default;
	virtual ~Patrol() = default;

	virtual void Execute() = 0;
};
#endif

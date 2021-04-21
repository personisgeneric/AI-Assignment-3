#pragma once
#ifndef __MOVE_TO_LOS__
#define __MOVE_TO_LOS__
#include "Action.h"

class MoveToLOS : public Action
{
public:
	MoveToLOS() = default;
	virtual ~MoveToLOS() = default;

	virtual void Execute() = 0;
};
#endif

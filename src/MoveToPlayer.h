#pragma once
#ifndef __MOVE_TO_PLAYER__
#define __MOVE_TO_PLAYER__
#include "Action.h"

class MoveToPlayer : public Action
{
public:
	MoveToPlayer() = default;
	virtual ~MoveToPlayer() = default;

	virtual void Execute() = 0;
};
#endif

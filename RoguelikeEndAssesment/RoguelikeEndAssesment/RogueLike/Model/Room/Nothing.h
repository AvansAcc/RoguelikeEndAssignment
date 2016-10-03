#pragma once

#include "IRoom.h"

class Nothing : public IRoom {
private:
	char icon;
public:
	char GetIcon();
};

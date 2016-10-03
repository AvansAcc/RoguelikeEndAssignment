#pragma once

#include "Room.h"

class StartRoom : public Room {
private:
	char icon;
public:
	char GetIcon();
};
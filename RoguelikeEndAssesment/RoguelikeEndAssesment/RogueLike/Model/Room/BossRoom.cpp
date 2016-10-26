#include "BossRoom.h"

namespace RogueLike { namespace Model { namespace Room {

	BossRoom::BossRoom(char icon, int x, int y)
		: Room(icon, x, y)
	{
		this->_isDiscovered = false;
	}

	BossRoom::~BossRoom()
	{

	}

	const std::string BossRoom::GetRoomDescription() 
	{
		std::string returnString;
		if (!_description.empty()) {
			returnString = _description;
		}
		else {
			returnString = "Je betreed de kamer. Er is iets extreem fout aan deze ruimte, je voelt je aan alle kanten bekeken en al je instincten schreeuwen om weg te rennen.";
			_description = returnString;
		}
		return returnString;
	}

} } }
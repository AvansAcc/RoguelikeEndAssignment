#include "StairsRoom.h"

namespace RogueLike { namespace Model { namespace Room {

	StairsRoom::StairsRoom(char icon, int x, int y, bool isDirectionDown) 
		: Room(icon, x, y)
	{
		this->_isDirectionDown = isDirectionDown;
		this->_isDiscovered = false;
		
	}

	StairsRoom::~StairsRoom()
	{

	}

	const bool StairsRoom::IsDirectionDown()
	{
		return this->_isDirectionDown;
	}

	const std::string StairsRoom::GetRoomDescription()
	{
		std::string returnString;
		if (!_description.empty()) {
			returnString = _description;
		}
		else {
			if (_isDirectionDown) {
				returnString = "Je betreed de kamer. In het midden van de kamer is een trap die je verder de donkere diepte in kan brengen";
				_description = returnString;
			}
			else {
				returnString = "Je betreed de kamer. In het midden van de kamer is een trap die je dichter richting de uitgang kan brengen";
				_description = returnString;
			}
		}
		return returnString;
	}

} } }
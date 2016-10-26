#include "StartRoom.h"

namespace RogueLike { namespace Model { namespace Room {

	StartRoom::StartRoom(char icon, int x, int y) 
		: Room(icon, x, y)
	{
		this->_isDiscovered = true;
	}

	StartRoom::~StartRoom()
	{

	}

	const std::string StartRoom::GetRoomDescription()
	{
		std::string returnString;
		if (!_description.empty()) {
			returnString = _description;
		}
		else {
			returnString = "Je betreed de eerste kamer. De deur naar buiten sluit boven je en je vraagt je af of je het daglicht ooit nog zult zien";
			_description = returnString;
		}
		return returnString;
	}

} } }
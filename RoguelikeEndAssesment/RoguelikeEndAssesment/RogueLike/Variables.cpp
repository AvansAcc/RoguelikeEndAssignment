#include "Variables.h"

namespace RogueLike {
	namespace Globals {

		const bool DEBUG = false;
		std::vector<std::string>* ROOM_OPTIONS = new std::vector<std::string>({ "Vechten", "Vluchten", "Bezittingen bekijken", "Uitrusten", "Eigenschappen bekijken", "Kaart bekijken", "Item oppakken", "Richting kiezen", "Trap gebruiken", "Terug naar Menu" });
		std::vector<std::string>* COMBAT_OPTIONS = new std::vector<std::string>({ "Aanvallen", "Vluchten", "Bezittingen gebruiken" });
	
	}
}
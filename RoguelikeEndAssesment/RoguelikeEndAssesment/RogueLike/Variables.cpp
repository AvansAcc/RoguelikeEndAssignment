#include "Variables.h"

namespace RogueLike {
	namespace Globals {

		const bool DEBUG = true;
		const bool PRERENDERFOES = true;
		std::vector<std::string>* ROOM_OPTIONS = new std::vector<std::string>({ "Vechten", "Vluchten", "Bezittingen bekijken", "Uitrusten", "Eigenschappen bekijken", "Kaart bekijken", "Item oppakken", "Richting kiezen", "Trap gebruiken", "Terug naar Menu", "Magische Talisman", "Zilveren Kompas" });
		std::vector<std::string>* COMBAT_OPTIONS = new std::vector<std::string>({ "Aanvallen", "Vluchten", "Bezittingen gebruiken", "Gebruik bom" });
	
	}
}
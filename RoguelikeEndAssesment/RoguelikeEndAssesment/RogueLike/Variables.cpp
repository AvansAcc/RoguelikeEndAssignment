#include "Variables.h"

namespace RogueLike {
	namespace Globals {

		const bool DEBUG = false;
		std::vector<std::string>* ROOM_OPTIONS = new std::vector<std::string>({ "Vechten", "Vluchten", "Spullen zien", "Uitrusten", "Eigenschappen zien", "Kaart bekijken", "Item oppakken", "Een gang in lopen", "Trap gebruiken", "Afsluiten" });
		std::vector<std::string>* COMBAT_OPTIONS = new std::vector<std::string>({ "Aanvallen", "Vluchten", "Spullen gebruiken" });
	
	}
}
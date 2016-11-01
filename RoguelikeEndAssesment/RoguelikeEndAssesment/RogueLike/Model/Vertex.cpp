#include "Vertex.h"

namespace RogueLike {
	namespace Model {

		Vertex::Vertex(Vertex* shortestVertex, int distance, int direction, int id, Room::Room* room = nullptr)
		{
			this->shortestVertex = shortestVertex;
			this->distance = distance;
			this->totalDistance = distance;
			this->direction = direction;
			this->id = id;
			this->room = room;
		}

		Vertex::~Vertex()
		{
		}
	}
}
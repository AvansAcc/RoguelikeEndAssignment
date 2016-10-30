#include "Vertex.h"

namespace RogueLike {
	namespace Model {

		Vertex::Vertex(Vertex* shortestVertex, int distance, int direction, int id)
		{
			this->shortestVertex = shortestVertex;
			this->distance = distance;
			this->totalDistance = distance;
			this->direction = direction;
			this->id = id;
		}

		Vertex::~Vertex()
		{
		}
	}
}
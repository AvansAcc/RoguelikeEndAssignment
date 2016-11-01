#pragma once

#include "Room/Room.h"

namespace RogueLike {
	namespace Model {
		class Vertex
		{
		public:
			Vertex(Vertex* shortestVertex, int distance, int direction, int id, Room::Room* room = nullptr);
			~Vertex();
			Vertex* shortestVertex;
			int distance;
			int totalDistance;
			int direction;
			int id;
			Room::Room* room;
		};
	}
}
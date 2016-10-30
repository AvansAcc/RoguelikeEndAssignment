#pragma once

namespace RogueLike {
	namespace Model {
		class Vertex
		{
		public:
			Vertex(Vertex* shortestVertex, int distance, int direction, int id);
			~Vertex();
			Vertex* shortestVertex;
			int distance;
			int totalDistance;
			int direction;
			int id;
		};
	}
}
#pragma once
namespace RogueLike {
	namespace Model {
		class Vertex
		{
		public:
			Vertex(int shortestdir, int distance);
			~Vertex();
			int shortestdir;
			int distance;
		};
	}
}
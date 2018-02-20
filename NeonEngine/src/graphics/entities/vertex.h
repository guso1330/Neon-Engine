#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <unordered_set>
#include <tuple>
#include <set>
#include <ctime>

namespace neon {
	struct Vertex {
		glm::vec3 pos;
		glm::vec2 uv;
		glm::vec3 normal;

		/* Operator functions */
		bool operator == (const Vertex& rhs) const
		{
			return (glm::all(glm::equal(pos, rhs.pos)) && 
					glm::all(glm::equal(uv, rhs.uv))   && 
					glm::all(glm::equal(normal, rhs.normal))); 
		}
		bool operator < (const Vertex& rhs) const
		{
			return (std::tie(pos.x, pos.y, pos.z) < std::tie(rhs.pos.x, rhs.pos.y, rhs.pos.z)) ||
				   (!(std::tie(pos.x, pos.y, pos.z) < std::tie(rhs.pos.x, rhs.pos.y, rhs.pos.z)) && std::tie(uv.x, uv.y) < std::tie(rhs.uv.x, rhs.uv.y)) ||
				   (!(std::tie(uv.x, uv.y) < std::tie(rhs.uv.x, rhs.uv.y)) && std::tie(normal.x, normal.y, normal.z) < std::tie(rhs.normal.x, rhs.normal.y, rhs.normal.z));
		}
	};
}
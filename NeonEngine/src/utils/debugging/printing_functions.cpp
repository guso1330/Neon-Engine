#include <iostream>
#include <vector>
#include <glm/glm.hpp>

namespace neon { 
	namespace debug {
		void print_vector_vec3(const std::vector<vec3> &v) {
			std::cout << "PRINTING A VECTOR OF VEC3" << std::endl;
			std::cout << "-------------------------" << std::endl;
			for(int i=0; i<v.size(); ++i) {
				std::cout << "Vertex " << i << ": " << v[i].x << ", " << v[i].y << ", " << v[i].z << std::endl;
			}
			std::cout << std::endl;
		}

		void print_vector_uint(const std::vector<GLuint> &v) {
			std::cout << "PRINTING A VECTOR OF UNSIGNED INT" << std::endl;
			std::cout << "---------------------------------" << std::endl;
			for(int i=0; i<v.size(); i += 3) {
				std::cout << "Index " << i << ": " << v[i] << ", " << v[i+1] << ", " << v[i+2] << std::endl;
			}
			std::cout << std::endl;
		}
	}
}
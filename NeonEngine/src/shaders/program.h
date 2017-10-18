/*
	TODO: Only supports one program currently, should make support >= 1 shader
*/

#include <glad/glad.h>
#include <vector>
#include "./shader.h"

namespace neon {
	class Program {
		public:
			Program(std::vector<Shader*> shaders);
			~Program();

		public:
			// GETTERS
			const GLuint GetProgramID() const { return m_programID; }

			// TODO: call glUseProgram 
			void Bind();
			void Unbind();
		private:
			void Init();
		private:
			std::vector<Shader*> m_shaders;
			GLuint m_programID;
	};
}

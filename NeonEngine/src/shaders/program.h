#pragma once
/*
	TODO: Only supports one program currently, should make support >= 1 shader
*/

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "./shader.h"

namespace neon {
	class Program {
		public:
			Program(std::vector<Shader*> shaders);
			~Program();

		public:
			// GETTERS
			const GLuint GetProgramID() const { return m_programID; }

			// SETTERS

		public:
			/****************************
			*	GLSL - Shader attribute *
			*	getters and setters		*
			****************************/
			GLint GetUniformLocation(const char* name);

			// 
			void SetUniformMat4(const char* name, const glm::mat4& matrix);
			void SetUniformMat4(GLuint loc, const glm::mat4& matrix);
			void SetUniform4f(GLuint loc, const glm::vec4& v4);
			void SetUniform1i(const char* name, GLfloat v0);
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

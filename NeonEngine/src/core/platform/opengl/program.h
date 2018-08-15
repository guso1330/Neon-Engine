#pragma once
/*
	TODO: Only supports one program currently, should make support >= 1 shader
*/

#include "./GL_Error.h"
#include "./shader.h"

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <unordered_map>

namespace neon {
	class Program {
		public:
			Program(std::vector<Shader*> shaders);
			~Program();

		public:
			// GETTERS
			const unsigned int GetProgramId() const { return m_programID; }

			// SETTERS

		public:
			/****************************
			*	GLSL - Shader attribute *
			*	getters and setters		*
			****************************/
			int GetUniformLocation(const char* name);
			int GetAttributeLocation(const char* name);

			// Set Functions
			void SetUniformMat4(const char* name, const glm::mat4& matrix);
			void SetUniformMat4(unsigned int loc, const glm::mat4& matrix);
			void SetUniformMat3(const char* name, const glm::mat3& matrix);
			void SetUniformMat3(unsigned int loc, const glm::mat3& matrix);
			void SetUniform4f(unsigned int loc, const glm::vec4& v4);
			void SetUniform4f(const char* name, const glm::vec4& v4);
			void SetUniform3f(unsigned int loc, const glm::vec3& v3);
			void SetUniform3f(const char* name, const glm::vec3& v3);
			void SetUniform1f(const char* name, GLfloat v0);
			void SetUniform1i(const char* name, GLint v0);

			void Bind();
			void Unbind();

		private:
			void Init();

		private:
			std::vector<Shader*> m_shaders;
			unsigned int m_programID;

			std::unordered_map<const char*, int> m_uniformLocationCache;
			std::unordered_map<const char*, int> m_attributeLocationCache;
	};
}

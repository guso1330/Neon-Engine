#pragma once
/*
	TODO
		1. Only supports one program currently, should make support >= 1 shader (Oct. 30 - Is this still a true TODO?)
		2. Convert the const char* data types to string
*/

#include "./GL_Error.h"
#include "./shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

namespace Neon {


	class Program {
		typedef std::unordered_map<const char*, int> LocationCache;
		typedef std::pair<std::string, unsigned int> AttributeUniformBlock;

		public:
			Program(std::vector<Shader*> shaders);
			~Program();

		public:
			/****************************
			*	GLSL - Shader attribute *
			*	getters and setters		*
			****************************/
			// Get Functions
			int GetUniformLocation(const char* name);
			int GetAttributeLocation(const char* name);
			const unsigned int GetProgramId() const { return m_programID; }

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

			void SaveUniform(unsigned int block, std::string uniformBlockName);

			void Bind();
			void Unbind();

		private:
			void Init();

		private:
			std::vector<Shader*> m_shaders;
			unsigned int m_programID;

			LocationCache m_uniformLocationCache;
			LocationCache m_attributeLocationCache;
	};
}

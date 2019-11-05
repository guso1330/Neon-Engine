#pragma once
/*
	TODO
		1. Only supports one program currently, should make support >= 1 shader (Oct. 30 - Is this still a true TODO?)
		2. Convert the const char* data types to string
*/

#include "Graphics/Renderers/IProgram.h"
#include "Core/Platforms/OpenGL/GL_Error.h"
#include "Core/Platforms/OpenGL/Shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Neon { namespace OpenGL {
	class Program : public IProgram {
		typedef std::unordered_map<const char*, int> LocationCache;
		typedef std::pair<std::string, unsigned int> AttributeUniformBlock;

		public:
			Program(const std::string& name, std::shared_ptr<Shader>& vertexShader, std::shared_ptr<Shader> fragmentShader);
			~Program();

		public:
			virtual void Bind() override;
			virtual void Unbind() override;

			/* Get Functions */
			int GetUniformLocation(const char* name);
			int GetAttributeLocation(const char* name);
			inline const unsigned int GetId() const { return m_programID; }
			inline virtual const std::string GetName() const override { return m_name; }

			/* Set Functions */
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

		private:
			void Init();

		private:
			std::vector<std::shared_ptr<Shader> > m_Shaders;
			unsigned int m_programID;
			const std::string m_name;

			LocationCache m_uniformLocationCache;
			LocationCache m_attributeLocationCache;
	};

}}

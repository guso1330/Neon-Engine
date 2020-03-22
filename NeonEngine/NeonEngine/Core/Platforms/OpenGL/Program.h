#pragma once
/*
	TODO
		1. Only supports one program currently, should make support >= 1 shader (Oct. 30 - Is this still a true TODO?)
*/

#include "Graphics/Renderers/IProgram.h"
#include "Core/Platforms/OpenGL/GL_Error.h"
#include "Core/Platforms/OpenGL/Shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Neon { namespace OpenGL {
	class Program : public IProgram {
		typedef std::unordered_map<std::string, int> LocationCache;
		typedef std::pair<std::string, unsigned int> AttributeUniformBlock;

		public:
			Program(const std::string& name, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
			Program(const std::string& name, std::shared_ptr<Shader>& vertexShader, std::shared_ptr<Shader> fragmentShader);
			virtual ~Program();

		public:
			virtual void Bind() override;
			virtual void Unbind() override;

			/* Get Functions */
			int GetUniformLocation(const std::string& name);
			int GetAttributeLocation(const std::string& name);
			inline const unsigned int GetId() const { return m_programID; }
			inline virtual const std::string GetName() const override { return m_name; }

			/* Set Functions */
			virtual void SetInt(const std::string& name, int value) override;
			virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
			virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
			virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		private:
			void Init();

		private:
			std::vector<std::shared_ptr<Shader>> m_Shaders;
			unsigned int m_programID;
			const std::string m_name;

			LocationCache m_uniformLocationCache;
			LocationCache m_attributeLocationCache;
	};

}}

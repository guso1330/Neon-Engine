#pragma once

#include "Graphics/Shaders/IShader.h"

namespace Neon {
	class IProgram {
		public:
			virtual ~IProgram() = default;

			/* Public Methods */
			virtual void Bind() = 0;
			virtual void Unbind() = 0;

			/* Getters */
			virtual const std::string GetName() const = 0;

			static IProgram* Create(const std::string& name, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	};

	class ProgramLibrary {
		public:
			/* Public Methods */
			void Add(const std::shared_ptr<IProgram>& program);
			void Replace(const std::string& name, const std::shared_ptr<IProgram>& program);
			bool Exists(const std::string& name) const;

			/* Getters */
			std::shared_ptr<IProgram> Get(const std::string& name);

		private:
			std::unordered_map<std::string, std::shared_ptr<IProgram>> m_Programs;
	};
}

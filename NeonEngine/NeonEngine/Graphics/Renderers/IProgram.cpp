#include "Graphics/Renderers/IProgram.h"
#include "Core/Core.h"
#include "nepch.h"

namespace Neon {
	std::shared_ptr<IProgram> Create(const std::string& name, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
		// Switch statement selecting version of create function
	}

	void ProgramLibrary::Add(const std::shared_ptr<IProgram>& program) {
		const std::string name = program->GetName();
		if (!Exists(name)) {
			m_Programs.insert(std::make_pair(name, program));
		} else {
			NE_CORE_ERROR("ProgramLibrary: Shader {} doesn't exist", name);
		}
	}

	void ProgramLibrary::Replace(const std::string& name, const std::shared_ptr<IProgram>& program) {
		if(Exists(name)) {
			m_Programs[name] = program;
		} else {
			NE_CORE_ERROR("ProgramLibrary: Shader {} doesn't exist", name);
		}
	}

	bool ProgramLibrary::Exists(const std::string& name) const {
		return m_Programs.find(name) != m_Programs.end();
	}
}

#pragma once

#include "nepch.h"

namespace Neon {
	enum class ShaderType {
		UNDEFINED = 0,
		VERTEX_SHADER = 1,
		FRAGMENT_SHADER = 2,
		GEOMETRY_SHADER = 3,
		COMPUTE_SHADER = 4
	};

	class IShader {
		public:
			virtual ~IShader() = default;

			/* Getters */
			virtual const ShaderType GetType() const = 0;

			static IShader* Create(const std::string& filepath, const ShaderType type);
	};
}

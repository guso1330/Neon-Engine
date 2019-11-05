#pragma once

#include "nepch.h"

namespace Neon {
	enum class TextureType {
		UNDEFINED = 0,
		DIFFUSE = 1,
		NORMAL = 2,
		SPECULAR = 3,
		HEIGHT = 4,
		OCCLUSION = 5
	};
	class ITexture {
		public:
			virtual ~ITexture() = default;

			/* Public Methods */
			virtual void Bind(unsigned int unit = 0) const = 0;
			virtual void Unbind(unsigned int unit = 0) const = 0;

			/* Getters */
			virtual const unsigned int GetWidth() const = 0;
			virtual const unsigned int GetHeight() const = 0;

			static std::shared_ptr<ITexture> Create(const std::string& filepath);
	};
}
